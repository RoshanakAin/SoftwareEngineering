#include "sudoku.h"

#define SetVisit 1
#define CancelVisit 0

using namespace std;

int n;//��Ҫ���ɵ������������
char grid[10][10];//��������
char buffer[170000000];//�������ļ��Ļ���
int buffer_cursor = 0;//buffer����ĵ�ǰ����
ofstream OutCreateFile;//���ɾ���д����ļ�
ifstream PuzzleFile;//����������Ե��ļ�
ofstream OutSolvedFile;//�����ľ����ļ�
char permutation[15] = { '1','2','3','4','5','6','7','9' };//���ɵĳ�ʼ����
char move1[10][5] = { "036","063" };//����ÿ���е��ƶ�����
char move2[10][5] = { "258","285","528","582","852","825" };//�ƶ�����4-6��
char move3[10][5] = { "147","174","417","471","714","741" };//�ƶ�����7-9��

int vis[3][10][10];
//��һά��0��ʾ�С�1��ʾ�С�2��ʾ�Ź���
//�ڶ�ά�б�ʾ�ڵڼ����С��л�Ź�����
//����ά��ʾ���е�ĳ�����֣���������ֱ������ˣ�visֵ��1��������0
bool is_found = false;//��ʶ�Ƿ��ҵ���

void CreateSudoku(int n)
{
	//���������������
	int cnt_create = 0;//�Ѿ����ɵ�������Ŀ
					   //ѭ������n������
	while (cnt_create < n)
	{
		permutation[8] = '8';//ѧ��λ�̶�
							 //�����ƶ���ʽ����72�ֲ�ͬ������
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				for (int k = 0; k < 6; ++k)
				{
					//ÿ����ƽ�ƹ�������
					//1-3��
					for (int row = 0; row < 3; ++row)
					{
						//���ɸ�������ĸ
						int tmp = (8 + move1[i][row] - '0') % 9;//����ƽ�ƺ�λ�ã���Ϊѧ��λ��ĩβ����+8
						buffer[buffer_cursor] = permutation[tmp];//���뻺����
						buffer_cursor++;

						//���а����ֺͿո���룬mΪ�����ַ�����
						for (int m = 1; m <= 16; m++)
						{
							buffer[buffer_cursor++] = ' ';//����ո�
							m++;
							int tmp = (8 - (m / 2) + move1[i][row] - '0') % 9;//���ɵ�ǰ������ƽ�ƺ�λ��
							buffer[buffer_cursor++] = permutation[tmp];
						}
						buffer[buffer_cursor++] = '\n';//����
					}

					//4-6��
					for (int row = 0; row < 3; ++row)
					{
						//���ɸ�������ĸ
						int tmp = (8 + move2[j][row] - '0') % 9;//����ƽ�ƺ�λ�ã���Ϊѧ��λ��ĩβ����+8
						buffer[buffer_cursor] = permutation[tmp];//���뻺����
						buffer_cursor++;

						//���а����ֺͿո���룬mΪ�����ַ�����
						for (int m = 1; m <= 16; m++)
						{
							buffer[buffer_cursor++] = ' ';//����ո�
							m++;
							int tmp = (8 - (m / 2) + move1[i][row] - '0') % 9;//���ɵ�ǰ������ƽ�ƺ�λ��
							buffer[buffer_cursor++] = permutation[tmp];
						}
						buffer[buffer_cursor++] = '\n';//����
					}

					//7-9��
					for (int row = 0; row < 3; ++row)
					{
						//���ɸ�������ĸ
						int tmp = (8 + move3[k][row] - '0') % 9;//����ƽ�ƺ�λ�ã���Ϊѧ��λ��ĩβ����+8
						buffer[buffer_cursor] = permutation[tmp];//���뻺����
						buffer_cursor++;

						//���а����ֺͿո���룬mΪ�����ַ�����
						for (int m = 1; m <= 16; m++)
						{
							buffer[buffer_cursor++] = ' ';//����ո�
							m++;
							int tmp = (8 - (m / 2) + move1[i][row] - '0') % 9;//���ɵ�ǰ������ƽ�ƺ�λ��
							buffer[buffer_cursor++] = permutation[tmp];
						}
						buffer[buffer_cursor++] = '\n';//����
					}

					buffer[buffer_cursor++] = '\n';//������ͬ������һ��

					cnt_create++;//���ɾ������+1
					if (cnt_create == n)
						return;
				}
			}
		}

		//���ֵ�������ȫ����,��ѧ��λ����
		next_permutation(permutation, permutation + 8);
	}
}

