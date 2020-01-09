/*
该文件处于未完成状态，仅提供伪代码形式思路和大致框架；
包含生成和求解两个模块。
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>
#include <algorithm>

using namespace std;

int n;//需要生成的数独矩阵个数
char grid[10][10];//生成的数独矩阵
char buffer[170000000];//读矩阵到文件的缓冲
int buffer_cursor = 0;//buffer数组的当前索引
ofstream OutCreateFile("sudoku.txt");//生成矩阵写入的文件
char permutation[15] = { '1','2','3','4','5','6','7','9' };//生成的初始排列
char move1[10][5] = { "036","063" };//矩阵每三行的移动规则
char move2[10][5] = { "258","285","528","582","852","825" };//移动矩阵4-6行
char move3[10][5] = { "147","174","417","471","714","741" };//移动矩阵7-9行

void CreateSudoku(int n)
{
	//生成数独具体代码
	int cnt_create = 0;//已经生成的数独数目
					   //循环生成n个矩阵
	while (cnt_create < n)
	{
		permutation[8] = '8';//学号位固定
							 //根据移动方式共有72种不同的排列
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				for (int k = 0; k < 6; ++k)
				{
					//每三行平移构建矩阵
					//1-3行
					for (int row = 0; row < 3; ++row)
					{
						//生成该行首字母
						int tmp = (8 + move1[i][row] - '0') % 9;//生成平移后位置，因为学号位在末尾，故+8
						buffer[buffer_cursor] = permutation[tmp];//存入缓冲区
						buffer_cursor++;

						//该行按数字和空格存入，m为该行字符计数
						for (int m = 1; m <= 16; m++)
						{
							buffer[buffer_cursor++] = ' ';//存入空格
							m++;
							int tmp = (8 - (m / 2) + move1[i][row] - '0') % 9;//生成当前处理数平移后位置
							buffer[buffer_cursor++] = permutation[tmp];
						}
						buffer[buffer_cursor++] = '\n';//换行
					}

					//4-6行
					for (int row = 0; row < 3; ++row)
					{
						//生成该行首字母
						int tmp = (8 + move2[j][row] - '0') % 9;//生成平移后位置，因为学号位在末尾，故+8
						buffer[buffer_cursor] = permutation[tmp];//存入缓冲区
						buffer_cursor++;

						//该行按数字和空格存入，m为该行字符计数
						for (int m = 1; m <= 16; m++)
						{
							buffer[buffer_cursor++] = ' ';//存入空格
							m++;
							int tmp = (8 - (m / 2) + move1[i][row] - '0') % 9;//生成当前处理数平移后位置
							buffer[buffer_cursor++] = permutation[tmp];
						}
						buffer[buffer_cursor++] = '\n';//换行
					}

					//7-9行
					for (int row = 0; row < 3; ++row)
					{
						//生成该行首字母
						int tmp = (8 + move3[k][row] - '0') % 9;//生成平移后位置，因为学号位在末尾，故+8
						buffer[buffer_cursor] = permutation[tmp];//存入缓冲区
						buffer_cursor++;

						//该行按数字和空格存入，m为该行字符计数
						for (int m = 1; m <= 16; m++)
						{
							buffer[buffer_cursor++] = ' ';//存入空格
							m++;
							int tmp = (8 - (m / 2) + move1[i][row] - '0') % 9;//生成当前处理数平移后位置
							buffer[buffer_cursor++] = permutation[tmp];
						}
						buffer[buffer_cursor++] = '\n';//换行
					}

					buffer[buffer_cursor++] = '\n';//两个不同矩阵间空一行

					cnt_create++;//生成矩阵计数+1
					if (cnt_create == n)
						return;
				}
			}
		}

		//按字典序生成全排列,但学号位不动
		next_permutation(permutation, permutation + 8);
	}
}

void MatrixToList()
{
	//将文件数据转化为DLX十字链表
}

void DLX()
{
	//DLX算法求解
}

void ListToFile()
{
	//得到的解写入文件
}

void SolveSudoku(string FilePath)//DLX算法尝试
{
	ifstream ReadFile(FilePath);
	if (!ReadFile.is_open())
	{
		cout << "Path Invalid！" << endl;
		return;
	}
	//求解数独具体代码
	MatrixToList();

	DLX();

	ListToFile();
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		//提示参数个数错误
		cout << "Please input 3 parameters" << endl;
		return 0;
	}

	if (strcmp(argv[1], "-c") == 0)
	{//生成数独终局
		n = atoi(argv[2]);//限制生成数独终局的个数范围
		if (n < 1 || n>1000000)
		{
			cout << "Number is illegal" << endl;
			return 0;
		}
		buffer_cursor = 0;
		memset(buffer, 0, sizeof(buffer));
		CreateSudoku(n);
		//输出到文件 
		OutCreateFile << buffer;
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		//求解数独
		SolveSudoku(argv[2]);
	}
	else
	{
		//提示参数内容错误
		cout << "Command illegal" << endl;
	}

	return 0;
}
