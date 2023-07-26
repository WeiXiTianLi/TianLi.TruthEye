// QAppMutRelease.cpp: 定义应用程序的入口点。
//
#include "../TianLi.TruthEye/include/TianLi.TruthEye.h"
// std
#include <thread>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

struct point
{
    int x;
    int y;
};
struct obj
{
    std::string name;
    std::string url;
    std::vector<point> points;
};

std::string format_json(std::vector<obj> objs)
{
    auto json_head = R"({"version": "1.0.0","type" : "update","content" : [)";
    auto json_tail = R"(]})";
    std::string json_body;
    for (auto &obj : objs)
    {
        json_body += R"({"name": ")" + obj.name + R"(","url" : ")" + obj.url + R"(","points" : [)";
        for (auto &point : obj.points)
        {
            json_body += R"({"x": )" + std::to_string(point.x) + R"(,"y" : )" + std::to_string(point.y) + R"(})";
            if (&point != &obj.points.back())
            {
                json_body += ",";
            }
        }
        json_body += R"(]})";
        if (&obj != &objs.back())
        {
            json_body += ",";
        }
    }
    return json_head + json_body + json_tail;
}

int main()
{
    TianLiTruthEye_CreateWindow();
    TianLiTruthEye_ShowWindow();

    std::vector<obj> objs;
    objs.push_back({"风晶蝶", "http://assets.yuanshen.site/icons/59.png", {{10, 10}, {12, 12}}});
    objs.push_back({"宝箱", "http://assets.yuanshen.site/icons/59.png", {{20, 30}}});
    //

    for (int i = 0; i < 10; i++)
    {
        objs[0].points[0].x += 1;
        auto json_str = format_json(objs);
        TianLiTruthEye_SetJsonParams(json_str.c_str(), json_str.size());
        this_thread::sleep_for(100ms);
    }

    this_thread::sleep_for(2s);
    // TianLiTruthEye_HideWindow();
    // this_thread::sleep_for(2s);
    // TianLiTruthEye_ShowWindow();
    // this_thread::sleep_for(2s);
    // TianLiTruthEye_HideWindow();
    // this_thread::sleep_for(2s);
    TianLiTruthEye_DestroyWindow();
    return 0;
}
