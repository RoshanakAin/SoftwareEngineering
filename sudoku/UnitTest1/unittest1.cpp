#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sudoku/sudoku.h"
#include "../sudoku/sudoku.cpp"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		int argc;
		char **argv_c, **argv_s;

		UnitTest1()
		{
			argc = 3;
			argv_c = new char*[3];
			argv_s = new char*[3];

			for (int i = 0; i < 3; i++)
			{
				argv_c[i] = new char[100];
				argv_s[i] = new char[100];
			}

			strcpy_s(argv_c[0], 100, "sudoku.exe");
			strcpy_s(argv_c[1], 100, "-c");
			strcpy_s(argv_c[2], 100, "10");

			strcpy_s(argv_s[0], 100, "sudoku.exe");
			strcpy_s(argv_s[1], 100, "-s");
			strcpy_s(argv_s[2], 100, "E:\\BIT\\2019-2020-1\\SE\\sudoku\\sudoku\\BIN\\puzzle.txt");
		}
		
		//对命令行-c输入的测试
		TEST_METHOD(TestMethod1)
		{
			strcpy_s(argv_c[2], 100, "20");
			check Q(argc, argv_c);
			Q.input_type_analyse();

			Assert::AreEqual(Q.get_type() == 'c', true);
			Assert::AreEqual(Q.get_num() == 20, true);
			Assert::AreEqual(Q.found_error() == false, true);
		}

		//对命令行-s输入的测试
		TEST_METHOD(TestMethod2) 
		{
			check Q(argc, argv_s);
			Q.input_type_analyse();

			Assert::AreEqual(Q.get_type() == 's', true);
			Assert::AreEqual(!strcmp(Q.get_filename(), "E:\\BIT\\2019-2020-1\\SE\\sudoku\\sudoku\\BIN\\puzzle.txt"), true);
			Assert::AreEqual(Q.found_error() == false, true);
		}

		//对命令行-c个数输入参数有误的测试
		TEST_METHOD(TestMethod3)
		{
			strcpy_s(argv_c[2], 100, "hdsdw");
			strcpy_s(argv_c[1], 100, "-c");
			check Q(argc, argv_c);
			Q.input_type_analyse();

			Assert::AreEqual(Q.found_error() == true, true);
		}

		//对命令行输入-s地址参数有误的测试
		TEST_METHOD(TestMethod4)
		{
			strcpy_s(argv_s[2], 100, "E:\\BIT\\2019-2020-1\\SE\\sudoku\\sudoku\\BIN\\puzzle123.txt");
			strcpy_s(argv_s[1], 100, "-s");
			check Q(argc, argv_s);
			Q.input_type_analyse();

			Assert::AreEqual(Q.found_error() == true, true);
		}

		//对命令行输入参数有误的测试
		TEST_METHOD(TestMethod5)
		{
			strcpy_s(argv_s[2], 100, "232");
			strcpy_s(argv_s[1], 100, "-a");
			check Q(argc, argv_s);
			Q.input_type_analyse();

			Assert::AreEqual(Q.found_error() == true, true);
		}

		//输入参数个数有误
		TEST_METHOD(TestMethod6)
		{
			argc = 4;
			check Q(argc, argv_c);
			Q.input_type_analyse();

			Assert::AreEqual(Q.found_error() == true, true);
		}

		//对输入参数-c生成数独终局个数有误的测试
		TEST_METHOD(TestMethod7)
		{
			strcpy_s(argv_c[2], 100, "9999999999");
			strcpy_s(argv_c[1], 100, "-c");
			check Q(argc, argv_c);
			Q.input_type_analyse();

			Assert::AreEqual(Q.found_error() == true, true);
		}

		//对输入参数-c生成数独终局个数有误的测试
		TEST_METHOD(TestMethod8)
		{
			strcpy_s(argv_c[2], 100, "0");
			strcpy_s(argv_c[1], 100, "-c");
			check Q(argc, argv_c);
			Q.input_type_analyse();

			Assert::AreEqual(Q.found_error() == true, true);
		}

		//对CheckVis函数进行的有误测试
		TEST_METHOD(TestMethod9)
		{
			char grid[9][9] = { { 9, 5, 8, 3, 5, 7, 1, 2, 4 },
			{ 2, 3, 7, 4, 5, 1, 9, 6, 8 },
			{ 1, 4, 6, 9, 2, 8, 3, 5, 7 },
			{ 2, 1, 2, 8, 7, 4, 5, 9, 3 },
			{ 5, 7, 3, 6, 1, 9, 4, 8, 2 },
			{ 4, 8, 9, 2, 3, 5, 6, 7, 1 },
			{ 7, 2, 4, 5, 9, 3, 8, 1, 5 },
			{ 8, 9, 1, 7, 4, 6, 2, 3, 5 },
			{ 3, 6, 5, 1, 8, 2, 7, 4, 9 }
			};

			int flag = 0;
			int row = 0;
			int col = 4;

			for (int j = 0; j < 9; j++)     //同一行
			{
				if (grid[row][j] == grid[row][col] && j != col)
				{
					flag = 1;
					break;
				}
			}
			Assert::AreEqual(flag == 1, true);

			row = 3; col = 0; flag = 0;
			for (int j = 0; j < 9; j++)     //同一列
			{
				if (grid[j][col] == grid[row][col] && j != row)
				{
					flag = 1;
					break;
				}
			}
			Assert::AreEqual(flag == 1, true);

			row = 6, col = 8; flag = 0;
			int baseRow = row / 3 * 3;
			int baseCol = col / 3 * 3;
			for (int j = baseRow; j < baseRow + 3; j++)   //同一宫
			{
				for (int k = baseCol; k < baseCol + 3; k++)
				{
					if (grid[j][k] == grid[row][col] && (j != row || k != col))
					{
						flag = 1;
						break;
					}
				}

				if (flag == 1)
					break;
			}

			Assert::AreEqual(flag == 1, true);
		}

		//对CheckVis函数进行的正确测试
		TEST_METHOD(TestMethod10)
		{
			char grid[9][9] = { { 9, 5, 8, 3, 6, 7, 1, 2, 4 },
			{ 2, 3, 7, 4, 5, 1, 9, 6, 8 },
			{ 1, 4, 6, 9, 2, 8, 3, 5, 7 },
			{ 6, 1, 2, 8, 7, 4, 5, 9, 3 },
			{ 5, 7, 3, 6, 1, 9, 4, 8, 2 },
			{ 4, 8, 9, 2, 3, 5, 6, 7, 1 },
			{ 7, 2, 4, 5, 9, 3, 8, 1, 6 },
			{ 8, 9, 1, 7, 4, 6, 2, 3, 5 },
			{ 3, 6, 5, 1, 8, 2, 7, 4, 9 }
			};

			int flag = 0;
			int row = 0;
			int col = 4;

			for (int j = 0; j < 9; j++)     //同一行
			{
				if (grid[row][j] == grid[row][col] && j != col)
				{
					flag = 1;
					break;
				}
			}

			for (int j = 0; j < 9; j++)     //同一列
			{
				if (grid[j][col] == grid[row][col] && j != row)
				{
					flag = 1;
					break;
				}
			}

			int baseRow = row / 3 * 3;
			int baseCol = col / 3 * 3;
			for (int j = baseRow; j < baseRow + 3; j++)   //同一宫
			{
				for (int k = baseCol; k < baseCol + 3; k++)
				{
					if (grid[j][k] == grid[row][col] && (j != row || k != col))
					{
						flag = 1;
						break;
					}
				}

				if (flag == 1)
					break;
			}

			Assert::AreEqual(flag == 0, true);
		}

		//对全排列函数检测
		TEST_METHOD(TestMethod11)
		{
			int x;
			int a[9] = { 1,2,3,4,5,6,7,8,9 };
			int flag = 0;
			next_permutation(a, a + 9);

			int b[9] = { 1,2,3,4,5,6,7,9,8 };
			for (int i = 0; i < 9; i++)
				if (a[i] != b[i])
				{
					flag = 1;
					break;
				}
			Assert::AreEqual(flag == 0, true);
		}

	};
}