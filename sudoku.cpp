/*
该文件处于未完成状态，仅提供伪代码形式思路和大致框架；
包含生成和求解两个模块。
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>
#include <algorithm>

#define SetVisit 1
#define CancelVisit 0

using namespace std;

int n;//需要生成的数独矩阵个数
char grid[10][10];//数独矩阵
char buffer[170000000];//读矩阵到文件的缓冲
int buffer_cursor = 0;//buffer数组的当前索引
ofstream OutCreateFile;//生成矩阵写入的文件
ifstream PuzzleFile;//解决矩阵来自的文件
ofstream OutSolvedFile;//解决后的矩阵文件
char permutation[15] = { '1','2','3','4','5','6','7','9' };//生成的初始排列
char move1[10][5] = { "036","063" };//矩阵每三行的移动规则
char move2[10][5] = { "258","285","528","582","852","825" };//移动矩阵4-6行
char move3[10][5] = { "147","174","417","471","714","741" };//移动矩阵7-9行

int vis[3][10][10];
//第一维中0表示行、1表示列、2表示九宫格
//第二维中表示在第几个行、列或九宫格中
//第三维表示其中的某个数字，如果该数字被填入了，vis值置1，否则置0
bool is_found = false;//标识是否找到解

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

void SetVis(int row, int col, int num, int flag)
{
	//占用时flag为1，撤销占用时flag为0
	vis[0][row][num] = flag;//行
	vis[1][col][num] = flag;//列
	vis[2][row / 3 * 3 + col / 3][num] = flag;//九宫格
}

void SolveSingleSudoku(int row, int col)
{
	while (grid[row][col] != '0')//找到未填入的格子
	{
		if (col < 8)//横向推进
			col++;
		else
		{//纵向推进
			col = 0;
			row++;
		}

		if (row == 9)
		{
			//遍历完后已经无空格
			is_found = true;
			return;
		}
	}

	bool is_search = false;
	//遍历1-9
	for (int i = 1; i <= 9; i++)
	{
		//若未访问
		if (vis[0][row][i] == 0
			&& vis[1][col][i] == 0
			&& vis[2][row / 3 * 3 + col / 3][i] == 0)
		{
			cout << i << "可用" << endl;
			SetVis(row, col, i, SetVisit);//置占用 
			grid[row][col] = i + '0';
			is_search = true;
			//回溯
			SolveSingleSudoku(row, col);
		}

		if (is_search)//若一个点被搜索过 
		{
			is_search = false;
			if (is_found)//找到了即返回
				return;
			//重置
			SetVis(row, col, i, CancelVisit);
			grid[row][col] = '0';
		}

		cout << i << "不可用" << endl;
	}
}

void SolveSudoku(char* FilePath)//回溯算法
{
	PuzzleFile.open(FilePath);
	if (!PuzzleFile)
	{
		cout << "Path Invalid！" << endl;
		return;
	}
	//从文件载入矩阵
	//ifstream读到空格就截止
	char str[25];
	int LineCount = 0;
	while (PuzzleFile.getline(str, 20))
	{
		for (int i = 0; i <= 16; ++i)
		{
			if (i % 2 == 0)//为矩阵元素
			{
				grid[LineCount][i / 2] = str[i];
				SetVis(LineCount, i / 2, str[i] - '0', SetVisit);//置占用
			}
		}

		LineCount++;//换行
		if (LineCount == 9)//换新矩阵
		{
			is_found = false;
			SolveSingleSudoku(0, 0);//回溯解数独
									//写入缓冲
			for (int row = 0; row < 9; ++row)
			{
				for (int col = 0; col < 9; ++col)
				{
					if (col != 9)
					{
						buffer[buffer_cursor++] = grid[row][col];
						buffer[buffer_cursor++] = ' ';
					}
					else
					{
						buffer[buffer_cursor++] = grid[row][col];
					}
				}
				buffer[buffer_cursor++] = '\n';
			}
			//清除访问
			memset(vis, 0, sizeof(vis));
			LineCount = 0;
		}
	}

	PuzzleFile.close();
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
		//初始化缓冲区
		buffer_cursor = 0;
		memset(buffer, 0, sizeof(buffer));
		//生成终局
		CreateSudoku(n);
		//输出到文件
		OutCreateFile.open("sudoku.txt");
		OutCreateFile << buffer;
		OutCreateFile.close();
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		//初始化缓冲区
		buffer_cursor = 0;
		memset(buffer, 0, sizeof(buffer));
		memset(vis, 0, sizeof(vis));
		//求解数独
		SolveSudoku(argv[2]);
		//输出到文件
		OutSolvedFile.open("sudoku_s.txt");
		OutSolvedFile << buffer;
		OutSolvedFile.close();
	}
	else
	{
		//提示参数内容错误
		cout << "Command illegal" << endl;
	}

	return 0;
}
