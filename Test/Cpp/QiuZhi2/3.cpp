#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * �����е����������������������Ѿ�ָ���������޸ģ�ֱ�ӷ��ط����涨��ֵ����
     * ����������֮��
     * @param s string�ַ��� ��ʾ��һ������
     * @param t string�ַ��� ��ʾ�ڶ�������
     * @return string�ַ���
     */
    string solve(string s, string t) {
        // write code here
        reverse(s.begin(),s.end());
        reverse(t.begin(),t.end());
        int n = s.length()>t.length()?s.length():t.length();
        string out;
        int is_up = 0;
        for (int i=0; i<n; i++) {
            int s_int = i<s.length()?(int) (s[i] - '0'):0;
            int t_int = i<t.length()?(int) (t[i] - '0'):0;
            int sum = (s_int + t_int + is_up) % 10;
            is_up = (s_int + t_int + is_up) / 10;
            out.push_back((char) (sum + '0'));
            if(i == n-1) {
                if (is_up == 1) {
                    out.push_back('1');
                }
            }
        }
        string out_s = out;
        reverse(out_s.begin(),out_s.end());
        return out_s;
    }
};

int main() {
    string s = "11";
    string t = "123";
    Solution so;
    cout << so.solve(s,t) << endl;
    return 0;
}