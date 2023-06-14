// QAppMutRelease.cpp: 定义应用程序的入口点。
//
#include "../TianLi.TruthEye/include/TianLi.TruthEye.h"
// std
#include <thread>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

int main()
{
	TianLiTruthEye_CreateWindow();
	TianLiTruthEye_ShowWindow();

	std::string json_str = R"({
        "version": "1.0.0",
        "type" : "update",
        "content" : [
    {
        "name": "风晶蝶",
            "url" : "http://assets.yuanshen.site/icons/59.png",
            "points" : [
        {
            "x": 100,
                "y" : 100
        },
                    {
                        "x": 200,
                        "y" : 200
                    }
            ]
    },
            {
                "name": "宝箱",
                "url" : "http://assets.yuanshen.site/icons/59.png",
                "points" : [
                   {
                        "x": 10,
                        "y" : 10
                    }
                ]
            }
        ]
})";

    SetJsonParams(json_str.c_str(), json_str.size());
        
	this_thread::sleep_for(2s);
	TianLiTruthEye_HideWindow();
	this_thread::sleep_for(2s);
	TianLiTruthEye_ShowWindow();
	this_thread::sleep_for(2s);
	TianLiTruthEye_HideWindow();
	this_thread::sleep_for(2s);
	TianLiTruthEye_DestroyWindow();
	return 0;
}
