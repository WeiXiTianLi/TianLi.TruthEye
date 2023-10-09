// QApp.cpp: 定义动态链接库的实现
//

#include "../include/TianLi.TruthEye.h"
// vcpkg
// #include <cpr/cpr.h>
// std
#include <future>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// win
#include <Windows.h>
// spdlog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/dup_filter_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
std::string utf8_to_gbk(const std::string &utf8_string)
{
    std::string ret_string;
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, NULL, 0);
    wchar_t *gbk_wstring = new wchar_t[len + 1];
    memset(gbk_wstring, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, gbk_wstring, len);
    len = WideCharToMultiByte(CP_ACP, 0, gbk_wstring, -1, NULL, 0, NULL, NULL);
    char *gbk_string = new char[len + 1];
    memset(gbk_string, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, gbk_wstring, -1, gbk_string, len, NULL, NULL);
    ret_string = gbk_string;
    delete[] gbk_string;
    delete[] gbk_wstring;
    return ret_string;
}

std::string gbk_to_utf8(const std::string &gbk_string)
{
    std::string ret_string;
    int len = MultiByteToWideChar(CP_ACP, 0, gbk_string.c_str(), -1, NULL, 0);
    wchar_t *utf8_wstring = new wchar_t[len + 1];
    memset(utf8_wstring, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, 0, gbk_string.c_str(), -1, utf8_wstring, len);
    len = WideCharToMultiByte(CP_UTF8, 0, utf8_wstring, -1, NULL, 0, NULL, NULL);
    char *utf8_string = new char[len + 1];
    memset(utf8_string, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, utf8_wstring, -1, utf8_string, len, NULL, NULL);
    ret_string = utf8_string;
    delete[] utf8_string;
    delete[] utf8_wstring;
    return ret_string;
}

class lib_impl
{
    lib_impl()
    {
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("TianLi.TruthEye.log", 1024 * 1024 * 5, 3));
        sinks.push_back(std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(5)));
        auto logger = std::make_shared<spdlog::logger>("TianLi.TruthEye", sinks.begin(), sinks.end());
        spdlog::set_default_logger(logger);
        spdlog::flush_every(std::chrono::seconds(1));
        spdlog::flush_on(spdlog::level::err);
    }

public:
    ~lib_impl() { spdlog::shutdown(); }
    static lib_impl *get_instance()
    {
        static lib_impl instance;
        return &instance;
    }

public:
    HMODULE libptr = nullptr;
    typedef void (*create_func_type)();
    typedef void (*destroy_func_type)();
    typedef void (*show_func_type)();
    typedef void (*hide_func_type)();
    typedef void (*set_func_type)(const char *, unsigned int);

    create_func_type create_funcptr = nullptr;
    destroy_func_type destroy_funcptr = nullptr;
    show_func_type show_funcptr = nullptr;
    hide_func_type hide_funcptr = nullptr;
    set_func_type set_funcptr = nullptr;
    bool is_loaded = false;

    std::string libpath = "TianLi.TruthEye.dll";
    std::string local_version;
    std::string remote_api = "https://github.com/WeiXiTianLi/TianLi.TruthEye/releases/latest";
    std::string remote_api_chinese = "https://gitee.com/WeiXiTianLi/TianLi.TruthEye/releases/latest";
};
#define impl lib_impl::get_instance()

HMODULE Load(std::string libpath)
{
    impl;
    spdlog::info("加载Impl: {}", libpath);
    spdlog::info("可能路径gbk_to_utf8版本:{}", gbk_to_utf8(libpath));
    spdlog::info("可能路径utf8_to_gbk版本:{}", utf8_to_gbk(libpath));

    HMODULE libptr = nullptr;
    // 1. 不转换调用A版本
    libptr = LoadLibraryA(libpath.c_str());
    if (libptr != nullptr)
    {
        spdlog::info("命中原始版本路径");
        return libptr;
    }
    // 2. 转换为utf8调用A版本
    libptr = LoadLibraryA(gbk_to_utf8(libpath).c_str());
    if (libptr != nullptr)
    {
        spdlog::info("命中gbk_to_utf8版本路径");
        return libptr;
    }
    // 3. 转换为gbk调用A版本
    libptr = LoadLibraryA(utf8_to_gbk(libpath).c_str());
    if (libptr != nullptr)
    {
        spdlog::info("命中utf8_to_gbk版本路径");
        return libptr;
    }
    spdlog::warn("未命中路径");
    return nullptr;
}

