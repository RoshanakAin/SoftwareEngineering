/*
该文件处于未完成状态，仅提供伪代码形式思路和大致框架；
包含生成和求解两个模块。
*/

#include <iostream>
#include <cmath>
#include <string.h>

using namespace std;

void ProduceSudoku(int n)
{
	//生成数独具体代码
}

void SolveSudoku()
{
	//求解数独具体代码
}

int main(int argc,char** argv)
{
	if (argc != 3)
	{
		//提示参数个数错误
	}
	
	if (strcmp(argv[1], "-c") == 0)
	{
		//生成数独终局
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		//求解数独

	}
	else
	{
		//提示参数内容错误
	}

	return 0;
}
