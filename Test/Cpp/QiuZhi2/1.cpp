#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * �����е����������������������Ѿ�ָ���������޸ģ�ֱ�ӷ��ط����涨��ֵ����
     * 
     * @param a int����vector<vector<>> ��һ������
     * @param b int����vector<vector<>> �ڶ�������
     * @return int����vector<vector<>>
     */
    vector<vector<int> > solve(vector<vector<int> >& a, vector<vector<int> >& b) {
        // write code here
        vector<vector<int>> resault;
        int n = a.size();
        for (int i=0; i<n; i++) { // ��
            vector<int> v; resault.push_back(v);
            for (int j=0; j<n; j++) { //��
                int sum = 0;
                for (int x=0; x<n; x++) {
                    sum += a[i][x] * b[x][j];
                }
                resault[i].push_back(sum);
            }
        }
        return resault;
    }
};

int main() {
    
    return 0;
}