// TianLi.TruthEye.cpp: 定义动态链接库的实现
//

#include "../include/TianLi.TruthEye.h"
// src
#include "form/te.popup.window.h"
// qt
#include <QApplication>
#include <QMetaType>
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
#include <filesystem>
// win
#include <Windows.h>
#include <winver.h>
// spdlog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/dup_filter_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

void init_logger()
{
    static bool is_inited = false;
    if (is_inited)
    {
        return;
    }
    // 全局日志
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("TianLi.TruthEye.log", 1024 * 1024 * 5, 2));
    sinks.push_back(std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(5)));
    auto logger = std::make_shared<spdlog::logger>("TianLi.TruthEye.Impl", sinks.begin(), sinks.end());
    // 每次启动的详细日志，每次启动都会清空
    if (std::filesystem::exists("TianLi.TruthEye.trace.log"))
    {
        std::filesystem::remove("TianLi.TruthEye.trace.log");
    }
    std::vector<spdlog::sink_ptr> trace_sinks;
    trace_sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("TianLi.TruthEye.trace.log"));
    trace_sinks.push_back(std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(5)));
    auto track_logger = std::make_shared<spdlog::logger>("trace", trace_sinks.begin(), trace_sinks.end());
    track_logger->set_level(spdlog::level::trace);
    // 注册
    spdlog::register_logger(track_logger);
    // 设置日志
    spdlog::set_default_logger(logger);
    spdlog::flush_every(std::chrono::seconds(1));
    spdlog::flush_on(spdlog::level::warn);
    is_inited = true;
}
static QApplication *g_app = nullptr;
static tePopupWindow *g_window = nullptr;
static std::thread g_thread;
static std::mutex g_mutex;
static std::condition_variable g_cv;
static void CreateQApplication()
{
    int argc = 1;
    TCHAR modulePath[MAX_PATH] = {0};
    GetModuleFileName(NULL, modulePath, MAX_PATH);
    char *argv[] = {(char *)modulePath};
    // 禁用自适应高DPI缩放，改为传入缩放比例
    // g_app->setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    spdlog::info("创建窗口事件循环 {}", modulePath);
    g_app = &app;
    g_window = new tePopupWindow();
    // 窗口创建完成
    g_cv.notify_one();
    g_app->exec();
    spdlog::info("窗口事件循环结束");
    spdlog::shutdown();
}

void TianLiTruthEye_Version(const char *version_buff, unsigned int buff_size)
{
    auto size = GetFileVersionInfoSizeA("TianLi.TruthEye.dll", NULL);
    if (size == 0)
        return;

    std::vector<char> buff(size);
    if (!GetFileVersionInfoA("TianLi.TruthEye.dll", NULL, size, buff.data()))
        return;
    VS_FIXEDFILEINFO *pFileInfo = NULL;
    UINT uLen = 0;
    if (!VerQueryValueA(buff.data(), "\\", (LPVOID *)&pFileInfo, &uLen))
        return;
    if (pFileInfo == NULL)
        return;
    sprintf_s((char *)version_buff, buff_size, "%d.%d.%d", HIWORD(pFileInfo->dwFileVersionMS), LOWORD(pFileInfo->dwFileVersionMS), HIWORD(pFileInfo->dwFileVersionLS));

    spdlog::info("悬浮窗版本: {}", version_buff);
}

void TianLiTruthEye_CreateWindow()
{
    init_logger();
    if (g_app != nullptr)
    {
        return;
    }
    spdlog::info("悬浮窗创建");
    g_thread = std::thread(CreateQApplication);
    // 等待窗口创建完成
    std::unique_lock lock(g_mutex);
    g_cv.wait(lock);
}

void TianLiTruthEye_DestroyWindow()
{
    if (g_app == nullptr)
    {
        return;
    }
    spdlog::info("悬浮窗销毁");
    g_app->exit(0);
    if (g_thread.joinable())
    {
        g_thread.join();
    }
}

void TianLiTruthEye_ShowWindow()
{
    if (g_window == nullptr)
    {
        return;
    }
    g_window->show_window();
}

void TianLiTruthEye_HideWindow()
{
    if (g_window == nullptr)
    {
        return;
    }
    g_window->hide_window();
}

void TianLiTruthEye_SetJsonParams(const char *json_buff, unsigned int buff_size)
{
    if (g_window == nullptr)
    {
        return;
    }
    g_window->signal_set_json_params(json_buff, buff_size);
}
