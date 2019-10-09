using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using FQuaryList;
using System.IO;

namespace Window
{
    public partial class Form1 : Form
    {
        private FQuary q;
        private int pages;
        private int resultCount;
        private int quaryLen;
        public Form1()
        {
            InitializeComponent();

            q = new FQuary();
            resultCount = 10;
            quaryLen = 20;
            if(File.Exists("dic.idb"))
                q.DeSerialize("dic.idb");
        }

        private void InputWord_TextChanged(object sender, EventArgs e)
        {

            string quary = InputWord.Text.ToLower();
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();

            stopwatch.Start();
            Data d = q.QuaryWord(quary);
            stopwatch.Stop();

            Label_Time.Text = stopwatch.Elapsed.TotalSeconds.ToString("F8");
            Label_Number.Text = d?.BlockCounts().ToString();
            Txt_ResultCount.Text = resultCount.ToString();

            QuaryResult.Clear();


            if (d != null)
            {
                int c,count = 0;
                char ch;
                string str;
                int start = 0, begin = 0;

                foreach (var i in d.QuaryData())
                {
                    foreach (var j in i.Blocks)
                    {
                        using (StreamReader sr = new StreamReader(i.Page + ".txt"))
                        {
                            str = String.Empty;

                            for (c = 0; c < j - quary.Length - quaryLen; ++c)
                                sr.Read();

                            for (c = 0; c < (quaryLen << 1) + quary.Length; ++c)
                            {
                                ch = (char)(sr.Read());
                                if (c < quaryLen && ch == '\n')
                                {
                                    str = String.Empty;
                                    continue;
                                }
                                else if (c >= quaryLen + quary.Length && ch == '\r')
                                    break;
                                if (c == quaryLen)
                                    start = str.Length;
                                str += ch;
                            }
                            //设置表头
                            begin = QuaryResult.Text.Length;
                            QuaryResult.AppendText("Page " + i.Page + " :");
                            QuaryResult.Select(begin, 4);
                            QuaryResult.SelectionColor = Color.Blue;
                            //设置重点颜色
                            start += QuaryResult.Text.Length;
                            QuaryResult.AppendText(str + '\r');
                            QuaryResult.Select(start, quary.Length);
                            QuaryResult.SelectionColor = Color.Red;

                            count++;
                        }
                        if (count >= resultCount)
                            return;
                    }
                }
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            q.Serialize("dic.idb");

            using (StreamWriter sw = new StreamWriter("setting.ini"))
            {
                sw.Write(pages);
            }
        }

        private void Btn_AddFile_Click(object sender, EventArgs e)
        {
            ChoiceTxtFile.ShowDialog();
        }

        private void ChoiceTxtFile_FileOk(object sender, CancelEventArgs e)
        {
            foreach (var filename in ChoiceTxtFile.FileNames)
            {
                using (StreamReader sr = new StreamReader(filename))
                {
                    long count = 0;
                    char c;
                    string str = String.Empty;

                    while (!sr.EndOfStream)
                    {
                        c = (char)(sr.Read());
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
                        {
                            str += c;
                        }
                        else if (str != String.Empty)
                        {
                            q.AddWord(str.ToLower(), pages, (int)(count));
                            str = String.Empty;
                        }
                        count++;
                    }
                }
                File.Copy(filename, pages + ".txt");
                pages++;
            }
            UpdateWordCount();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            if (File.Exists("setting.ini"))
                using (StreamReader sr = new StreamReader("setting.ini"))
                {
                    pages = Convert.ToInt32(sr.ReadLine());
                }
            else
                pages = 0;
            UpdateWordCount();
        }

        private void Btn_ClearDB_Click(object sender, EventArgs e)
        {
            q.Dispose();
            q = new FQuary();

            int i = 0;
            while (i < pages)
            {
                if (File.Exists(i + ".txt"))
                    File.Delete(i + ".txt");
                i++;
            }
            pages = 0;
            UpdateWordCount();
        }

        private void Txt_ResultCount_TextChanged(object sender, EventArgs e)
        {
            try
            {
                resultCount = Convert.ToInt32(Txt_ResultCount.Text);
            }
            catch
            { }
        }

        private void UpdateWordCount()
        {
            Label_WordCount.Text = q.QuaryWordCount().ToString();
        }
    }
}
