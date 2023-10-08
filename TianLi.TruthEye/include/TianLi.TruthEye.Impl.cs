using Sirenix.Utilities;
using System;
using System.Reflection;
using System.Runtime.InteropServices;
using UnityEngine;

/// <summary>
/// TianLi.TruthEye 的 C API
/// </summary>
namespace TianLi
{
    public class TruthEyeApis
    {
        public delegate bool ImplLoad_Type(byte[] path = null, bool isReload = false);
        public delegate bool ImplLoadVersion_Type(byte[] version);
        public delegate bool ImplFree_Type();
        public delegate bool CreateWindow_Type();
        public delegate bool DestroyWindow_Type();
        public delegate bool ShowWindow_Type();
        public delegate bool HideWindow_Type();
        public delegate bool SetJsonParams_Type(byte[] json_buff, int buff_size);

        public IntPtr TianLiTruthEye_Impl_Load_Func = IntPtr.Zero;
        public IntPtr TianLiTruthEye_Impl_Load_Version_Func = IntPtr.Zero;
        public IntPtr TianLiTruthEye_Impl_Free_Func = IntPtr.Zero;
        public IntPtr TianLiTruthEye_CreateWindow_Func = IntPtr.Zero;
        public IntPtr TianLiTruthEye_DestroyWindow_Func = IntPtr.Zero;
        public IntPtr TianLiTruthEye_ShowWindow_Func = IntPtr.Zero;
        public IntPtr TianLiTruthEye_HideWindow_Func = IntPtr.Zero;
        public IntPtr TianLiTruthEye_SetJsonParams_Func = IntPtr.Zero;
        public bool IsLoad = false;

        private bool getFuncName(string fieldName, ref string funcName)
        {
            if (fieldName.Contains("_") == false) return false;
            if (fieldName.Substring(fieldName.Length - 4, 4) != "Func") return false;
            funcName = fieldName.Substring(0, fieldName.Length - 5);
            return true;
        }
        public delegate IntPtr GetAddress(IntPtr lib, String funcName);
        public bool LoadApis(IntPtr libPtr, GetAddress getAddr)
        {
            if (libPtr == IntPtr.Zero) return false;
            // 获取apis类的成员变量列表
            FieldInfo[] fields = GetType().GetFields();
            foreach (FieldInfo field in fields)
            {
                string name = "";
                if (!getFuncName(field.Name, ref name)) continue;
                IntPtr funcPtr = getAddr(libPtr, name);
                if (funcPtr == IntPtr.Zero) return false;
                field.SetValue(this, funcPtr);
            }
            IsLoad = true;
            return true;
        }

        public bool FreeApis(IntPtr libPtr)
        {
            if (libPtr != IntPtr.Zero) return false;
            // 获取apis类的成员变量列表
            FieldInfo[] fields = GetType().GetFields();
            foreach (FieldInfo field in fields)
            {
                string name = "";
                if (!getFuncName(field.Name, ref name)) continue;
                IntPtr funcPtr = (IntPtr)field.GetValue(this);
                field.SetValue(this, IntPtr.Zero);
            }
            IsLoad = false;
            return true;
        }

        public bool ImplLoad(byte[] path = null, bool isReload = false)
        {
            if (TianLiTruthEye_Impl_Load_Func == IntPtr.Zero) return false;
            ImplLoad_Type func = (ImplLoad_Type)Marshal.GetDelegateForFunctionPointer(TianLiTruthEye_Impl_Load_Func, typeof(ImplLoad_Type));
            return func(path, isReload);
        }

        public bool ImplLoadVersion(byte[] version)
        {
            if (TianLiTruthEye_Impl_Load_Version_Func == IntPtr.Zero) return false;
            ImplLoadVersion_Type func = (ImplLoadVersion_Type)Marshal.GetDelegateForFunctionPointer(TianLiTruthEye_Impl_Load_Version_Func, typeof(ImplLoadVersion_Type));
            return func(version);
        }

        public bool ImplFree()
        {
            if (TianLiTruthEye_Impl_Free_Func == IntPtr.Zero) return false;
            ImplFree_Type func = (ImplFree_Type)Marshal.GetDelegateForFunctionPointer(TianLiTruthEye_Impl_Free_Func, typeof(ImplFree_Type));
            return func();
        }

        public bool CreateWindow()
        {
            if (TianLiTruthEye_CreateWindow_Func == IntPtr.Zero) return false;
            CreateWindow_Type func = (CreateWindow_Type)Marshal.GetDelegateForFunctionPointer(TianLiTruthEye_CreateWindow_Func, typeof(CreateWindow_Type));
            return func();
        }