void SetVis(int row, int col, int num, int flag)
{
	//ռ��ʱflagΪ1������ռ��ʱflagΪ0
	vis[0][row][num] = flag;//��
	vis[1][col][num] = flag;//��
	vis[2][row / 3 * 3 + col / 3][num] = flag;//�Ź���
}

bool CheckVis(int row, int col, int num)
{
	if (vis[0][row][num] == 0
		&& vis[1][col][num] == 0
		&& vis[2][row / 3 * 3 + col / 3][num] == 0)
		return true;
	return false;
}

void SolveSingleSudoku(int row, int col)
{
	while (grid[row][col] != '0')//�ҵ�δ����ĸ���
	{
		if (col < 8)//�����ƽ�
			col++;
		else
		{//�����ƽ�
			col = 0;
			row++;
		}

		if (row == 9)
		{
			//��������Ѿ��޿ո�
			is_found = true;
			return;
		}
	}

	bool is_search = false;
	//����1-9
	for (int i = 1; i <= 9; i++)
	{
		//��δ����
		if (CheckVis(row,col,i))
		{
			SetVis(row, col, i, SetVisit);//��ռ�� 
			grid[row][col] = i + '0';
			is_search = true;
			//����
			SolveSingleSudoku(row, col);
		}

		if (is_search)//��һ���㱻������ 
		{
			is_search = false;
			if (is_found)//�ҵ��˼�����
				return;
			//����
			SetVis(row, col, i, CancelVisit);
			grid[row][col] = '0';
		}
	}
}

void SolveSudoku(char* FilePath)//�����㷨
{
	PuzzleFile.open(FilePath);
	if (!PuzzleFile)
	{
		cout << "Path Invalid��" << endl;
		return;
	}
	//���ļ��������
	//ifstream�����ո�ͽ�ֹ
	char str[25];
	int LineCount = 0;
	while (PuzzleFile.getline(str, 20))
	{
		for (int i = 0; i <= 16; ++i)
		{
			if (i % 2 == 0)//Ϊ����Ԫ��
			{
				grid[LineCount][i / 2] = str[i];
				SetVis(LineCount, i / 2, str[i] - '0', SetVisit);//��ռ��
			}
		}

		LineCount++;//����
		if (LineCount == 9)//���¾���
		{
			is_found = false;
			SolveSingleSudoku(0, 0);//���ݽ�����
									//д�뻺��
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
			buffer[buffer_cursor++] = '\n';
			OutSolvedFile << buffer;
			//�������
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
		//��ʾ������������
		cout << "Please input 3 parameters" << endl;
		return 0;
	}

	int start = clock();
	if (strcmp(argv[1], "-c") == 0)
	{//���������վ�
		n = atoi(argv[2]);//�������������վֵĸ�����Χ
		if (n < 1 || n>1000000)
		{
			cout << "Number is illegal" << endl;
			return 0;
		}
		//��ʼ��������
		buffer_cursor = 0;
		memset(buffer, 0, sizeof(buffer));
		//�����վ�
		CreateSudoku(n);
		//������ļ�
		OutCreateFile.open("sudoku.txt");
		OutCreateFile << buffer;
		OutCreateFile.close();
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		//��ʼ��������
		buffer_cursor = 0;
		memset(buffer, 0, sizeof(buffer));
		memset(vis, 0, sizeof(vis));
		//���ļ�
		OutSolvedFile.open("sudoku.txt");
		//�������
		SolveSudoku(argv[2]);
		//������ļ�
		OutSolvedFile.close();
	}
	else
	{
		//��ʾ�������ݴ���
		cout << "Command illegal" << endl;
	}
	int end = clock();
	cout << "����ʱ��Ϊ��" << end - start << "ms" << endl;
	return 0;
}