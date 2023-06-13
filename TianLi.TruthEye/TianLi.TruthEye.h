// QApp.h: 动态链接库的主头文件。
// 或项目特定的包含文件。

#pragma once
#ifdef TIANLI_TRUTHEYE_EXPORTS
#define TIANLI_TRUTHEYE_API __declspec(dllexport)
#else
#define TIANLI_TRUTHEYE_API __declspec(dllimport)
#endif

#if defined(_WIN32) || defined(_WIN64)
#define QAPP_OS_WIN
#elif defined(__linux__)
#define QAPP_OS_LINUX
#elif defined(__APPLE__)
#define QAPP_OS_MAC
#endif

#ifdef __cplusplus
extern "C" {
#endif

    TIANLI_TRUTHEYE_API void CreateApp();
    TIANLI_TRUTHEYE_API void DestroyApp();
    TIANLI_TRUTHEYE_API int RunApp();
    TIANLI_TRUTHEYE_API void SetJsonParams(const char* json);

#ifdef __cplusplus
}
#endif




