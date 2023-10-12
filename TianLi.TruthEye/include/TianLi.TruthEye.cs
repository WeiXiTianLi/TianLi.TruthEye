using System.Runtime.InteropServices;

/// <summary>
/// TianLi.TruthEye 的 C API
/// </summary>
namespace TianLi
{
    public class TruthEyeInface
    {
        public delegate void Progress_Type(int current, int total);
        [DllImport("TianLi.TruthEye.Inface.dll", EntryPoint = "TianLiTruthEye_Impl_Async_Download", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ImplAsyncDownload(Progress_Type progress);

        [DllImport("TianLi.TruthEye.Inface.dll", EntryPoint = "TianLiTruthEye_Impl_Load", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Load(byte[] path = null, bool is_release = false);

        [DllImport("TianLi.TruthEye.Inface.dll", EntryPoint = "TianLiTruthEye_Impl_Free", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Free();

        [DllImport("TianLi.TruthEye.Inface.dll", EntryPoint = "TianLiTruthEye_CreateWindow", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void CreateWindow();

        [DllImport("TianLi.TruthEye.Inface.dll", EntryPoint = "TianLiTruthEye_DestroyWindow", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void DestroyWindow();

        [DllImport("TianLi.TruthEye.Inface.dll", EntryPoint = "TianLiTruthEye_ShowWindow", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ShowWindow();

        [DllImport("TianLi.TruthEye.Inface.dll", EntryPoint = "TianLiTruthEye_HideWindow", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void HideWindow();

        [DllImport("TianLi.TruthEye.Inface.dll", EntryPoint = "TianLiTruthEye_SetJsonParams", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetJsonParams(byte[] json_buff, int buff_size);
    }

    public class TruthEye
    {
        [DllImport("TianLi.TruthEye.dll", EntryPoint = "TianLiTruthEye_CreateWindow", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void CreateWindow();

        [DllImport("TianLi.TruthEye.dll", EntryPoint = "TianLiTruthEye_DestroyWindow", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void DestroyWindow();

        [DllImport("TianLi.TruthEye.dll", EntryPoint = "TianLiTruthEye_ShowWindow", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ShowWindow();

        [DllImport("TianLi.TruthEye.dll", EntryPoint = "TianLiTruthEye_HideWindow", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void HideWindow();

        [DllImport("TianLi.TruthEye.dll", EntryPoint = "TianLiTruthEye_SetJsonParams", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetJsonParams(byte[] json_buff, int buff_size);
    }
}
