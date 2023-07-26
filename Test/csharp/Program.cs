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
        struct point
        {
            public int x;
            public int y;
        };
        struct obj
        {
            public string name;
            public string url;
            public point[] points;
        };
        static string format_json(obj[] objs)
        {
            string json_head = "{\"version\": \"1.0.0\",\"type\" : \"update\",\"content\" : [";
            string json_tail = "]}";
            string json_body = "";
            for (int i = 0; i < objs.Length; i++)
            {
                json_body += "{\"name\": \"" + objs[i].name + "\",\"url\" : \"" + objs[i].url + "\",\"points\" : [";
                for (int j = 0; j < objs[i].points.Length; j++)
                {
                    json_body += "{\"x\": " + objs[i].points[j].x + ",\"y\" : " + objs[i].points[j].y + "}";
                    if (j != objs[i].points.Length - 1)
                    {
                        json_body += ",";
                    }
                }
                json_body += "]}";
                if (i != objs.Length - 1)
                {
                    json_body += ",";
                }
            }
            return json_head + json_body + json_tail;
        }
        // main function
        static void Main(string[] args)
        {
            // call
            TruthEye.CreateWindow();
            TruthEye.ShowWindow();



            obj[] objs = new obj[2];
            objs[0].name = "风晶蝶";
            objs[0].url = "http://assets.yuanshen.site/icons/59.png";
            objs[0].points = new point[2];
            objs[0].points[0].x = 10;
            objs[0].points[0].y = 10;
            objs[0].points[1].x = 12;
            objs[0].points[1].y = 12;
            objs[1].name = "宝箱";
            objs[1].url = "http://assets.yuanshen.site/icons/59.png";
            objs[1].points = new point[1];
            objs[1].points[0].x = 20;
            objs[1].points[0].y = 30;

            for (int i = 0; i < 10; i++)
            {
                objs[0].points[0].x++;
                string json = format_json(objs);
                byte[] json_buff = System.Text.Encoding.Default.GetBytes(json);
                TruthEye.SetJsonParams(json_buff, json_buff.Length);
                System.Threading.Thread.Sleep(50);
                Console.WriteLine(json);
            }




            // wait
            //Console.ReadKey();

            // wait for 5 seconds
            System.Threading.Thread.Sleep(5000);







            TruthEye.HideWindow();
            TruthEye.DestroyWindow();
            // return
        }
    }
}