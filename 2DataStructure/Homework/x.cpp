#include<iostream>
#include<cmath>
using namespace std;
typedef char ElemType;
typedef struct
{
	ElemType *base;//ָ��ջ��
	ElemType *top;//ָ��ջ��
	int StackSize = 20;
}sqStack;//����һ���ṹ����
void InitStack(sqStack *s)//��ʼ��ջ
{
	s->base = (ElemType *)malloc(20 * sizeof(ElemType));
	s->top = s->base;
}
void Push(sqStack *s, ElemType e)
{
	*(s->top) = e;
	s->top++;//ջ��ָ���һ
}
void Pop(sqStack *s, ElemType *e)
{
	*e = *(s->top);
	s->top--;
}
int main()
{
	ElemType c;
	sqStack s;
	int n = 0, sum = 0;
	InitStack(&s);
	cout << "" << 
	endl;
	cin >> c;
	while (c != '#') {
		Push(&s, c);
		n++;
		cin >> c;
	}
	for (int i = 0; i < n; i++) {
		Pop(&s, &c);
		cout << c << endl;
	}
	cout << sum;
	return 0;
}