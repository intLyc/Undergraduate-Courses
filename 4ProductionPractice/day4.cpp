#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <iomanip>
#include <map>
using namespace std;
//��ȥ���ո�֮����Ӵ�
int trimSpace(const char *str, char *outbuf);
int trimSpace(const char *str, char *outbuf)
{
	if (NULL == str || NULL == outbuf)
	{
		return -1;
	}
	const char *p = str;
	int i = 0;
	int j = strlen(str) - 1;
	while (isspace(p[i]) && p[i] != '\0')
	{
		i++;
	}
	while (isspace(p[j]) && p[j] != '\0')
	{
		j--;
	}
	int count = 0;
	count = j - i + 1;
	strncpy(outbuf, str + i, count);
	outbuf[count] = '\0';
	return 0;
}
/**
*���ܣ�ͳ�Ƹ�������������
*������char *str,char a
*˵����str���ַ�����a��Ҫ����������ַ�
**/
int count(char *str, char a)
{
	int count = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == a)
			count++;
	}
	return count;
}
/**
*���ܣ��õ��ָ����ַ���
*������char *str,int len
*˵����str���ַ�����lenΪ�ָ����ַ�������
**/
char *getnext(char *str, int len)
{
	char *re = (char *)malloc(20);
	strncpy(re, str + 1, len);
	re[len] = '\0';
	return re;
}
/**
*���ܣ����ַ�����ŵ���ά���飻������������
*������char *str,char**me_array
*˵����str���ַ�����me_array�Ƕ�ά����
**/
int my_array(char *str, char **me_array)
{
	char *tmp = str;
	if (NULL == str)
		return -1;

	int row = count(str, ',');

	tmp = strchr(str, '{') + 1;
	for (int i = 0; i < row; i++)
	{
		char *p = strchr(tmp, '"'); ////�ҵ���һ�γ���"��λ��
		char *tmp3 = p;
		char *q = strchr(tmp3 + 1, '"');
		//int a = q - p;
		int len = (q - p) - 1;
		char *tmp2 = p;
		me_array[i] = getnext(tmp2, len);
		/*me_array[strlen(me_array) + 1] = '\0';*/
		tmp = p;
		tmp += q - p + 1;
	}
	//cout << *me_array[0] << me_array[1];
	for (int i = 0; i < row; i++)
	{
		cout << me_array[i] << endl;
	}
	cout << "����Ϊ" << row << endl;
	cout << "����Ϊ" << row << endl;
	return 0;
}
/*
��������
1."{"abcedf","dddddd","eeeee","yyyyy",}"
2."{"abcedf","ddd ddd","eeeee","yyyyy",}"
3."{"abcedf", "ddd ddd", "eeeee", "yyyyy",}"
*/
void test()
{
	char *str = "{\"ab cedf\",   \"dddddd\",  \"eeeee\" ,  \"yyyyy\",}";
	int row = count(str, ',');
	if (NULL == str)
		return;
	char **me_array = (char **)malloc(sizeof(char *) * row);
	for (int i = 0; i < row; i++)
	{
		me_array[i] = (char *)malloc(sizeof(char) * 1024);
	}
	my_array(str, me_array);
}
int main()
{
	test();
	system("pause");
	return 0;
}
