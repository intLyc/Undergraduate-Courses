#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
using namespace std;
char data1[20][20]; //������ȹ�ϵ
char s[100];		//ģ�����ջs
char lable[20];		//�ķ��ռ�����
char input[100];	//�ķ�������Ŵ�
char str[20][10];   //�������봮�ķ���
int k, j;
char a, q;
int r; //�ķ��������
int r1;
int m, n, N;					 //ת�����ķ��������
char st[10][30];				 //�����洢�ķ�����
char first[10][10];				 //�ķ����ս��FIRSTVT��
char last[10][10];				 //�ķ����ս��LASTVT��
int fflag[10] = {0};			 //��־��i�����ս����FIRSTVT���Ƿ������
int lflag[10] = {0};			 //��־��i�����ս����LASTVT���Ƿ������
int deal();						 //�����봮�ķ���
int end(char c);				 //�ж��ַ�c�Ƿ����ռ���
int location(char c);			 //���ַ�c��������ȹ�ϵ���е��±�
void out(int j, int k, char *s); //��ӡsջ
void FIRSTVT(char c);			 //����ս��c��FIRSTVT��
void LASTVT(char c);			 //����ս��c��LASTVT��
void table();					 //�����ķ����ȹ�ϵ��
char output[10];				 //�洢�沨��ʽ
int main()
{
	int i, j, k = 0;
	printf("�������ķ���������");
	scanf("%d", &r);
	printf("�������ķ�����\n");
	for (i = 0; i < r; i++)
	{
		scanf("%s", st[i]); //�洢�ķ����򣬳�ʼ��FIRSTVT����LASTVT��
		first[i][0] = 0;	/*first[i][0]��last[i][0]�ֱ��ʾst[i][0]���ռ�����FIRSTVT����LASTVT����Ԫ�صĸ���*/
		last[i][0] = 0;
	}
	for (i = 0; i < r; i++) //�ж��ķ��Ƿ�Ϸ�
	{
		for (j = 0; st[i][j] != '\0'; j++)
		{
			if (st[i][0] < 'A' || st[i][0] > 'Z')
			{
				printf("�ķ�error!\n");
				exit(-1);
			}
			if (st[i][j] >= 'A' && st[i][j] <= 'Z')
			{
				if (st[i][j + 1] >= 'A' && st[i][j + 1] <= 'Z')
				{
					printf("�ķ�error!\n");
					exit(-1);
				}
			}
		}
	}
	for (i = 0; i < r; i++) //
		for (j = 0; st[i][j] != '\0'; j++)
			if ((st[i][j] < 'A' || st[i][j] > 'Z') && st[i][j] != '-' && st[i][j] != '>' && st[i][j] != '|')
				lable[k++] = st[i][j];
	lable[k] = '#';
	lable[k + 1] = '\0';
	table();				   //
	printf("FIRSTVT��Ϊ��\n"); //���ÿ�����ս����FIRST��
	for (i = 0; i < r; i++)
	{
		printf("%c: ", st[i][0]);
		for (j = 0; j < first[i][0]; j++)
			printf("%c ", first[i][j + 1]);
		printf("\n");
	}
	printf("LASTVT��Ϊ��\n"); //���ÿ�����ս����LAST��
	for (i = 0; i < r; i++)
	{
		printf("%c: ", st[i][0]);
		for (j = 0; j < last[i][0]; j++)
		{
			printf("%c ", last[i][j + 1]);
		}
		printf("\n");
	}
	printf("������ȷ���������:\n");
	for (i = 0; lable[i] != '\0'; i++)
		printf("\t%c", lable[i]);
	printf("\n");
	for (i = 0; i < k + 1; i++)
	{
		printf("%c\t", lable[i]);
		for (j = 0; j < k + 1; j++)
		{
			printf("%c\t", data1[i][j]);
		}
		printf("\n");
	}
	printf("�������ķ�������Ŵ���#����:");
	scanf("%s", input);
	deal();
	cout << "�沨��ʽΪ��";
	for (i = 0; lable[i] != '\0'; i++)
		cout << output[i] << '\0'; //
	cout << endl;
	system("pause");
}
void table()
{
	char text[20][10]; //�洢��д����ķ�
	int i, j, k, t, l, x = 0, y = 0;
	int m, n;
	x = 0;
	for (i = 0; i < r; i++)
	{
		FIRSTVT(st[i][0]);
		LASTVT(st[i][0]);
	}
	for (i = 0; i < r; i++) //��д�ķ�
	{
		text[x][y] = st[i][0];
		y++;
		for (j = 1; st[i][j] != '\0'; j++)
		{
			if (st[i][j] == '|') //
			{
				text[x][y] = '\0';
				x++;
				y = 0;
				text[x][y] = st[i][0];
				y++;
				text[x][y++] = '-';
				text[x][y++] = '>';
			}
			else
			{
				text[x][y] = st[i][j];
				y++;
			}
		}
		text[x][y] = '\0';
		x++;
		y = 0;
	}
	r1 = x; //
	printf("ת������ķ�Ϊ:\n");
	for (i = 0; i < x; i++) //���ת������ķ�����
	{
		printf("%s\n", text[i]);
	}
	for (i = 0; i < x; i++) /*��ÿ���ս�����Ƶ����(ȥ��"->"���ת���ķ����������Ĺ�Լ)*/
	{
		str[i][0] = text[i][0];
		for (j = 3, l = 1; text[i][j] != '\0'; j++, l++)
			str[i][l] = text[i][j];
		str[i][l] = '\0';
	}
	for (i = 0; i < x; i++)
	{
		for (j = 1; text[i][j + 1] != '\0'; j++)
		{
			if (end(text[i][j]) && end(text[i][j + 1]))
			{
				m = location(text[i][j]);
				n = location(text[i][j + 1]);
				data1[m][n] = '=';
			}
			if (text[i][j + 2] != '\0' && end(text[i][j]) && end(text[i][j + 2]) && !end(text[i][j + 1]))
			{
				m = location(text[i][j]);
				n = location(text[i][j + 2]);
				data1[m][n] = '=';
			}
			if (end(text[i][j]) && !end(text[i][j + 1])) //�ս���ͷ��ս����ӣ��ú��ڹ�ϵ���
			{
				for (k = 0; k < r; k++)
				{
					if (st[k][0] == text[i][j + 1])
						break;
				}
				m = location(text[i][j]);
				for (t = 0; t < first[k][0]; t++)
				{
					n = location(first[k][t + 1]);
					data1[m][n] = '<';
				}
			}
			if (!end(text[i][j]) && end(text[i][j + 1])) //���ս�����ս����ӣ������ڹ�ϵ���
			{
				for (k = 0; k < r; k++)
				{
					if (st[k][0] == text[i][j])
						break;
				}
				n = location(text[i][j + 1]);
				for (t = 0; t < last[k][0]; t++)
				{
					m = location(last[k][t + 1]);
					data1[m][n] = '>';
				}
			}
		}
	}
	m = location('#'); //#�������е��ս����Լ
	for (t = 0; t < first[0][0]; t++)
	{
		n = location(first[0][t + 1]);
		data1[m][n] = '<';
	}
	n = location('#'); //
	for (t = 0; t < last[0][0]; t++)
	{
		m = location(last[0][t + 1]);
		data1[m][n] = '>';
	}
	data1[n][n] = '=';
}
void FIRSTVT(char c) //��FIRSTVT��
{
	int i, j, k, m, n;
	for (i = 0; i < r; i++) //�ҳ��ǵ�i�����ս��
	{
		if (st[i][0] == c)
			break;
	}
	if (fflag[i] == 0)
	{
		n = first[i][0] + 1;
		m = 0;
		do
		{
			if (m == 2 || st[i][m] == '|')
			{
				if (end(st[i][m + 1]))
				{
					first[i][n] = st[i][m + 1];
					n++;
				}
				else
				{
					if (end(st[i][m + 2]))
					{
						first[i][n] = st[i][m + 2];
						n++;
					}
					if (st[i][m + 1] != c)
					{
						FIRSTVT(st[i][m + 1]);
						for (j = 0; j < r; j++)
						{
							if (st[j][0] == st[i][m + 1])
								break;
						}
						for (k = 0; k < first[j][0]; k++)
						{
							int t;
							for (t = 0; t < n; t++)
							{
								if (first[i][t] == first[j][k + 1])
									break;
							}
							if (t == n)
							{
								first[i][n] = first[j][k + 1];
								n++;
							}
						}
					}
				}
			}
			m++;
		} while (st[i][m] != '\0');
		first[i][n] = '\0';
		first[i][0] = --n;
		fflag[i] = 1;
	}
}
void LASTVT(char c) //��LASTVT��
{
	int i, j, k, m, n;
	for (i = 0; i < r; i++)
	{
		if (st[i][0] == c)
			break;
	}
	if (lflag[i] == 0)
	{
		n = last[i][0] + 1;
		m = 0;
		do
		{
			if (st[i][m + 1] == '\0' || st[i][m + 1] == '|')
			{
				if (end(st[i][m]))
				{
					last[i][n] = st[i][m];
					n++;
				}
				else
				{
					if (end(st[i][m - 1]))
					{
						last[i][n] = st[i][m - 1];
						n++;
					}
					if (st[i][m] != c)
					{
						LASTVT(st[i][m]);
						for (j = 0; j < r; j++)
						{
							if (st[j][0] == st[i][m])
								break;
						}
						for (k = 0; k < last[j][0]; k++)
						{
							int t;
							for (t = 0; t < n; t++)
							{
								if (last[i][t] == last[j][k + 1])
									break;
							}
							if (t == n)
							{
								last[i][n] = last[j][k + 1];
								n++;
							}
						}
					}
				}
			}
			m++;
		} while (st[i][m] != '\0');
		last[i][n] = '\0';
		last[i][0] = --n;
		lflag[i] = 1;
	}
}
int deal()
{
	int i, j;
	int size = 0; //
	int x, y;
	int z; //���봮�ĳ���
	k = 1;
	s[k] = '#'; //ջ�ó�ֵ
	for (i = 0; input[i] != '\0'; i++)
		;	//�������봮�ĳ���
	z = i--; //
	i = 0;
	while ((a = input[i]) != '\0') //a��ʾҪ������ַ�
	{
		if (end(s[k]))
			j = k;
		else
			j = k - 1;
		x = location(s[j]);
		y = location(a);
		if (data1[x][y] == '>')
		{
			if (lable[x] != ')')
				output[size++] = lable[x]; //��Ҫ��Լ���ս��������
			out(1, k, s);
			printf("%c", a);
			out(i + 1, z, input);
			printf("��Լ\n");
			do
			{
				q = s[j];
				if (end(s[j - 1]))
					j = j - 1;
				else
					j = j - 2;
				x = location(s[j]);
				y = location(q);
			} while (data1[x][y] != '<');
			int m, n, N;
			for (m = j + 1; m <= k; m++)
			{
				for (N = 0; N < r1; N++)
					for (n = 1; str[N][n] != '\0'; n++)
					{
						if (!end(s[m]) && !end(str[N][n]))
						{
							if (end(s[m + 1]) && end(str[N][n + 1]) && s[m + 1] == str[N][n + 1])
							{
								s[j + 1] = str[N][0];
								break;
							}
						}
						else if (end(s[m]))
							if (s[m] == str[N][n])
							{
								s[j + 1] = str[N][0];
								break;
							}
					}
			}
			k = j + 1;
			if (k == 2 && a == '#')
			{
				out(1, k, s);
				printf("%c", a);
				out(i + 1, z, input);
				printf("����\n");
				printf("��Լ�ɹ�!\n");
				return 1; //���봮�����ķ��Ķ���
			}
		}
		else if (data1[x][y] == '<' || data1[x][y] == '=')
		{ //�ƽ�
			out(1, k, s);
			printf("%c", a);
			out(i + 1, z, input);
			printf("�ƽ�\n");
			k++;
			s[k] = a;
			i++;
		}
		else
		{
			printf("\n��Լʧ��\n");
			return 0;
		}
	}
	printf("\n��Լʧ��\n"); //
	return 0;
}
void out(int j, int k, char *s)
{
	int n = 0;
	int i;
	for (i = j; i <= k; i++)
	{
		printf("%c", s[i]);
		n++;
	}
	for (; n < 15; n++)
	{
		printf(" ");
	}
}
int location(char c) //���ַ�c��������ȹ�ϵ���е��±�
{
	int i;
	for (i = 0; lable[i] != '\0'; i++)
	{
		if (c == lable[i])
			return i;
	}
	return -1;
}
int end(char c) //�ж��ַ�c�Ƿ����ռ���
{
	int i;
	for (i = 0; lable[i] != '\0'; i++)
	{
		if (c == lable[i])
			return 1;
	}
	return 0;
}
