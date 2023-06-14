using System.Runtime.InteropServices;

/// <summary>
/// TianLi.TruthEye 的 C API
/// </summary>
namespace TianLi
{
    public class TruthEye
    {
        [DllImport("TianLi.TruthEye.dll")]
        public static extern void TianLiTruthEye_CreateWindow();

        [DllImport("TianLi.TruthEye.dll")]
        public static extern void TianLiTruthEye_DestroyWindow();

        [DllImport("TianLi.TruthEye.dll")]
        public static extern void TianLiTruthEye_ShowWindow();

        [DllImport("TianLi.TruthEye.dll")]
        public static extern void TianLiTruthEye_HideWindow();
    }
}
