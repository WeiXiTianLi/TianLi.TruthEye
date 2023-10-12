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
#ifdef TIANLI_TRUTHEYE_IMPL
    TIANLI_TRUTHEYE_API bool TianLiTruthEye_Impl_Check_Update();
    TIANLI_TRUTHEYE_API bool TianLiTruthEye_Impl_Get_Update_Info(char *json_buff, unsigned int buff_size);
    TIANLI_TRUTHEYE_API bool TianLiTruthEye_Impl_Checkout_Version(char *json_buff, unsigned int buff_size);
    TIANLI_TRUTHEYE_API bool TianLiTruthEye_Impl_Auto_Checkout_Version(char *json_buff, unsigned int buff_size,
                                                                       void (*download_progress)(int, int),
                                                                       void (*install_progress)(int, int));
    TIANLI_TRUTHEYE_API bool TianLiTruthEye_Impl_Get_Version(char *json_buff, unsigned int buff_size);
    TIANLI_TRUTHEYE_API void TianLiTruthEye_Impl_Async_Download(void (*progress)(int, int));
    TIANLI_TRUTHEYE_API void TianLiTruthEye_Impl_Async_Install(void (*progress)(int, int));
    TIANLI_TRUTHEYE_API bool TianLiTruthEye_Impl_Load(const char *path = nullptr, bool is_reload = false);
    TIANLI_TRUTHEYE_API bool TianLiTruthEye_Impl_Load_Version(const char *version);
    TIANLI_TRUTHEYE_API bool TianLiTruthEye_Impl_Free();
#endif
    TIANLI_TRUTHEYE_API void TianLiTruthEye_Version(const char *version_buff, unsigned int buff_size);
    TIANLI_TRUTHEYE_API void TianLiTruthEye_CreateWindow();
    TIANLI_TRUTHEYE_API void TianLiTruthEye_DestroyWindow();
    TIANLI_TRUTHEYE_API void TianLiTruthEye_ShowWindow();
    TIANLI_TRUTHEYE_API void TianLiTruthEye_HideWindow();
    TIANLI_TRUTHEYE_API void TianLiTruthEye_SetJsonParams(const char *json_buff, unsigned int buff_size);
    TIANLI_TRUTHEYE_API void TianLiTruthEye_RegisterCallback(const char *callback_name, void (*callback)(const char *json_buff, unsigned int buff_size));
#ifdef __cplusplus
}
#endif
