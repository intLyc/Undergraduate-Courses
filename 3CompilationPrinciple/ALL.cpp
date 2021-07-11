#include <iostream>
#include <string>
#include <vector>
#include <stack>
#define MAXS 100
char prog[80], token[8];
char ch;
int syn, p, m = 0, n, row, sum = 0;
using namespace std;

//����תNFA
char unaryOP[16] = {'+', '-', '*', '/', '<', '>', '=', ';', ',', '(', ')', '[', ']', '{', '}', '!'}; //����һԪ�����
string ps[6] = {"if", "else", "int", "retn", "void", "whie"};										 //ϵͳ������
string *pa = ps;
string str[7] = {"ID", "NUM"};
string *strToken = str;
typedef enum
{
	ID,
	NUM
} tokenType; //�Ǻ�����
struct Node
{
	Node(int id, char input, int nextId)
	{
		this->id = id;
		this->input = input;
		this->nextId = nextId;
	}
	int id;
	char input;
	int nextId;
};

class MyClass
{
public:
	MyClass()
	{
		strExpress = "";
		statusId = 0;
	}

	MyClass(string str)
	{
		strExpress = str;
		statusId = 0;
	}

	int is_c = 0;
	void printNFA();
	void strToNFA();
	void fchange(vector<int> &, vector<char> &, vector<int> &);

private:
	string strExpress;
	int statusId;
	vector<Node *> map;
};

void MyClass::strToNFA()
{
	stack<int> s_st;
	stack<int> s_ed;
	stack<char> s_str;

	s_str.push('$');
	s_st.push(statusId++);
	s_ed.push(statusId++);

	for (auto i = strExpress.begin(); i != strExpress.end(); ++i)
	{
		char ch = *i;
		cout << ch;
		switch (ch)
		{
		case '(':
		{
			s_ed.push((statusId++) - 1);
			s_str.push('(');
			break;
		}
		case ')':
		{
			int ed = s_ed.top();
			int st = s_st.top();
			map.push_back(new Node(st, '-', ed));
			ch = s_str.top();
			while (ch != '(')
			{
				int nxt = s_st.top();
				s_st.pop();
				int pre = s_st.top();
				if (ch != '#')
					map.push_back(new Node(pre, ch, nxt));
				s_str.pop();
				ch = s_str.top();
			}
			s_str.pop();
			s_str.push('#');
			int top_num = s_ed.top();
			s_st.push(top_num);
			s_ed.pop();
			break;
		}
		case '|':
		{
			int ed = s_ed.top();
			int st = s_st.top();
			map.push_back(new Node(st, '-', ed));
			ch = s_str.top();
			while (ch != '(' && ch != '$')
			{
				int nxt = s_st.top();
				s_st.pop();
				int pre = s_st.top();
				if (ch != '#')
					map.push_back(new Node(pre, ch, nxt));
				s_str.pop();
				ch = s_str.top();
			}
			break;
		}
		case '*':
		{
			int nxt = s_st.top();
			s_st.pop();
			int pre = s_st.top();
			map.push_back(new Node(pre, '-', nxt));
			map.push_back(new Node(nxt, '-', pre));
			is_c++;
			s_st.push(nxt);
			break;
		}
		default:
		{
			s_str.push(ch);
			s_st.push((statusId++) - 1);
			break;
		}
		}
	}
	char ch = s_str.top();
	while (ch != '$')
	{
		int nxt = s_st.top();
		s_st.pop();
		int pre = s_st.top();
		if (ch != '#')
			map.push_back(new Node(pre, ch, nxt));
		s_str.pop();
		ch = s_str.top();
	}
}

void MyClass::printNFA()
{
	cout << "  NFA:" << endl;
	for (auto node : map)
	{
		cout << node->id << " " << node->input << " " << node->nextId << endl;
	}
}

