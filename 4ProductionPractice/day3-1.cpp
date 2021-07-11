#include <iostream>
#include <stdlib.h>
using namespace std;

/* ���ܣ��ַ�����ת
 * ������char* �ַ���ָ��, int �ַ�������
 * ����ֵ��void
 * ���ߣ����ӳ�20171002448
 */
void reverseStr(char *s, int len) {
    if(!s) return;
    int low=0, high=len-1;
    while (low<high) {
        char c = s[low];
        s[low] = s[high];
        s[high] = c;
        low++; high--;
    }
}

/* ���ܣ��ַ������
 * ������char* �ַ���ָ��
 * ����ֵ��void
 * ���ߣ����ӳ�20171002448
 */
void printStr(char *s) {
    cout << s;
}

/* ���ܣ��ַ���ת����
 * ��������
 * ����ֵ��void
 * ���ߣ����ӳ�20171002448
 */
void test() {
    char s[10];
    for (int test_num=0; test_num<20; test_num++) {
        printf("--�� %d �β���--\n", test_num);
        
        for (int i=0; i<10; i++) { //��������ַ���
            int a = rand()%80 + 33; //�������ascii��33-113���ַ�����һ��
            s[i] = char(a);
        }
        int len = sizeof(s)/sizeof(char);
        
        cout << "old str�� ";
        printStr(s);
        reverseStr(s, len);
        cout << "reversed str�� ";
        printStr(s);
        cout <<endl;
    }
}

int main () {
    test();
    return 0;
}
