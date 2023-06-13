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
	CreateApp();
	this_thread::sleep_for(2s);
	DestroyApp();
	return 0;
}
