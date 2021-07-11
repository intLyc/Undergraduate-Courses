#include <iostream>
#include <iomanip>

using namespace std;

class RD { //����������
public:
    bool flag;
    int number;
    int addr;
    int size;
    RD *next;
    RD() {flag = 0; number = 0; addr = 0; size = 0; next = NULL;}
    RD(bool var1,int var2,int var3,int var4) {
        flag = var1; number = var2; addr = var3; size = var4; next = NULL;
        }
    void print() {
        if (number) {
            cout << "��־:" << setw(5) << flag
            << "  ���̺�:" << setw(5) << number
            << "  ��ʼ��ַ:" << setw(5) << addr
            << "  ��С:" << setw(5) << size << endl;
        }
        else cout << "��־:" << setw(5) << flag
        << "  ���̺�:" << setw(5) << "����"
        << "  ��ʼ��ַ:" << setw(5) << addr
        << "  ��С:" << setw(5) << size << endl;
    }
};


class Memory {
private:
    RD *head;
    int maxsize;
    int j_number;

public:
    Memory();
    ~Memory() {del(head);}
    void del(RD *p);

    void run();
    void print();

    bool request_first();
    bool request_fixed();
    bool request_nfixed();
    void release();

    int get_input_size();
    RD *get_pre(RD *p);
};

Memory::Memory() {
    head = new RD();
    j_number = 0;
}

void Memory::del(RD *p) {
    if (p) {
        del(p->next);
        delete p;
    }
}

void Memory::run() {
    cout << "��������ռ�: ";
    cin >> maxsize;
    head->next = new RD(0,0,0,maxsize);

    int method;
    cout << "����: 1.�״� 2.���ʺ� 3.��ʺ� ";
    cin >> method;
    while(method!=1 && method!=2 && method!= 3) {
        cout << "��������ȷ�����!" << endl;
        cout << "����: 1.�״� 2.���ʺ� 3.��ʺ� ";
        cin >> method;
    }

    while (1) {
        int fun;
        cout << "����Ҫʹ�õĹ���: 1.���� 2.�ͷ� 3.�˳� ";
        cin >> fun;

        switch (fun) {
            case 1:
                switch (method) {
                case 1:
                    request_first();
                    print();
                    break;
                case 2:
                    request_fixed();
                    print();
                    break;
                case 3:
                    request_nfixed();
                    print();
                    break;
                }
                break;
            case 2:
                release();
                print();
                break;
            case 3:
                return;
            default:
                cout << "��������ȷ�����!" << endl;
                break;
        }
    }
}

void Memory::print() {
	RD *p = head;
	while (p != NULL) {
		if (p != head) {
			p->print();
		}
        p = p->next;
	}
}

bool Memory::request_first() {
    int size = get_input_size()+1;
    RD *p = head;
	while (p != NULL) {
		if (!p->flag && (p->size + 1) >= size) {
			RD *new_ptr = new RD(1, ++j_number, p->addr+p->size-size+1, size-1);
			RD *tmp = p->next;
			new_ptr->next = tmp;
			p->next = new_ptr;
			p->size -= size;
			if (p->size == -1) {				
				get_pre(p)->next = p->next;
				delete p;				
			}
			cout << "�ɹ���" << endl;
			return true;
		}
        p = p->next;
	}
	cout << "�ռ䲻�㣡" << endl;
    return false;
}

bool Memory::request_fixed() {
    int size = get_input_size()+1;
    RD *p = head;
	RD *min_ptr = new RD(0, 0, 0, maxsize);
	while (p != NULL) {		
		if (!p->flag && (p->size+1) >= size && p->size <= min_ptr->size) {
			min_ptr = p;
		}
        p = p->next;
	}
	if (min_ptr->size+1 >= size) {
		RD *new_ptr = new RD(1, ++j_number, min_ptr->addr+min_ptr->size-size+1, size-1);
		RD *tmp = min_ptr->next;
		new_ptr->next = tmp;
		min_ptr->next = new_ptr;
		min_ptr->size -= size;
		if (min_ptr->size == -1) {
			get_pre(min_ptr)->next = min_ptr->next;
			delete min_ptr;
		}
		cout << "�ɹ���" << endl;
		return true;
	}
	cout << "�ռ䲻�㣡" << endl;
    return false;
}

bool Memory::request_nfixed() {
    int size = get_input_size()+1;
    RD *p = head;
	RD *max_ptr = p->next;
	while (p != NULL) {
		if (!p->flag && (p->size+1) >= size && p->size >= max_ptr->size) {
			max_ptr = p;
		}
        p = p->next;
	}
	if (max_ptr->size+1 >= size) {
		RD *new_ptr = new RD(1, ++j_number, max_ptr->addr+max_ptr->size-size+1, size-1);
		RD *tmp = max_ptr->next;
		new_ptr->next = tmp;
		max_ptr->next = new_ptr;
		max_ptr->size -= size;
		if (max_ptr->size == -1) {
			get_pre(max_ptr)->next = max_ptr->next;
			delete max_ptr;
		}
		cout << "�ɹ���" << endl;
		return true;
	}
	cout << "�ռ䲻�㣡" << endl;
    return false;
}

void Memory::release() {
    int j;
    cout << "����Ҫ�ͷŵĽ��̺�: ";
    cin >> j;

    //��ȡҪ�ͷŽ��̵�ָ��
    RD *p_release = head;
	while (p_release) {
		if (p_release->number == j && p_release->flag) {
            break;
		}
        p_release = p_release->next;
	}

    //��ȡǰһ�����ָ��
    RD *pre = get_pre(p_release);

    if (!p_release) {
        cout << "�޴˽���!" << endl;
    } else if (pre == head && p_release->next) {
        if (p_release->next->flag) {
			p_release->flag = 0;
			p_release->number = 0;
		}
		else {
			p_release->next->addr -= (p_release->size + 1);
			p_release->next->size += (p_release->size + 1);
			head->next = p_release->next;
			delete p_release;
		}
    } else if (pre == head && !p_release->next) {
        p_release->flag = 0;
		p_release->number = 0;
    } else if (pre != head && !p_release->next) {
        if (pre->flag) {
			p_release->flag = 0;
			p_release->number = 0;
			return;
		}
		else {
			pre->size += (p_release->size + 1);
			pre->next = NULL;
			delete p_release;
		}
    } else if (pre != head && p_release->next) {
        if (pre->flag && p_release->next->flag) {
            p_release->flag = 0;
            p_release->number = 0;
        } else if (!pre->flag && p_release->next->flag) {
            pre->size += (p_release->size + 1);			
            pre->next = p_release->next;
            delete p_release;
        } else if (pre->flag && !p_release->next->flag) {
            p_release->next->size += (p_release->size + 1);
            p_release->next->addr = p_release->addr;
            pre->next = p_release->next;
            delete p_release;
        } else if (!pre->flag && !p_release->next->flag) {
            pre->size += (p_release->size + 1);
            pre->size += (p_release->next->size + 1);
            pre->next = p_release->next->next;
            delete p_release->next;
            delete p_release;
        }
    }
}

int Memory::get_input_size() {
    int size;
    cout << "���������С: ";
    cin >> size;
    return size;
}

RD *Memory::get_pre(RD *p) {
    RD *temp = head;
    while (temp) {
		if (temp->next == p) {
			return temp;
		}
        temp = temp->next;
	}
	return NULL;
}

int main() {
    Memory m;
    m.run();
    return 0;
}
