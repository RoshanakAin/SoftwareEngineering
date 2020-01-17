using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsAppSudoku
{
    public partial class Form1 : Form
    {
        public static ArrayList sudoku_table = new ArrayList();
        public static int flag = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            sudoku_table.Add(textBox11);
            sudoku_table.Add(textBox12);
            sudoku_table.Add(textBox13);
            sudoku_table.Add(textBox14);
            sudoku_table.Add(textBox15);
            sudoku_table.Add(textBox16);
            sudoku_table.Add(textBox17);
            sudoku_table.Add(textBox18);
            sudoku_table.Add(textBox19);
            sudoku_table.Add(textBox21);
            sudoku_table.Add(textBox22);
            sudoku_table.Add(textBox23);
            sudoku_table.Add(textBox24);
            sudoku_table.Add(textBox25);
            sudoku_table.Add(textBox26);
            sudoku_table.Add(textBox27);
            sudoku_table.Add(textBox28);
            sudoku_table.Add(textBox29);
            sudoku_table.Add(textBox31);
            sudoku_table.Add(textBox32);
            sudoku_table.Add(textBox33);
            sudoku_table.Add(textBox34);
            sudoku_table.Add(textBox35);
            sudoku_table.Add(textBox36);
            sudoku_table.Add(textBox37);
            sudoku_table.Add(textBox38);
            sudoku_table.Add(textBox39);
            sudoku_table.Add(textBox41);
            sudoku_table.Add(textBox42);
            sudoku_table.Add(textBox43);
            sudoku_table.Add(textBox44);
            sudoku_table.Add(textBox45);
            sudoku_table.Add(textBox46);
            sudoku_table.Add(textBox47);
            sudoku_table.Add(textBox48);
            sudoku_table.Add(textBox49);
            sudoku_table.Add(textBox51);
            sudoku_table.Add(textBox52);
            sudoku_table.Add(textBox53);
            sudoku_table.Add(textBox54);
            sudoku_table.Add(textBox55);
            sudoku_table.Add(textBox56);
            sudoku_table.Add(textBox57);
            sudoku_table.Add(textBox58);
            sudoku_table.Add(textBox59);
            sudoku_table.Add(textBox61);
            sudoku_table.Add(textBox62);
            sudoku_table.Add(textBox63);
            sudoku_table.Add(textBox64);
            sudoku_table.Add(textBox65);
            sudoku_table.Add(textBox66);
            sudoku_table.Add(textBox67);
            sudoku_table.Add(textBox68);
            sudoku_table.Add(textBox69);
            sudoku_table.Add(textBox71);
            sudoku_table.Add(textBox72);
            sudoku_table.Add(textBox73);
            sudoku_table.Add(textBox74);
            sudoku_table.Add(textBox75);
            sudoku_table.Add(textBox76);
            sudoku_table.Add(textBox77);
            sudoku_table.Add(textBox78);
            sudoku_table.Add(textBox79);
            sudoku_table.Add(textBox81);
            sudoku_table.Add(textBox82);
            sudoku_table.Add(textBox83);
            sudoku_table.Add(textBox84);
            sudoku_table.Add(textBox85);
            sudoku_table.Add(textBox86);
            sudoku_table.Add(textBox87);
            sudoku_table.Add(textBox88);
            sudoku_table.Add(textBox89);
            sudoku_table.Add(textBox91);
            sudoku_table.Add(textBox92);
            sudoku_table.Add(textBox93);
            sudoku_table.Add(textBox94);
            sudoku_table.Add(textBox95);
            sudoku_table.Add(textBox96);
            sudoku_table.Add(textBox97);
            sudoku_table.Add(textBox98);
            sudoku_table.Add(textBox99);
        }

        public static int count = 0;
        static void FillGrid()
        { 
            //从文件中读取数独题目
            StreamReader sr = new StreamReader("puzzle.txt");
            for (int i = 0; i < 10 * count; i++)
            {
                string lineadd = sr.ReadLine();
            }

            //填入数字
            for (int i = 0; i < 9; i++)
            {
                string line = sr.ReadLine();
                for (int k = 0; k < 9; k++)
                {
                    TextBox t = sudoku_table[i * 9 + k] as TextBox;
                    if (line[2 * k] == '0')//挖空
                    {
                        t.Text = "";
                        t.ReadOnly = false;
                    }
                    else
                    {
                        t.Text = line[2 * k].ToString();
                        t.ReadOnly = true;
                    }
                }
                count++;
            }
        }

        static void JudgeSubmit()
        { 
            //将每一次输入的信息存入字符数组中
            string[] buffer;
            buffer = new string[10];

            for (int i = 0; i < 9; i++)
            {
                buffer[i] = "";
                for (int k = 0; k < 9; k++)
                {
                    TextBox t = sudoku_table[i * 9 + k] as TextBox;
                    if (t.Text == "")
                    {
                        MessageBox.Show("请作答完毕", "提示");
                        return;
                    }
                    else buffer[i] += t.Text;
                }
            }

            int[] check_row = { 0, 3, 6, 27, 30, 33, 54, 57, 60 };
            int[] check_plus = { 0, 1, 2, 9, 10, 11, 18, 19, 20 };

            for (int i = 0; i < 9; i++)
            {//检查输入的数独是否合法
                int[] ROW = new int[10]; //每一行计数
                int[] COL = new int[10]; //每一列计数
                int[] GONG = new int[10]; //每一宫计数

                for (int j = 0; j < 9; j++)
                {//初始化
                    ROW[j] = 0;
                    COL[j] = 0;
                    GONG[j] = 0;
                }

                for (int j = 0; j < 9; j++)//记录数字出现次数
                {
                    ROW[buffer[i][j] - '0']++;
                    COL[buffer[j][i] - '0']++;
                    int a1 = (check_row[i] + check_plus[j]) / 9;
                    int a2 = (check_row[i] + check_plus[j]) % 9;
                    GONG[buffer[a1][a2] - '0']++;
                }

                for (int j = 1; j <= 9; j++)
                {
                    if (ROW[j] != 1 || COL[j] != 1 || GONG[j] != 1)
                    { 
                        //某一个数字未出现或出现了不止一次,报错
                        MessageBox.Show("作答错误", "提示");
                        return;
                    }
                }
            }
            MessageBox.Show("作答正确", "提示");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            JudgeSubmit();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            FillGrid();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
