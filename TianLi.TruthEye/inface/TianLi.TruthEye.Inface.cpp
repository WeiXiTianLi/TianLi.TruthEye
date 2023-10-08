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

class lib_impl
{
    lib_impl() = default;

public:
    ~lib_impl() = default;
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

bool TianLiTruthEye_Impl_Load(bool is_reload)
{
    if (impl->libptr != nullptr)
    {
        if (is_reload == false)
        {
            return true;
        }
        FreeLibrary(impl->libptr);
        impl->libptr = nullptr;
    }
    impl->libptr = LoadLibraryA(impl->libpath.c_str());
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
    return true;
}
bool TianLiTruthEye_Impl_Free()
{
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
        // return;
        TianLiTruthEye_Impl_Load();
        if (impl->is_loaded == false)
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
    if (impl->is_loaded == true)
    {
        TianLiTruthEye_Impl_Free();
    }
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