void MyClass::fchange(vector<int> &fid, vector<char> &value, vector<int> &lid)
{
	for (auto node : map)
	{
		fid.push_back(node->id);
		value.push_back(node->input);
		lid.push_back(node->nextId);
	}
	for (; is_c > 0; is_c--)
	// if(is_c)
	{
		for (int i = 0; i < fid.size() - 1; i++)
		{
			if (fid[i] == lid[i + 1] && fid[i + 1] == lid[i] && value[i] == value[i + 1])
			{
				char a = fid[i], b = lid[i];
				fid.erase(fid.begin() + i);
				value.erase(value.begin() + i);
				lid.erase(lid.begin() + i);
				fid.erase(fid.begin() + i);
				value.erase(value.begin() + i);
				lid.erase(lid.begin() + i);
				for (int i = 0; i < fid.size(); i++)
				{
					if (fid[i] == b)
						fid[i] = a;
					if (lid[i] == b)
						lid[i] = a;
				}
			}
		}
		for (int i = 0; i < fid.size(); i++)
		{
			if (fid[i] == lid[i] && value[i] == '-')
			{
				fid.erase(fid.begin() + i);
				lid.erase(lid.begin() + i);
				value.erase(value.begin() + i);
			}
		}
	}

	//����
	int n = fid.size();
	for (int j = 0; j < n - 1; j++)
	{
		for (int i = 0; i < n - j - 1; i++)
		{
			if (fid[i] > fid[i + 1])
			{
				int x = fid[i];
				fid[i] = fid[i + 1];
				fid[i + 1] = x;
				char c = value[i];
				value[i] = value[i + 1];
				value[i + 1] = c;
				int y = lid[i];
				lid[i] = lid[i + 1];
				lid[i + 1] = y;
			}
		}
	}

	cout << endl;
	for (int i = 0; i < fid.size(); i++)
	{
		cout << (char)(fid[i] + 'A') << " " << value[i] << " " << (char)(lid[i] + 'A') << endl;
	}
}

//NFAתDFA

