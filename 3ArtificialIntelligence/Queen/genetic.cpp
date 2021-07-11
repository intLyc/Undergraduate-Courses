#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <time.h>
using namespace std;

class Genetic {
private:
    int m_Num;                                // �ʺ�����
    bool m_IsSuccess;                         // �Ƿ�ɹ��ҵ����Ž�
    vector<int>m_optimalSolution;             // ���Ž�.
    vector<vector<int> >m_population;          // ��Ⱥ
    vector<double>m_adaptive;                 // ��Ⱥ����Ӧֵ(1/��ͻ��)��
    vector<double>m_AdaptValue;               // �ۻ�����Ӧֵ(��λ��һ����ѡ�е�)
    

public:
    Genetic(int numOfQueens, int initialGroupNum);
    double CalcuAdaptive(vector<int> &state);         // ������Ӧֵ�������๥���Ļʺ������
    void SetPopulation();
    void Choose();                                    // ѡ��
    void GeneticCrossover();                          // �ӽ�
    void GeneticMutate();                             // ����
    void GeneticCalculation();
    void Print();                                     // ��ӡ���Ž�
};

Genetic::Genetic(int numOfQueens, int initialGroupNum) {
    m_adaptive.resize(initialGroupNum, 0);
    m_AdaptValue.resize(initialGroupNum, 0);
    m_Num = numOfQueens;
    m_IsSuccess = true;
    SetPopulation();
}

void Genetic::SetPopulation() {
    m_population.clear();
    vector<int> tmpState(m_Num, 0);
    for (int i = 0; i < m_adaptive.size(); ++i) {
        for (int j = 0; j < m_Num; ++j)       // ��ʼ��
            tmpState[j] = rand() % m_Num;
        m_population.push_back(tmpState);
        m_adaptive[i] = CalcuAdaptive(tmpState);
    }
}

double Genetic::CalcuAdaptive(vector<int> &state) {
    int conflict = 0;
    for (int i = 0; i < m_Num; ++i) {
        for (int j = i + 1; j < m_Num; ++j) {
            //����Խ��߷����๥�������ߴ�ֱ�����๥��
            if (state[i] == state[j] || abs(state[i] - state[j]) == j - i)
                conflict++;
        }
    }
    if (conflict == 0) {                     // �ҵ����Ž�
        m_IsSuccess = false;
        m_optimalSolution = state;             //���浱ǰ��״̬    
    }
    return 1.0 / conflict;
}

//��Ȼѡ�񣨴���˼·�����̶�ѡ��
void Genetic::Choose() {            
    vector<vector<int>> NewPopulation;    //����һ���µĿ���ȺNewPopulation
    m_AdaptValue[0] = m_adaptive[0];
    for (int i = 1; i < m_AdaptValue.size(); i++)
        m_AdaptValue[i] = m_AdaptValue[i - 1] + m_adaptive[i];
    double totalAdaptive = m_AdaptValue[m_AdaptValue.size() - 1];
    //��������ֲ����Ž�(��ֱ��ѡ����Ӧֵ��ߵ����������ӽ�)
    for (int i = 0; i < m_population.size(); i++) {

        //�������ŵ����̶�
        int magnifyTotalAdaptive = totalAdaptive * 100000;    //ʵ��->����(�Ŵ�)
        int random = (rand()*rand()) % magnifyTotalAdaptive;//ת������
        double select = (double)random / 100000;            //����ͬ������С
        
        //int select = rand()*rand() % ((int)totalAdaptive);
        vector<double>::iterator indexi;
        //���ֲ���: ��m_AdaptValue�в�����Ӧֵ��select��ӽ��ĸ�����±�
        indexi = lower_bound(m_AdaptValue.begin(), m_AdaptValue.end(), select);
        int indexj = indexi - m_AdaptValue.begin();
        //�����µ���Ⱥ��
        NewPopulation.push_back(m_population[indexj]);
    }
    // double min = 100;
    // double max = 0;
    // for (int i=0; i<m_adaptive.size(); ++i) {
    //     double x = double(m_adaptive[i])/totalAdaptive*100;
    //     if (x > max)
    //         max = x;
    //     if (x < min)
    //         min = x;
    // } cout  << max << ' ' << min<< endl;
    // int x; cin>>x;

    // ������Ⱥ
    m_population.clear();
    m_population = NewPopulation;
}

void Genetic::GeneticCrossover() {    //�ӽ�==>��������Ƭ��(�ʺ�λ�ý��н���)
    int first = 0;
    int row1;
    for (int i = 0; i < m_population.size(); i++) {
        if (rand() % 2) {
            ++first;
            if (first % 2 == 0) {
                int crossPoint = rand() % (m_Num - 1);
                for (int j = crossPoint; j < m_Num; j++)swap(m_population[row1][j], m_population[i][j]);  //ֵ����
            }
            else row1 = i;
        }
    }
}

void Genetic::Print() {
    for (int i = 0; i < m_optimalSolution.size(); ++i) {
        for (int j = 0; j < m_optimalSolution.size(); ++j) {
            if (j == m_optimalSolution[i]) cout << "Q ";
            else cout << ". ";
        }cout << '\n';
    }cout << '\n';
}

//���ͻ��=> ����ı�ĳ�������ĳ������(����ı�ĳ����ͼ�е�ĳ���ʺ��λ��)
void Genetic::GeneticMutate() {        
    int mutateSpot = 0;
    for (int i = 0; i < m_population.size(); ++i) {
        if (rand() % 2 == 0) {
            mutateSpot = rand() % m_Num;
            m_population[i][mutateSpot] = rand() % m_Num;
        }
        //m_adaptive[i] = CalcuAdaptive(m_population[i]);  // ������Ӧֵ
    }
}

void Genetic::GeneticCalculation() {
    clock_t start, finish;
    start = clock();
    int count = 0;
    while (m_IsSuccess) {
        count++;
        // ��Ȼѡ��
        Choose();
        // �ӽ�
        GeneticCrossover();
        // ����
        GeneticMutate();

        for (int i = 0; i < m_population.size(); ++i) {
            m_adaptive[i] = CalcuAdaptive(m_population[i]);  // ������Ӧֵ
        }
    }
    cout<<count<<endl;
    //��ӡ���Ž�
    //if (m_Num<25) Print();
    Print();
    finish = clock();
    cout << "�Ŵ��㷨���ʱ��: " << finish - start << "ms" << endl;
}

int main() {
srand((unsigned)time(NULL));

    while (1) {
    int numOfQueen;
    cout << "������ʺ���Ŀ: ";
    cin >> numOfQueen;
    cout << "���Ŵ��㷨��⡿" << endl;
    Genetic Q(numOfQueen, 100);
    Q.GeneticCalculation();
    system("pause");}
}
