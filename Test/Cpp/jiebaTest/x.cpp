#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 1000
using namespace std;

struct node
{
	int to;	  //�����ӵ���һ���ڵ�
	int next; //��¼ǰһ���ߣ����ڻ��ݣ�
	int w;
} edge[maxn * 2];

struct point
{
	int gra;
	int v;
} extra[maxn], defic[maxn];

int head[maxn * 2]; //ÿ�������ڵıߺţ�ÿ������������2��u->v,v->u��
int fath[maxn];		//�ڵ�ĸ��ڵ�
int gran[maxn];		//�ڵ�ĵ����ڶ��������Ƚڵ㣨�������ĵڶ���Ľڵ㣩
int dis[maxn];		//�ڵ㵽���ڵ�ľ���
int arm[maxn];		//�������ڳ��е�
int cal[maxn], tim[maxn], b[maxn];
int n;		 //�ڵ����
int m;		 //������
int tot = 0; //���ĵڶ���ڵ�ĸ���
int cnt = 0; //�ߺţ�ÿ������������2��u->v,v->u��
int sum = 0, na = 0, nc = 0;

bool comp(const point &a, const point &b)
{
	return a.v > b.v;
}

void add(int, int, int); //��ͼ
void dfs(int);			 //�����Ҫ�����ǵĵ���ѱ����ǵĵ�
void cal_tim(int);		 //�����ÿ�����ӵ��������ܵ������ܵ�
void cal_extra(int);	 //�ܵ��Ļ��ж���ʣ��
void cal_defic();		 //���ܵ��Ļ������
bool remedy();			 //�ܵ����ܲ��ܲ��벻�ܵ���
bool ok(int);			 //���ֵ�ʱ���Ƿ񹻣���ʵ���ǵ��������ĸ�������
void conn_anc(int);		 //�������������������ֱϽ�У����ڵ�Ķ���
int erfen();			 //����ʱ��

int main()
{
	cin >> n;
	memset(head, 0, sizeof(head));
	//�����
	for (int i = 1; i < n; i++)
	{
		int x, y, ww;
		cin >> x >> y >> ww;
		//ÿ�β�����������ߣ�Ŀ����Ϊ�˻���
		//edge�������߼��ǣ���������->�ӣ�˫������->����
		add(x, y, ww);
		add(y, x, ww);
		if (x == 1 || y == 1)
			tot++;
	}

	cin >> m;
	if (tot > m) //�жϾ��������Ƿ�С�ڵڶ���ڵ�������С�����޽⣩
	{
		cout << -1;
		return 0;
	}

	//������ȡ���нڵ�ĸ��ڵ㡢�ڶ������Ƚڵ㡢�����ڵ�ľ���
	conn_anc(1);

	//�������
	for (int i = 1; i <= m; i++)
		cin >> arm[i];
	sort(arm + 1, arm + 1 + m);

	cout << erfen();
	return 0;
}

void add(int u, int v, int ww)
{
	cnt++;
	edge[cnt].to = v;		  //�ߵ���һ����
	edge[cnt].next = head[u]; //�洢���ݵı�
	edge[cnt].w = ww;		  //����
	head[u] = cnt;			  //����u���������ı�
}

void conn_anc(int x)
{
	for (int i = head[x]; i; i = edge[i].next) //��ʼ����x���������ıߣ�����������û�л��ݣ���������������һ����
	{
		int vv = edge[i].to; //���������ŵ���һ����
		if (fath[x] != vv)	 //�Ƿ��ӽڵ㣨���û����������ݸ��ڵ㣩
		{
			if (x == 1)		   //���ڵ㣬��ʱvv���Ǹ��ڵ���ӽڵ㣨�ڶ���Ľڵ㣩
				gran[vv] = vv; //�ڶ������Ƚڵ���ڱ���
			else
				gran[vv] = gran[x];		  //���ݸ��ڵ�洢�ĸ��µ�ǰ�ڵ�ĵڶ������Ƚڵ�
			fath[vv] = x;				  //���¸��ڵ�
			dis[vv] = dis[x] + edge[i].w; //��ǰ�ڵ㵽���ڵ�ľ���
			conn_anc(vv);				  //�������������һ����
		}
	}
}

void dfs(int root)
{
	int maxx = -1, now1 = 0, now2 = 0;
	for (int i = head[root]; i; i = edge[i].next) //��ʼ����x���������ıߣ�����������û�л��ݣ���������������һ����
	{
		int vv = edge[i].to;  //���������ŵ���һ����
		if (fath[root] != vv) //�Ƿ�Ϊ�ӽڵ�
		{
			dfs(vv); //������������ӽڵ�
			if (tim[vv] == -1)
				now2 = 1; //�õ���δ������
			if (tim[vv] >= edge[i].w)
				now1 = 1; //�õ���Ա�����
			maxx = max(maxx, tim[vv] - edge[i].w);
		}
	}
	if (root != 1 && edge[head[root]].next) //��ǰ�㲻�Ǹ��ڵ� �� ��ǰ�ı߲�������Ҫ����
	{
		if (now1)
			tim[root] = max(tim[root], maxx);
		else if (now2)
			tim[root] = max(tim[root], -1);
		else
			tim[root] = max(tim[root], 0);
	}
}

void cal_tim(int ti)
{
	for (int i = 1; i <= m; i++)
		if (dis[arm[i]] >= ti) //���ӵ����ڵ�ľ������������ʱ��
			tim[arm[i]] = ti;
	dfs(1);
}

void cal_extra(int ti)
{
	for (int i = 1; i <= m; i++)
	{
		if (dis[arm[i]] < ti)
		{
			extra[++na].gra = gran[arm[i]];
			extra[na].v = ti - dis[arm[i]];
		}
	}
	sort(extra + 1, extra + na + 1, comp);
	for (int i = 1; i <= na; i++)
	{
		if (!cal[extra[i].gra])
			cal[extra[i].gra] = i;
		else if (extra[cal[extra[i].gra]].v > extra[i].v)
			cal[extra[i].gra] = i;
	}
}

void cal_defic()
{
	for (int i = head[1]; i; i = edge[i].next)
	{
		int vv = edge[i].to;
		if (tim[vv] == -1)
		{
			defic[++nc].gra = vv;
			defic[nc].v = edge[i].w;
		}
	}
	sort(defic + 1, defic + nc + 1, comp);
}

bool remedy()
{
	if (na < nc)
		return false;
	memset(b, 0, sizeof(b));
	int i = 1, j = 1;
	for (; i <= nc; i++)
	{
		if (!b[cal[defic[i].gra]] && cal[defic[i].gra])
			b[cal[defic[i].gra]] = 1;
		else
		{
			while (j <= na && b[j])
				j++;
			if (j > na || extra[j].v < defic[i].v)
				return false;
			b[j] = 1, j++;
		}
	}
	return true;
}

bool ok(int ti)
{
	memset(cal, 0, sizeof(cal));
	na = nc = 0;
	memset(tim, -1, sizeof(tim));
	cal_tim(ti);
	cal_extra(ti);
	cal_defic();
	return remedy();
}

int erfen()
{
	int l = -1, r = 999999999;
	//���ַ���ʱ���0-999999999��ÿ�ζ԰�֣�ֱ���ҵ����ϵ���С��
	while (l + 1 < r)
	{
		int mid = (l + r) / 2;
		if (ok(mid))
			r = mid;
		else
			l = mid;
	}
	return r;
}
