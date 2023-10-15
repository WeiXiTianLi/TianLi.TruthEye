// QAppMutRelease.cpp: 定义应用程序的入口点。
//
#define TIANLI_TRUTHEYE_IMPL
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
static void progress(int progress, int total)
{
    std::cout << "download progress: " << progress << "/" << total << std::endl;
}

int main()
{
    // TianLiTruthEye_Impl_Async_Download(progress);

    std::string path = "TianLi.TruthEye.dll";
    TianLiTruthEye_Impl_Load(path.c_str());
    TianLiTruthEye_CreateWindow();
    TianLiTruthEye_ShowWindow();

    std::vector<obj> objs;
    objs.push_back({"风晶蝶", "https://tiles.yuanshen.site/d/marker_image/icons/%E6%B5%8B%E8%AF%95%E5%9B%BE%E6%A0%871.png", {{10, 10}, {12, 12}}});
    objs.push_back({"宝箱", "https://tiles.yuanshen.site/d/marker_image/icons/%E6%B5%8B%E8%AF%95%E5%9B%BE%E6%A0%871.png", {{20, 30}}});
    //

    for (int i = 0; i < 10; i++)
    {
        objs[0].points[0].x += 1;
        auto json_str = format_json(objs);
        TianLiTruthEye_SetJsonParams(json_str.c_str(), json_str.size());
        this_thread::sleep_for(100ms);
    }
    std::string test = R"({"version": "1.0.1","type" : "update","content" : [{"name": "item","url" : "https://tiles.yuanshen.site/d/marker_image/icons/%E6%B5%8B%E8%AF%95%E5%9B%BE%E6%A0%871.png","points" : [{"x": 14,"y" : -8}],"content_info" : {
  "text": "这是一个【完成雷霆探针解密】后携带雷种子使用雷极飞到空中获得的【散失的雷神瞳】",
  "picture_url": "https://yuanshen.site/comment_png/288_48.jpg"
}}]})";
    TianLiTruthEye_SetJsonParams(test.c_str(), test.size());

    this_thread::sleep_for(2000ms);
    // TianLiTruthEye_HideWindow();
    // this_thread::sleep_for(2s);
    // TianLiTruthEye_ShowWindow();
    // this_thread::sleep_for(2s);
    // TianLiTruthEye_HideWindow();
    // this_thread::sleep_for(2s);
    TianLiTruthEye_DestroyWindow();
    TianLiTruthEye_Impl_Free();
    return 0;
}
