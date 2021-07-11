#include <iostream>
#include "stack.h"
using namespace std;

struct xnode { // ���ṹ��
    int x;
    xnode *link;
    xnode(xnode *ptr = NULL) {link = ptr; x = 0;}
    xnode(const int& item, xnode *ptr = NULL) {
        x = item;
        link = ptr;
    }
    void operator=(xnode &d) {
        x = d.x;
        link = d.link;
    }
};

class big_number { //������
public:
    big_number() {head = new xnode; head->link = new xnode(1);};
    ~big_number() {destory();};
    void destory();
    xnode *get_head() {return head;};
    void factorial(int n);
    friend ostream &operator<<(ostream &output, big_number &b);
private:
    xnode *head;
};

void big_number::factorial(int n) { //�׳˹��ܺ���
    int flow; //�����������
    for (int i=1; i<=n; i++) { //�����������1�˵�n
        xnode *p = head->link;
        flow = 0;
        while (p) { //�����˷�
            p->x = i * p->x + flow;
            if (p->x >= 10 && !p->link) { //�����������½��ڵ�
                p->link = new xnode();
            }
            flow = p->x/10;
            p->x %= 10;
            p = p->link;
        }
    }
}

ostream &operator<<(ostream &out, big_number &b) { //������Ԫ�����������ת�������
    stack<int> st;
    xnode *p = b.get_head();
    while (p->link) { //�������ݳ�Ա��ջ
        st.push(p->link->x);
        p = p->link;
    }
    while (!st.empty()) { //�������ݳ�Ա��ջ
        out << st.top();
        st.pop();
    }
    return out;
}

void big_number::destory() { //ɾ����������Ŀռ�
    xnode *p;
    while (head != NULL) {
        p = head;
        head = head->link;
        delete p;
    }
}

int main() {
    int n;
    while (cin >> n && n > 0) {
        big_number out;
        out.factorial(n);
        cout << out << endl;
    }
    return 0;
}
