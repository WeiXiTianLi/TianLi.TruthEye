// QApp.cpp: 定义动态链接库的实现
//

#include "../include/TianLi.TruthEye.h"
// src
#include "source/form/te.popup.window.h"
// 3rd
//#include <fmt>
#include <meojson/include/json.hpp>
#include <cpp-httplib/include/httplib.h>
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

    std::string jsonStr(json_buff,buff_size);
    auto json_res = json::parse(jsonStr);
    if (json_res.has_value() == false)
    {
        return;
    }
    auto json = json_res.value();

    if (json["version"] != "1.0.0")
    {
        return;
    }
    struct tePoint
    {
        float x;
        float y;
    };
    struct item_set
    {
        std::string name;
        std::string url;
        std::vector<tePoint> points;
    };

std::vector<item_set> items;
    for (auto& item : json["content"].as_array())
    {
        item_set item_set;
        item_set.name = item["name"].as_string();
        item_set.url = item["url"].as_string();
        for (auto& point : item["points"].as_array())
        {
            tePoint te_point;
            te_point.x = point["x"].as_float();
            te_point.y = point["y"].as_float();
            item_set.points.push_back(te_point);
        }
        items.push_back(item_set);
    }
    // download image
for (auto& item : items)
    {
        std::string url = item.url;
        std::string name = item.name;
        std::string path = "./";
        path += name;
        path += ".png";
        auto res = httplib::Client("127.0.0.1").Get(url.c_str());
        if (res && res->status == 200)
        {
            std::ofstream out(path, std::ios::binary);
            out.write(res->body.c_str(), res->body.size());
            out.close();
        }
        else
        {
            std::cout << "download image failed" << res.error() << std::endl;
        }
    }
    
    // json:
    /*
    {
        "version": "1.0.0",
        "type": "update",
        "content": [
            {
                "name": "风晶蝶",
                "url": "https://xxx",
                "points":[
                   {
                        "x": 100,
                        "y": 100
                    },
                    {
                        "x": 200,
                        "y": 200
                    }
                ]
            },
            {
                "name": "宝箱",
                "url": "https://xxx",
                "points":[
                   {
                        "x": 10,
                        "y": 10
                    }
                ]
            }
        ]
    }
    */

    return  void();
}
