// QAppMutRelease.cpp: 定义应用程序的入口点。
//
#include "../TianLi.TruthEye/TianLi.TruthEye.h"
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
