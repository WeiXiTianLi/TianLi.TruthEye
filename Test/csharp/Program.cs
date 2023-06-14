// using some lib
using System;
using System.Drawing;
using TianLi;

// namespace
namespace TianLiTruthEye.csharp.test
{
    // class
    class Program
    {
        // main function
        static void Main(string[] args)
        {
            // print
            Console.WriteLine("Hello World!");
            // call
            TruthEye.TianLiTruthEye_CreateWindow();
            TruthEye.TianLiTruthEye_ShowWindow();
            // wait
            Console.ReadKey();

            // read local image
            Bitmap bitmap = new Bitmap("C:\\Users\\Administrator\\Desktop\\test.bmp");

            char[] image_buff = new char[bitmap.Width * bitmap.Height * 3];
            // copy image data
            for (int i = 0; i < bitmap.Width; i++)
            {
                for (int j = 0; j < bitmap.Height; j++)
                {
                    Color color = bitmap.GetPixel(i, j);
                    image_buff[(i + j * bitmap.Width) * 3 + 0] = (char)color.R;
                    image_buff[(i + j * bitmap.Width) * 3 + 1] = (char)color.G;
                    image_buff[(i + j * bitmap.Width) * 3 + 2] = (char)color.B;
                }
            }

            // call
            //TruthEye.TianLiTruthEye_SetImage(image_buff, bitmap.Width, bitmap.Height);

            

            


            TruthEye.TianLiTruthEye_HideWindow();
            TruthEye.TianLiTruthEye_DestroyWindow();
            // return
        }
    }
}