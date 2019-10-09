using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FQuaryList;
using System.IO;
using System.Diagnostics;

namespace ConsoleTest
{
    class Program
    {
        static void Main(string[] args)
        {
            FQuary q = new FQuary();
            string str = "";
            char c;
            int count = 0;

            using (FileStream fs = File.OpenRead("test.txt"))
            {
                //StreamReader sr = new StreamReader(fs);
                //while (!sr.EndOfStream)
                //{
                //    c = (char)(sr.Read());
                //    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                //        str += c;
                //    else if (str != "")
                //    {
                //        q.AddWord(str, 1, count++);
                //        str = "";
                //    }
                //}

                q.DeSerialize("dic.txt");

                System.Diagnostics.Stopwatch stopwatch = new Stopwatch();

                stopwatch.Start();

                Data d = q.QuaryWord("the");

                stopwatch.Stop();


                Console.WriteLine(stopwatch.Elapsed.TotalSeconds);
                str = "";

                if(d != null)
                {
                    foreach(var i in d.QuaryData())
                    {
                        foreach (var j in i.Blocks)
                            Console.WriteLine(j);
                    }
                }
                else
                {
                    Console.WriteLine("???????");
                }

            }
        }
    }
}