        public bool DestroyWindow()
        {
            if (TianLiTruthEye_DestroyWindow_Func == IntPtr.Zero) return false;
            DestroyWindow_Type func = (DestroyWindow_Type)Marshal.GetDelegateForFunctionPointer(TianLiTruthEye_DestroyWindow_Func, typeof(DestroyWindow_Type));
            return func();
        }

        public bool ShowWindow()
        {
            if (TianLiTruthEye_ShowWindow_Func == IntPtr.Zero) return false;
            ShowWindow_Type func = (ShowWindow_Type)Marshal.GetDelegateForFunctionPointer(TianLiTruthEye_ShowWindow_Func, typeof(ShowWindow_Type));
            return func();
        }

        public bool HideWindow()
        {
            if (TianLiTruthEye_HideWindow_Func == IntPtr.Zero) return false;
            HideWindow_Type func = (HideWindow_Type)Marshal.GetDelegateForFunctionPointer(TianLiTruthEye_HideWindow_Func, typeof(HideWindow_Type));
            return func();
        }

        public bool SetJsonParams(byte[] json_buff, int buff_size)
        {
            if (TianLiTruthEye_SetJsonParams_Func == IntPtr.Zero) return false;
            SetJsonParams_Type func = (SetJsonParams_Type)Marshal.GetDelegateForFunctionPointer(TianLiTruthEye_SetJsonParams_Func, typeof(SetJsonParams_Type));
            return func(json_buff, buff_size);
        }
    }

    public class TruthEyeLibrary
    {
        static public string LibPath = "TianLi.TruthEye.Inface.dll";
        static public IntPtr LibPtr = IntPtr.Zero;
        static public TruthEyeApis Apis = new TruthEyeApis();
        public bool IsLoaded()
        {
            return Apis.IsLoad;
        }
        public bool Load(string libPath)
        {
            LibPath = libPath;
            if (LibPtr != IntPtr.Zero) return false;
            LibPtr = LoadLibraryExW(LibPath, IntPtr.Zero, LoadLibraryFlags.LOAD_WITH_ALTERED_SEARCH_PATH);
            if (LibPtr == IntPtr.Zero) return false;
            return Apis.LoadApis(LibPtr, GetProcAddress);
        }

        public bool Free()
        {
            if (LibPtr == IntPtr.Zero) return false;
            bool ret = FreeLibrary(LibPtr);
            if (ret) LibPtr = IntPtr.Zero;
            return Apis.FreeApis(LibPtr);
        }

        public bool ImplLoad(bool isReload = false)
        {
            return Apis.ImplLoad(isReload);
        }

        public bool ImplLoadVersion(string version)
        {
            byte[] version_buff = System.Text.Encoding.Default.GetBytes(version);
            return Apis.ImplLoadVersion(version_buff);
        }

        public bool ImplFree()
        {
            return Apis.ImplFree();
        }

        public bool CreateWindow()
        {
            return Apis.CreateWindow();
        }

        public bool DestroyWindow()
        {
            return Apis.DestroyWindow();
        }

        public bool ShowWindow()
        {
            return Apis.ShowWindow();
        }

        public bool HideWindow()
        {
            return Apis.HideWindow();
        }

        public bool SetJsonParams(string json)
        {
            byte[] json_buff = System.Text.Encoding.Default.GetBytes(json);
            return Apis.SetJsonParams(json_buff, json_buff.Length);
        }

        [DllImport("kernel32.dll")]
        public static extern IntPtr LoadLibraryW(string path);

        [System.Flags]
        public enum LoadLibraryFlags : uint
        {
            DONT_RESOLVE_DLL_REFERENCES = 0x00000001,
            LOAD_IGNORE_CODE_AUTHZ_LEVEL = 0x00000010,
            LOAD_LIBRARY_AS_DATAFILE = 0x00000002,
            LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE = 0x00000040,
            LOAD_LIBRARY_AS_IMAGE_RESOURCE = 0x00000020,
            LOAD_WITH_ALTERED_SEARCH_PATH = 0x00000008,
            LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR = 0x00000100,
            LOAD_LIBRARY_SEARCH_SYSTEM32 = 0x00000800,
            LOAD_LIBRARY_SEARCH_DEFAULT_DIRS = 0x00001000
        }
        [DllImport("kernel32.dll", EntryPoint = "LoadLibraryExW", SetLastError = true)]
        public static extern System.IntPtr LoadLibraryExW([In()][MarshalAs(System.Runtime.InteropServices.UnmanagedType.LPWStr)] string lpLibFileName, System.IntPtr hFile, LoadLibraryFlags dwFlags);

        [DllImport("kernel32.dll")]
        public static extern bool FreeLibrary(IntPtr lib);

        [DllImport("kernel32.dll")]
        public static extern IntPtr GetProcAddress(IntPtr lib, String funcName);

    }

}