bool TianLiTruthEye_Impl_Load(const char *path, bool is_reload)
{
    impl;
    spdlog::info("加载实现:{}, 重加载:{}", path, is_reload);
    if (impl->libptr != nullptr)
    {
        if (is_reload == false)
        {
            return true;
        }
        FreeLibrary(impl->libptr);
        impl->libptr = nullptr;
    }
    if (path != nullptr)
    {
        impl->libpath = std::string{path};
    }
    if (impl->libpath.empty())
    {
        impl->libpath = "TianLi.TruthEye.dll";
    }
    // 相对路径不一定找不到，所以不需要判断
    // if (std::filesystem::exists(impl->libpath) == false)
    // {
    //     return false;
    // }
    impl->libptr = Load(impl->libpath);
    if (impl->libptr == nullptr)
    {
        return false;
    }
    impl->create_funcptr = (lib_impl::create_func_type)GetProcAddress(impl->libptr, "TianLiTruthEye_CreateWindow");
    impl->destroy_funcptr = (lib_impl::destroy_func_type)GetProcAddress(impl->libptr, "TianLiTruthEye_DestroyWindow");
    impl->show_funcptr = (lib_impl::show_func_type)GetProcAddress(impl->libptr, "TianLiTruthEye_ShowWindow");
    impl->hide_funcptr = (lib_impl::hide_func_type)GetProcAddress(impl->libptr, "TianLiTruthEye_HideWindow");
    impl->set_funcptr = (lib_impl::set_func_type)GetProcAddress(impl->libptr, "TianLiTruthEye_SetJsonParams");
    if (impl->create_funcptr == nullptr || impl->destroy_funcptr == nullptr || impl->show_funcptr == nullptr || impl->hide_funcptr == nullptr || impl->set_funcptr == nullptr)
    {
        FreeLibrary(impl->libptr);
        impl->libptr = nullptr;
        impl->create_funcptr = nullptr;
        impl->destroy_funcptr = nullptr;
        impl->show_funcptr = nullptr;
        impl->hide_funcptr = nullptr;
        impl->set_funcptr = nullptr;
        return false;
    }
    impl->is_loaded = true;
    return true;
}
bool TianLiTruthEye_Impl_Load_Version(const char *version)
{
    impl;
    spdlog::info("加载指定版本实现:{}", version);
    return true;
}
bool TianLiTruthEye_Impl_Free()
{
    impl;
    spdlog::info("卸载当前实现:{}, 加载情况:{}", impl->libpath, impl->libptr != nullptr);
    if (impl->libptr == nullptr)
    {
        return false;
    }
    FreeLibrary(impl->libptr);
    impl->libptr = nullptr;
    impl->create_funcptr = nullptr;
    impl->destroy_funcptr = nullptr;
    impl->show_funcptr = nullptr;
    impl->hide_funcptr = nullptr;
    impl->set_funcptr = nullptr;
    impl->is_loaded = false;
    return true;
}
void TianLiTruthEye_CreateWindow()
{
    if (impl->is_loaded == false)
    {
        if (TianLiTruthEye_Impl_Load(nullptr, false) == false)
        {
            return;
        }
    }
    impl->create_funcptr();
}

void TianLiTruthEye_DestroyWindow()
{
    if (impl->is_loaded == false)
    {
        return;
    }
    impl->destroy_funcptr();
    // 可能需要自动加载，但是释放的时候需要明确的手动执行
    // if (impl->is_loaded == true)
    // {
    //     TianLiTruthEye_Impl_Free();
    // }
}

void TianLiTruthEye_ShowWindow()
{
    if (impl->is_loaded == false)
    {
        return;
    }
    impl->show_funcptr();
}

void TianLiTruthEye_HideWindow()
{
    if (impl->is_loaded == false)
    {
        return;
    }
    impl->hide_funcptr();
}

void TianLiTruthEye_SetJsonParams(const char *json_buff, unsigned int buff_size)
{
    if (impl->is_loaded == false)
    {
        return;
    }
    impl->set_funcptr(json_buff, buff_size);
}

bool TianLiTruthEye_Impl_Check_Update();
bool TianLiTruthEye_Impl_Get_Update_Info(char *json_buff, unsigned int buff_size);
bool TianLiTruthEye_Impl_Checkout_Version(char *json_buff, unsigned int buff_size);
bool TianLiTruthEye_Impl_Auto_Checkout_Version(char *json_buff, unsigned int buff_size,
                                               void (*download_progress)(int, int),
                                               void (*install_progress)(int, int));
bool TianLiTruthEye_Impl_Get_Version(char *json_buff, unsigned int buff_size);
void TianLiTruthEye_Impl_Async_Download(void (*progress)(int, int));
void TianLiTruthEye_Impl_Async_Install(void (*progress)(int, int));