#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    while(1) {
        float x;
        int e,j=0,ne,o; //β�������롢���������
        cin >> x;

        x<0 ? ne=1 : ne=0;
        x = fabs(x);

        while(x<1||x>=2) { //����IEEE��׼�涨��λ��
            if(x<1) {x*=2;j--;}
            if(x>=2) {x/=2;j++;}
        }

        j += pow(2,7); //��������

        x -= 1;
        x *= pow(2,23); //������ȥ��С����
        e = x;
        ne *= pow(2,31); //����31λ
        j *= pow(2,23); //����23λ
        o = ne + j + e;
        cout << hex << o << endl << endl;
    }
    return 0;
}