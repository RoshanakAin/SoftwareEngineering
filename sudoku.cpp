/*
该文件处于未完成状态，仅提供伪代码形式思路和大致框架；
包含生成和求解两个模块。
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>

using namespace std;

int n;//需要生成的数独矩阵个数
char grid[9][9];//生成的数独矩阵
char buffer[1000000];//读控制台的缓冲
ofstream OutCreateFile("../BIN/sudoku.txt");//生成矩阵写入的文件

void CreateSudoku(int n)
{
	//生成数独具体代码
}

void SolveSudoku()
{
	//求解数独具体代码
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
		CreateSudoku(n);
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		//求解数独
	}
	else
	{
		//提示参数内容错误
		cout << "Command illegal" << endl;
	}

	return 0;
}
