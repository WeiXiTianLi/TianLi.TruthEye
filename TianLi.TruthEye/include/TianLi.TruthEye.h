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
extern "C"
{
#endif

    TIANLI_TRUTHEYE_API void TianLiTruthEye_CreateWindow();
    TIANLI_TRUTHEYE_API void TianLiTruthEye_DestroyWindow();
    TIANLI_TRUTHEYE_API void TianLiTruthEye_ShowWindow();
    TIANLI_TRUTHEYE_API void TianLiTruthEye_HideWindow();
    TIANLI_TRUTHEYE_API void TianLiTruthEye_SetJsonParams(const char *json_buff, unsigned int buff_size);

#ifdef __cplusplus
}
#endif
