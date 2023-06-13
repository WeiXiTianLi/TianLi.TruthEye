// QApp.cpp: 定义动态链接库的实现
//

#include "TianLi.TruthEye.h"
//3rd
//#include <fmt>
// qt
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QTextCodec>
#include <QTranslator>
#include <QFile>
#include <QIcon>
#include <QFileInfo>
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
static std::thread*  g_thread = nullptr;
static void QApplicationCreate()
{
    // 由于Qt的一些特性，在创建QWidget之前，必须先创建QApplication
    // 但是，由于QApplication的构造函数中，会创建一个QDesktopWidget对象
    // 而QDesktopWidget对象的构造函数中，会创建一个QWidget对象
    // 因此，这里需要先创建一个QApplication对象，然后再创建一个QDesktopWidget对象
    // 最后再创建一个QWidget对象

    // 创建QApplication对象
    int argc = 1;
    TCHAR modulePath[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, modulePath, MAX_PATH);
    char* argv[] = { (char*)modulePath };
    g_app = new QApplication(argc, argv);
    // 创建QWidget对象
    QWidget widget;
    // 显示QWidget对象
    widget.show();
    g_app->exec();
}

void CreateApp()
{
    g_thread = new std::thread(QApplicationCreate);
}

void DestroyApp()
{
    g_app->exit(0);
    g_thread->join();
}

int RunApp()
{
return 0;
}

void SetJsonParams(const char* json)
{
    return  void();
}
