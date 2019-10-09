namespace Window
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.InputWord = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.ChoiceTxtFile = new System.Windows.Forms.OpenFileDialog();
            this.Btn_AddFile = new System.Windows.Forms.Button();
            this.Btn_ClearDB = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Label_Time = new System.Windows.Forms.Label();
            this.QuaryResult = new System.Windows.Forms.RichTextBox();
            this.Label_Number = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.Txt_ResultCount = new System.Windows.Forms.TextBox();
            this.Label_WordCount = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // InputWord
            // 
            this.InputWord.Location = new System.Drawing.Point(12, 43);
            this.InputWord.Name = "InputWord";
            this.InputWord.Size = new System.Drawing.Size(222, 21);
            this.InputWord.TabIndex = 0;
            this.InputWord.TextChanged += new System.EventHandler(this.InputWord_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(89, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "输入查询字符：";
            // 
            // ChoiceTxtFile
            // 
            this.ChoiceTxtFile.FileName = "选择要加入索引的文件";
            this.ChoiceTxtFile.Filter = "文本文件|*.txt|逗号分隔文件|*.csv";
            this.ChoiceTxtFile.Multiselect = true;
            this.ChoiceTxtFile.FileOk += new System.ComponentModel.CancelEventHandler(this.ChoiceTxtFile_FileOk);
            // 
            // Btn_AddFile
            // 
            this.Btn_AddFile.Location = new System.Drawing.Point(24, 300);
            this.Btn_AddFile.Name = "Btn_AddFile";
            this.Btn_AddFile.Size = new System.Drawing.Size(75, 23);
            this.Btn_AddFile.TabIndex = 3;
            this.Btn_AddFile.Text = "添加新文件";
            this.Btn_AddFile.UseVisualStyleBackColor = true;
            this.Btn_AddFile.Click += new System.EventHandler(this.Btn_AddFile_Click);
            // 
            // Btn_ClearDB
            // 
            this.Btn_ClearDB.Location = new System.Drawing.Point(137, 300);
            this.Btn_ClearDB.Name = "Btn_ClearDB";
            this.Btn_ClearDB.Size = new System.Drawing.Size(75, 23);
            this.Btn_ClearDB.TabIndex = 4;
            this.Btn_ClearDB.Text = "清空索引库";
            this.Btn_ClearDB.UseVisualStyleBackColor = true;
            this.Btn_ClearDB.Click += new System.EventHandler(this.Btn_ClearDB_Click);
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(10, 82);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 23);
            this.label2.TabIndex = 5;
            this.label2.Text = "查询用时：";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(213, 82);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(21, 23);
            this.label3.TabIndex = 6;
            this.label3.Text = "秒";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // Label_Time
            // 
            this.Label_Time.Location = new System.Drawing.Point(84, 82);
            this.Label_Time.Name = "Label_Time";
            this.Label_Time.Size = new System.Drawing.Size(123, 23);
            this.Label_Time.TabIndex = 7;
            this.Label_Time.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // QuaryResult
            // 
            this.QuaryResult.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.QuaryResult.Location = new System.Drawing.Point(240, 15);
            this.QuaryResult.Name = "QuaryResult";
            this.QuaryResult.ReadOnly = true;
            this.QuaryResult.Size = new System.Drawing.Size(412, 308);
            this.QuaryResult.TabIndex = 8;
            this.QuaryResult.Text = "";
            // 
            // Label_Number
            // 
            this.Label_Number.Location = new System.Drawing.Point(84, 105);
            this.Label_Number.Name = "Label_Number";
            this.Label_Number.Size = new System.Drawing.Size(123, 23);
            this.Label_Number.TabIndex = 11;
            this.Label_Number.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(213, 105);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(21, 23);
            this.label5.TabIndex = 10;
            this.label5.Text = "个";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(10, 105);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(89, 23);
            this.label6.TabIndex = 9;
            this.label6.Text = "查询到结果：";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(213, 128);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(21, 23);
            this.label7.TabIndex = 13;
            this.label7.Text = "个";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label8
            // 
            this.label8.Location = new System.Drawing.Point(10, 128);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(89, 23);
            this.label8.TabIndex = 12;
            this.label8.Text = "显示结果：";
            this.label8.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // Txt_ResultCount
            // 
            this.Txt_ResultCount.Location = new System.Drawing.Point(86, 129);
            this.Txt_ResultCount.Name = "Txt_ResultCount";
            this.Txt_ResultCount.Size = new System.Drawing.Size(121, 21);
            this.Txt_ResultCount.TabIndex = 14;
            this.Txt_ResultCount.TextChanged += new System.EventHandler(this.Txt_ResultCount_TextChanged);
            // 
            // Label_WordCount
            // 
            this.Label_WordCount.Location = new System.Drawing.Point(84, 274);
            this.Label_WordCount.Name = "Label_WordCount";
            this.Label_WordCount.Size = new System.Drawing.Size(123, 23);
            this.Label_WordCount.TabIndex = 17;
            this.Label_WordCount.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label9
            // 
            this.label9.Location = new System.Drawing.Point(213, 274);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(21, 23);
            this.label9.TabIndex = 16;
            this.label9.Text = "词";
            this.label9.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label10
            // 
            this.label10.Location = new System.Drawing.Point(10, 274);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(89, 23);
            this.label10.TabIndex = 15;
            this.label10.Text = "当前词库：";
            this.label10.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(664, 336);
            this.Controls.Add(this.Label_WordCount);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.Txt_ResultCount);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.Label_Number);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.QuaryResult);
            this.Controls.Add(this.Label_Time);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.Btn_ClearDB);
            this.Controls.Add(this.Btn_AddFile);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.InputWord);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Form1";
            this.Text = "查询工具";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox InputWord;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.OpenFileDialog ChoiceTxtFile;
        private System.Windows.Forms.Button Btn_AddFile;
        private System.Windows.Forms.Button Btn_ClearDB;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label Label_Time;
        private System.Windows.Forms.RichTextBox QuaryResult;
        private System.Windows.Forms.Label Label_Number;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox Txt_ResultCount;
        private System.Windows.Forms.Label Label_WordCount;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
    }
}