string NODE;   //��㼯��
string CHANGE; //�ս������
int N;		   //NFA����
struct edge
{
	string first;
	string change;
	string last;
};
struct chan
{
	string ltab;
	string jihe[MAXS];
};
void kong(int a)
{
	int i;
	for (i = 0; i < a; i++)
		cout << ' ';
}
//����
void paixu(string &a)
{
	int i, j;
	char b;
	for (j = 0; j < a.length(); j++)
		for (i = 0; i < a.length(); i++)
			if (NODE.find(a[i]) > NODE.find(a[i + 1]))
			{
				b = a[i];
				a[i] = a[i + 1];
				a[i + 1] = b;
			}
}
void eclouse(char c, string &he, edge b[])
{
	int k;
	for (k = 0; k < N; k++)
	{
		if (c == b[k].first[0])
			if (b[k].change[0] == '-')
			{
				if (he.find(b[k].last) > he.length())
					he += b[k].last;
				eclouse(b[k].last[0], he, b);
			}
	}
}
void move(chan &he, int m, edge b[])
{
	int i, j, k, l;
	k = he.ltab.length();
	l = he.jihe[m].length();
	for (i = 0; i < k; i++)
		for (j = 0; j < N; j++)
			if ((CHANGE[m] == b[j].change[0]) && (he.ltab[i] == b[j].first[0]))
				if (he.jihe[m].find(b[j].last[0]) > he.jihe[m].length())
					he.jihe[m] += b[j].last[0];
	for (i = 0; i < l; i++)
		for (j = 0; j < N; j++)
			if ((CHANGE[m] == b[j].change[0]) && (he.jihe[m][i] == b[j].first[0]))
				if (he.jihe[m].find(b[j].last[0]) > he.jihe[m].length())
					he.jihe[m] += b[j].last[0];
}
//���
void outputfa(int len, int h, chan *t)
{
	int i, j, m;
	cout << " I      ";
	for (i = 0; i < len; i++)
		cout << "I" << CHANGE[i] << "      ";
	cout << endl
		 << "-------------------------" << endl;
	for (i = 0; i < h; i++)
	{
		cout << ' ' << t[i].ltab;
		m = t[i].ltab.length();
		for (j = 0; j < len; j++)
		{
			kong(8 - m);
			m = t[i].jihe[j].length();
			cout << t[i].jihe[j];
		}
		cout << endl;
	}
}
string delete_comment(string a)
{
	int k = 0;
	int s = 0;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == '/' && a[i + 1] == '*')
		{
			k = i;
		}
	}
	for (int j = k + 1; j < a.length(); j++)
	{
		if (a[j] == '*' && a[j + 1] == '/')
		{
			s = j + 1;
		}
	}

	a.erase(k, s - k);
	return a;
}
void verify()
{
	for (int n = 0; n < 8; n++)
		token[n] = NULL;
	ch = prog[p++];
	while (ch == ' ')
	{
		ch = prog[p];
		p++;
	}
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) //�����Ǳ�ʾ�����߱�����
	{
		m = 0;
		while ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		{
			token[m++] = ch;
			ch = prog[p++];
		}
		token[m++] = '\0';
		p--;
		syn = 10;
		for (n = 0; n < 6; n++) //��ʶ��������ַ����Ѷ���ı�ʾ�����Ƚϣ�
			if (token == pa[n])
			{
				syn = n + 1;
				break;
			}
	}
	else if ((ch >= '0' && ch <= '9')) //����
	{
		{
			sum = 0;
			while ((ch >= '0' && ch <= '9'))
			{
				sum = sum * 10 + ch - '0';
				ch = prog[p++];
			}
		}
		p--;
		syn = 11;
		if (sum > 32767)
			syn = -1;
	}
	else
		switch (ch) //�����ַ�
		{
		case '<':
			m = 0;
			token[m++] = ch;
			ch = prog[p++];
			if (ch == '>')
			{
				syn = 21;
				token[m++] = ch;
			}
			else if (ch == '=')
			{
				syn = 22;
				token[m++] = ch;
			}
			else
			{
				syn = 23;
				p--;
			}
			break;
		case '>':
			m = 0;
			token[m++] = ch;
			ch = prog[p++];
			if (ch == '=')
			{
				syn = 24;
				token[m++] = ch;
			}
			else
			{
				syn = 20;
				p--;
			}
			break;
		case ':':
			m = 0;
			token[m++] = ch;
			ch = prog[p++];
			if (ch == '=')
			{
				syn = 18;
				token[m++] = ch;
			}
			else
			{
				syn = 17;
				p--;
			}
			break;
		case '*':
			syn = 13;
			token[0] = ch;
			break;
		case '/':
			syn = 14;
			token[0] = ch;
			break;
		case '+':
			syn = 15;
			token[0] = ch;
			break;
		case '-':
			syn = 16;
			token[0] = ch;
			break;
		case '=':
			syn = 25;
			token[0] = ch;
			break;
		case ';':
			syn = 26;
			token[0] = ch;
			break;
		case '(':
			syn = 27;
			token[0] = ch;
			break;
		case ')':
			syn = 28;
			token[0] = ch;
			break;
		case '#':
			syn = 0;
			token[0] = ch;
			break;
		case '\n':
			syn = -2;
			break;
		default:
			syn = -1;
			break;
		}
}
int main()
{
	string str;
	cout << "��������ʽ��";
	cin >> str;
	vector<int> fid, lid;
	vector<char> value;

	MyClass myclass(str);
	myclass.strToNFA();
	// myclass.printNFA();
	myclass.fchange(fid, value, lid);

	//nfa to dfa

	edge *b = new edge[MAXS];
	int i, j, k, m, n, h, x, y, len;
	bool flag;
	string jh[MAXS], endnode, ednode, sta;
	// cout << "������NFA������Ϣ����� ����[��Ϊ-] �յ㣩����#������" << endl;

	for (i = 0; i < fid.size(); i++)
	{
		b[i].first = char(fid[i] + 'A');
		b[i].change = value[i];
		b[i].last = char(lid[i] + 'A');
	}

	// for (i = 0; i < MAXS; i++)
	// {

	//     cin >> b[i].first;
	//     if (b[i].first == "#")
	//         break;
	//     cin >> b[i].change >> b[i].last;
	// }
	N = i;
	// N = fid.size();
	/*for(j=0;j<N;j++)
	cout<<b[j].first<<b[j].change<<b[j].last<<endl;*/
	for (i = 0; i < N; i++)
	{
		if (NODE.find(b[i].first) > NODE.length())
			NODE += b[i].first;
		if (NODE.find(b[i].last) > NODE.length())
			NODE += b[i].last;
		if ((CHANGE.find(b[i].change) > CHANGE.length()) && (b[i].change != "-"))
			CHANGE += b[i].change;
	}
	len = CHANGE.length();
	cout << "�����������̬���ǣ�" << endl;
	cin >> endnode;
	for (i = 0; i < endnode.length(); i++)
		if (NODE.find(endnode[i]) > NODE.length())
		{
			cout << "������̬���ڼ����У�����" << endl;
			return 0;
		}
	//cout<<"endnode="<<endnode<<endl;
	chan *t = new chan[MAXS];
	t[0].ltab = b[0].first;
	h = 1;
	eclouse(b[0].first[0], t[0].ltab, b); //��e-clouse
										  //cout<<t[0].ltab<<endl;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < t[i].ltab.length(); j++)
			for (m = 0; m < len; m++)
				eclouse(t[i].ltab[j], t[i].jihe[m], b); //��e-clouse
		for (k = 0; k < len; k++)
		{
			//cout<<t[i].jihe[k]<<"->";
			move(t[i], k, b); //��move(I,a)
							  //cout<<t[i].jihe[k]<<endl;
			for (j = 0; j < t[i].jihe[k].length(); j++)
				eclouse(t[i].jihe[k][j], t[i].jihe[k], b); //��e-clouse
		}
		for (j = 0; j < len; j++)
		{
			paixu(t[i].jihe[j]); //�Լ��������Ա�Ƚ�
			for (k = 0; k < h; k++)
			{
				flag = operator==(t[k].ltab, t[i].jihe[j]);
				if (flag)
					break;
			}
			if (!flag && t[i].jihe[j].length())
				t[h++].ltab = t[i].jihe[j];
		}
	}
	cout << endl
		 << "״̬ת���������£�" << endl;
	outputfa(len, h, t); //���״̬ת������
						 //״̬��������
	string *d = new string[h];
	NODE.erase();
	cout << endl
		 << "��������" << endl;
	for (i = 0; i < h; i++)
	{
		sta = t[i].ltab;
		t[i].ltab.erase();
		t[i].ltab = 'A' + i;
		NODE += t[i].ltab;
		cout << '{' << sta << "}=" << t[i].ltab << endl;
		for (j = 0; j < endnode.length(); j++)
			if (sta.find(endnode[j]) < sta.length())
				d[1] = ednode += t[i].ltab;
		for (k = 0; k < h; k++)
			for (m = 0; m < len; m++)
				if (sta == t[k].jihe[m])
					t[k].jihe[m] = t[i].ltab;
	}
	for (i = 0; i < NODE.length(); i++)
		if (ednode.find(NODE[i]) > ednode.length())
			d[0] += NODE[i];
	endnode = ednode;
	cout << endl
		 << "DFA���£�" << endl;
	outputfa(len, h, t); //���DFA
	cout << "������̬Ϊ��" << endnode << endl;
	//DFA��С��
	m = 2;
	sta.erase();
	flag = 0;
	for (i = 0; i < m; i++)
	{
		//cout<<"d["<<i<<"]="<<d[i]<<endl;
		for (k = 0; k < len; k++)
		{
			//cout<<"I"<<CHANGE[k]<<endl;
			y = m;
			for (j = 0; j < d[i].length(); j++)
			{
				for (n = 0; n < y; n++)
				{
					if (d[n].find(t[NODE.find(d[i][j])].jihe[k]) < d[n].length() || t[NODE.find(d[i][j])].jihe[k].length() == 0)
					{
						if (t[NODE.find(d[i][j])].jihe[k].length() == 0)
							x = m;
						else
							x = n;
						if (!sta.length())
						{
							sta += x + 48;
						}
						else if (sta[0] != x + 48)
						{
							d[m] += d[i][j];
							flag = 1;
							d[i].erase(j, 1);
							//cout<<d[i]<<endl;
							j--;
						}
						break; //����n
					}
				} //n
			}	 //j
			if (flag)
			{
				m++;
				flag = 0;
			}
			//cout<<"sta="<<sta<<endl;
			sta.erase();
		} //k
	}	 //i
	cout << endl
		 << "���ϻ��֣�";
	for (i = 0; i < m; i++)
		cout << "{" << d[i] << "} ";
	cout << endl;
	//״̬��������
	chan *md = new chan[m];
	NODE.erase();
	cout << endl
		 << "��������" << endl;
	for (i = 0; i < m; i++)
	{
		md[i].ltab = 'A' + i;
		NODE += md[i].ltab;
		cout << "{" << d[i] << "}=" << md[i].ltab << endl;
	}
	for (i = 0; i < m; i++)
		for (k = 0; k < len; k++)
			for (j = 0; j < h; j++)
			{
				if (d[i][0] == t[j].ltab[0])
				{
					for (n = 0; n < m; n++)
					{
						if (!t[j].jihe[k].length())
							break;
						else if (d[n].find(t[j].jihe[k]) < d[n].length())
						{
							md[i].jihe[k] = md[n].ltab;
							break;
						}
					}
					break;
				}
			}
	ednode.erase();
	for (i = 0; i < m; i++)
		for (j = 0; j < endnode.length(); j++)
			if (d[i].find(endnode[j]) < d[i].length() && ednode.find(md[i].ltab))
				ednode += md[i].ltab;
	endnode = ednode;
	cout << endl
		 << "��С��DFA���£�" << endl;
	outputfa(len, m, md);
	cout << "������̬Ϊ��" << endnode << endl;
	p = 0;
	row = 1;
	cout << "Please input string:" << endl;
	do
	{
		cin.get(ch);
		prog[p++] = ch;
	} while (ch != '#');
	p = 0;
	do
	{
		verify();
		switch (syn)
		{
		case 11:
			cout << "(" << syn << "," << sum << ")" << endl;
			break;
		case -1:
			cout << "Error in row " << row << "!" << endl;
			break;
		case -2:
			row = row++;
			break;
		default:
			cout << "(" << syn << "," << token << ")" << endl;
			break;
		}
	} while (syn != 0);
	//string sentence;
	//cin >> sentence;
	//sentence =delete_comment(sentence);//Ԥ����
	//verify(sentence);
	//cout << sentence<<endl;
	system("pause");
	return 0;
}
