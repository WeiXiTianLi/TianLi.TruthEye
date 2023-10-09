// QApp.cpp: 定义动态链接库的实现
//

#include "../include/TianLi.TruthEye.h"
// src
#include "source/form/te.popup.window.h"
// vcpkg
// #include <cpr/cpr.h>
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
// win
#include <Windows.h>
// spdlog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/dup_filter_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
void init_logger()
{
    static bool is_inited = false;
    if (is_inited)
    {
        return;
    }
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("TianLi.TruthEye.log", 1024 * 1024 * 5, 3));
    sinks.push_back(std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(5)));
    auto logger = std::make_shared<spdlog::logger>("TianLi.TruthEye.Impl", sinks.begin(), sinks.end());
    spdlog::set_default_logger(logger);
    spdlog::flush_every(std::chrono::seconds(1));
    spdlog::flush_on(spdlog::level::warn);
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
    g_app->setAttribute(Qt::AA_EnableHighDpiScaling);
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
