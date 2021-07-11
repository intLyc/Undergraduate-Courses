#ifndef LMS_H
#define LMS_H

#include <iostream>
#include "BTree.h"
#include "Book.h"
#include "LInfo.h"

using namespace std;

const int LEND_TIME = 7;

class LMS {
public:
    LMS();
    ~LMS();

    void setTime(); // ���õ�ǰʱ��
    void insert(); // �ɱ����
    void remove(); // ������
    void lend(); // ����
    void back(); // �黹
    void show(); // ��ʾ

    void showAuthor(); // �г�ĳ����ȫ������
    void showBook(); // �г�ĳ��״̬
    void subscribe(); // ԤԼ����

    void run();

private:
    BTree<Book> *bt;
    LInfo *linfo;
    LInfo *subLinfo;
    int datenow;
};

LMS::LMS() {
    bt = new BTree<Book>();
    linfo = new LInfo();
    subLinfo = new LInfo();
    datenow  = 0;
}

LMS::~LMS() {
    delete bt;
    delete linfo;
    delete subLinfo;
}

void LMS::setTime() {
    cout << "�����뵱ǰʱ�䣺";
    cin >> datenow;
    cout << "Success!" << endl;
}

void LMS::insert() {
    int input = 1;
    int k; string n; string a; int as;
    while (input != 0) {
        cout << "������Ҫ���������š����������ߡ�������";
        cin >> k >> n >> a >> as;
        Book *t = new Book(k,n,a,as,as);
        Book *b;
        if (bt->get(*t, b)) {
            if (b->name != n || b->author != a) {
                cout << "������Ϣ������" << endl << "Faild!" << endl;
                continue;
            }
            b->amountNow += as;
            b->amountSum += as;
            cout << "Success!" << endl;
            return;
        }
        bt->insert(*t)? cout << "Success!" << endl: cout << "Faild!" << endl;
        cout << "����0ֹͣ��ӣ�����1������ӣ�";
        cin >> input;
    }
}

void LMS::remove() {
    cout << "������Ҫ���������ţ�";
    int k;
    cin >> k;
    Book b(k);
    bt->remove(b)? cout << "Success!" << endl: cout << "Faild!" << endl;
}

void LMS::lend() {
    cout << "��������ĵ���š�ͼ��֤�ţ�";
    int k, n;
    cin >> k >> n;
    Book b(k);
    if (bt->contain(b)) {
        Book *book;
        bt->get(b, book);
        if (book->amountNow <= 0) {
            cout << "��ͼ����û�п�棡" << endl;
        } else {
            book->amountNow--;
            linfo->add(k, n, datenow, datenow+LEND_TIME);
            cout << "���ĳɹ�����" << LEND_TIME << "��֮�ڹ黹������Ҫ�����ڽ�1��/�죩" << endl;
        }
    } else {
        cout << "�ֿ�û�и��飡" << endl;
    }
}

void LMS::back() {
    cout << "������Ҫ�黹����š�ͼ��֤�ţ�";
    int k, n;
    cin >> k >> n;
    Book b(k);
    if (!bt->contain(b)) {
        cout << "��Ŵ��󣬲ֿ�û�и��飡" << endl;
    } else {
        if (!linfo->contain(k, n)) {
            cout << "�黹��Ϣ���󣨹黹�����޴���Ϣ��!" << endl;
        } else {
            Book *book;
            bt->get(b, book);
            if (book->amountNow >= book->amountSum) {
                cout << "�黹��Ϣ���󣨸������������ޣ���" << endl;
            } else {
                Info *info;
                linfo->search(n, info);
                if (datenow > info->rdate) {
                    cout << "�����ڣ��븶���ڽ�" << (datenow-info->rdate)*1 << "Ԫ��" << endl;
                } else {
                    cout << "�黹�ɹ���" << endl;
                }
                linfo->del(n);
                if (book->amountNow == 0) { // �黹ǰû�п��,����ԤԼ��Ϣ����
                    if (subLinfo->contain(k)) { // ��Ԥ������ļ�¼
                        Info *get;
                        subLinfo->getDeleteFirst(k, get);
                        linfo->add(get->key, get->number, datenow, datenow+LEND_TIME);
                        cout << endl << "~~ϵͳ��ʾ~~" << endl;
                        cout << "����֤��Ϊ��" << get->number << "�����û��������Ϊ��" << get->key << "���������п�棬��ȡ�飡" << endl;
                        cout << "���ĳɹ�����" << LEND_TIME << "��֮�ڹ黹������Ҫ�����ڽ�1��/�죩" << endl;
                        delete get;
                        return;
                    }
                }
                book->amountNow++;
            }
        }
    }
}

