#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    /**
     * �����е����������������������Ѿ�ָ���������޸ģ�ֱ�ӷ��ط����涨��ֵ����
     * 
     * @param a string�ַ��� �������ַ���
     * @return int����
     */
    int solve(string a) {
        // write code here
        // �������Ӳ���Ϊ2��ʼ����
        // int max = 0;
        // int step_len = 2;
        // for (int i=0; i<a.length()-step_len+1; i++) {
        //     for (int j=step_len; j<=a.length()-i; j+=2) {
        //         int begin_1 = i;
        //         int begin_2 = i+j/2;
        //         int t = 0;
        //         int x;
        //         for (x=0; x<j/2; x++) {
        //             if (a[begin_1+x] == a[begin_2+x]) {
        //                 t++;
        //             } else break;
        //         }
        //         if(x == j/2) {
        //             if (max < t*2) max = t*2;
        //             step_len = t+1;
        //         }
        //     }
        // }
        // return max;

        // ʹ�ã��Ӳ������ʼ����
        int max = 0;
        int step = a.length()%2?a.length()-1:a.length();
        int flag = 0;
        for (; step>1; step-=2) {
            for (int i=0; i+step<=a.length(); i++) {
                int begin_1 = i;
                int begin_2 = i+step/2;
                int x=0;
                while (a[begin_1+x] == a[begin_2+x]) {
                    x++;
                }
                if (x == step/2) {
                    max = step;
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
        return max;
    }
};

int main() {
    string a; a="q1qwertyuiopasdfghjklzxcvbnmq1qwertyuiopasdfghjklzxcvbnmabc";
    Solution s;
    cout << s.solve(a) << endl;
    return 0;
}