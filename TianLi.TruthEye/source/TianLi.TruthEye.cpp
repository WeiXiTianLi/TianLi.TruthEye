// QApp.cpp: 定义动态链接库的实现
//

#include "../include/TianLi.TruthEye.h"
// src
#include "source/form/te.popup.window.h"
// vcpkg
//#include <cpr/cpr.h>
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

static QApplication* g_app = nullptr;
static tePopupWindow* g_window = nullptr;
static std::thread*  g_thread = nullptr;
static std::mutex g_mutex;
static std::condition_variable g_cv;
static void CreateQApplication()
{
    int argc = 1;
    TCHAR modulePath[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, modulePath, MAX_PATH);
    char* argv[] = { (char*)modulePath };
    // 高分屏支持
    g_app->setAttribute(Qt::AA_EnableHighDpiScaling);
    g_app = new QApplication(argc, argv);

    
    //QMetaType::registerComparators<std::string>();
    g_window = new tePopupWindow();
    g_cv.notify_one();
    g_app->exec();
}

void TianLiTruthEye_CreateWindow()
{
    g_thread = new std::thread(CreateQApplication);
    std::unique_lock lock(g_mutex);
    g_cv.wait(lock);
}

void TianLiTruthEye_DestroyWindow()
{
    if (g_app == nullptr)
    {
        return;
    }
    g_app->exit(0);
    g_thread->join();
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

void SetJsonParams(const char* json_buff, unsigned int buff_size)
{
    if (g_window == nullptr)
    {
        return;
    }
    g_window->signal_set_json_params(json_buff, buff_size);
}