void LMS::show() {
    bt->display();
}

void LMS::showAuthor() {
    cout << "������������:";
    string input;
    cin >> input;
    bt->printAuthor(input);
}

void LMS::showBook() {
    cout << "������Ҫ���ҵ���ţ�";
    int k;
    cin >> k;
    Book b(k);
    if (!(bt->contain(b))) {
        cout << "�ֿ�û�и��飡" << endl;
    } else {
        Book *book;
        bt->get(b, book);
        cout << "��ţ�" << book->key << endl
            << "������" << book->name << endl
            << "���ߣ�" << book->author << endl
            << "��棺" << book->amountNow << "/" << book->amountSum << endl;
        if (book->amountNow == book->amountSum) {
            cout << "���鵱ǰû�н��ļ�¼" << endl;
        } else {
            linfo->infoOut(k, datenow);
        }
    }
}

void LMS::subscribe() {  
    cout << "������Ԥ������š�ͼ��֤�ţ�";
    int k, n;
    cin >> k >> n;
    Book b(k);
    if (bt->contain(b)) {
        Book *book;
        bt->get(b, book);
        if (book->amountNow <= 0) { // û�п��
            subLinfo->add(k, n, datenow, datenow);
            cout << "��ǰ�������޿�棬ϵͳ�����п��ʱ��������" << endl;
        } else {
            book->amountNow--;
            linfo->add(k, n, datenow, datenow+LEND_TIME);
            cout << "��ǰ�п�棬���ĳɹ�����" << LEND_TIME << "��֮�ڹ黹������Ҫ�����ڽ�1��/�죩" << endl;
        }
    } else {
        cout << "�ֿ�û�и��飡" << endl;
    }

    // �˶���������Ҫ��
    // cout << "������Ԥ������š�ͼ��֤�š�Ԥ�����ڡ�����������";
    // int k, n, l, d;
    // cin >> k >> n >> l >> d;
    // Book b(k);
    // if (bt->contain(b)) {
    //     Book *book;
    //     bt->get(b, book);
    //     if (book->amountNow <= 0) { // û�е�ǰ���
    //         if (book->amountNow + linfo->subAmount(k, l) <= 0) {
    //             cout << "��ͼ�鵽Ԥ��ʱ����û�п�棡" << endl;
    //         } else {
    //             book->amountNow--;
    //         linfo->add(k, n, l, l+d);
    //         cout << "Ԥ���ɹ���" << endl;
    //         }
    //     } else {
    //         book->amountNow--;
    //         linfo->add(k, n, l, l+d);
    //         cout << "Ԥ���ɹ���" << endl;
    //     }
    // } else {
    //     cout << "�ֿ�û�и��飡" << endl;
    // }
}

void LMS::run() {
    cout << "~~~~~~ͼ�����ϵͳ~~~~~~" << endl;
    while(1) {
        cout<< "      1.�ɱ����" << endl
            << "      2.������" << endl
            << "      3.����ͼ��" << endl
            << "      4.�黹ͼ��" << endl
            << "      5.��ʾ���" << endl
            << "      6.��������" << endl
            << "      7.ͼ��״̬" << endl
            << "      8.ԤԼ����" << endl
            << "      0.����ʱ��"  << endl
            << "     -1.�˳�" << endl
            << "������Ҫʹ�õĹ��ܣ�";
        int input;
        cin >> input;
        if(-1 == input) break;
        switch (input)
        {
            case 0:
                setTime();
                break;
            case 1:
                insert();
                break;
            case 2:
                remove();
                break;
            case 3:
                lend();
                break;
            case 4:
                back();
                break;
            case 5:
                show();
                break;
            case 6:
                showAuthor();
                break;
            case 7:
                showBook();
                break;
            case 8:
                subscribe();
                break;
            default:
                cout << "��������ȷѡ�" << endl;
                break;
        }
        system("pause");
    }
}

#endif // LMS_H