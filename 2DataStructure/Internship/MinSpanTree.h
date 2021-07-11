#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 10000
#define FILENAME "mst.txt"

struct Graph {
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
};

int InDegree(Graph G, int v) {
	int sum = 0;
	for (int i=0; i<G.numVertexes; i++) {
		if (G.arc[i][v] != INFINITY && G.arc[i][v] != 0)
			sum += 1;
	}
	return sum;
}

struct Edge {
    int begin, end, weight;
};

class MSTree {
protected:
    Graph *G;
	ofstream ofile;
public:
    MSTree();
    ~MSTree();
    void Swapn(Edge *edges,int i, int j);
    void sort(Edge *edges);
    int Find(int *parent, int f);
    void Kruskal();
    void Prim();
    void Print_Graph();
};

MSTree::MSTree() {
	ofile.open(FILENAME, ios::out);
    G = new Graph();
    int i, j;
	int a, b, c; 

    cout << "��������������";
    cin >> G->numEdges >> G->numVertexes;

	for (i = 0; i < G->numVertexes; i++) {
		for ( j = 0; j < G->numVertexes; j++) {
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	cout << "����߼�(�����0 ~ n-1)��" << endl;
	for (i = 0; i < G->numEdges; i++) {
		cin >> a >> b >> c;
		G->arc[a][b] = c;
	}

	for(i = 0; i < G->numVertexes; i++) {
		for(j = 0; j < G->numVertexes; j++) {
			if (G->arc[i][j]!=0 && G->arc[i][j]!=INFINITY)
				G->arc[j][i] =G->arc[i][j];
		}
	}
	cout << endl;
}

MSTree::~MSTree() {
    delete G;
	ofile.close();
}

void MSTree::Swapn(Edge *edges,int i, int j) {
    int temp;
	temp = edges[i].begin;
	edges[i].begin = edges[j].begin;
	edges[j].begin = temp;
	temp = edges[i].end;
	edges[i].end = edges[j].end;
	edges[j].end = temp;
	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
}

void MSTree::sort(Edge edges[])
{
	int i, j;
	for ( i = 0; i < G->numEdges; i++) {
		for ( j = i + 1; j < G->numEdges; j++) {
			if (edges[i].weight > edges[j].weight) {
				Swapn(edges, i, j);
			}
		}
	}
}

int MSTree::Find(int *parent, int f) {
    while ( parent[f] > 0) {
		f = parent[f];
	}
	return f;
}

void MSTree::Kruskal(){
    int i, j, n, m;
	int k = 0, sum = 0;
	int parent[MAXVEX]; // ����һ���������жϱ�����Ƿ��γɻ�·
	
	Edge edges[MAXEDGE]; // ����߼�����,edge�ĽṹΪbegin,end,weight,��Ϊ����

	// ���������߼����鲢����
	for ( i = 0; i < G->numVertexes-1; i++) {
		for (j = i + 1; j < G->numVertexes; j++) {
			if (G->arc[i][j]<INFINITY) {
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G->arc[i][j];
				k++;
			}
		}
	}
	sort(edges);

	for (i = 0; i < G->numVertexes; i++)
		parent[i] = 0; // ��ʼ������ֵΪ0

	cout << "��С������(Kruskal)��\n";
	for (i = 0; i < G->numEdges; i++) { // ѭ��ÿһ����
		n = Find(parent,edges[i].begin);
		m = Find(parent,edges[i].end);
		if (n != m) { // ����n��m���ȣ�˵���˱�û�������е��������γɻ�·
			parent[n] = m;	// ���˱ߵĽ�β��������±�Ϊ����parent��
							// ��ʾ�˶����Ѿ���������������
			cout << setw(3) << edges[i].begin << setw(3) << edges[i].end << setw(3) << edges[i].weight << endl;
			ofile << setw(3) << edges[i].begin << setw(3) << edges[i].end << setw(3) << edges[i].weight << endl;
            sum += edges[i].weight;
		}
	}
    cout << "��Ȩֵ��"  << sum << endl;
	cout << endl;
	ofile << endl;
}

void MSTree::Prim() {
    int min, i, j, k;
    int sum = 0;
	int adjvex[MAXVEX];		// ������ض����±�
	int lowcost[MAXVEX];	// ������ض����ߵ�Ȩֵ 
	lowcost[0] = 0;// ��ʼ����һ��ȨֵΪ0����v0���������� 
			// lowcost��ֵΪ0����������Ǵ��±�Ķ����Ѿ����������� 
	adjvex[0] = 0;			// ��ʼ����һ�������±�Ϊ0 
	for(i = 1; i < G->numVertexes; i++)	{ // ѭ�����±�Ϊ0���ȫ������ 
		lowcost[i] = G->arc[0][i];	// ��v0������֮�бߵ�Ȩֵ�������� 
		adjvex[i] = 0;					// ��ʼ����Ϊv0���±� 
	}
	cout << "��С������(Prim)��\n";
	for(i = 1; i < G->numVertexes; i++) {
		min = INFINITY;	// ��ʼ����СȨֵΪ��
		j = 1;k = 0;
		while(j < G->numVertexes) { // ѭ��ȫ������
			if(lowcost[j]!=0 && lowcost[j] < min) { // ������СȨֵ��min
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		cout << setw(3) << adjvex[k] << setw(3) << k << setw(3) << G->arc[adjvex[k]][k] << endl;// ��ӡ��ǰ�������Ȩֵ��С�ı� 
		ofile << setw(3) << adjvex[k] << setw(3) << k << setw(3) << G->arc[adjvex[k]][k] << endl;
        sum += G->arc[adjvex[k]][k];
		lowcost[k] = 0;// ����ǰ�����Ȩֵ����Ϊ0,��ʾ�˶����Ѿ�������� 
		for(j = 1; j < G->numVertexes; j++)	{ // ѭ�����ж��� 
			if(lowcost[j]!=0 && G->arc[k][j] < lowcost[j]) { // ����±�Ϊk�������ȨֵС�ڴ�ǰ��Щ����δ������������Ȩֵ 
				lowcost[j] = G->arc[k][j];// ����С��Ȩֵ����lowcost��Ӧλ�� 
				adjvex[j] = k;				// ���±�Ϊk�Ķ������adjvex 
			}
		}
	}
    cout << "��Ȩֵ��" << sum << endl;
	cout << endl;
}

void MSTree::Print_Graph() {
	cout << "�ڽӾ���" << endl;
    for (int i = 0; i < G->numVertexes; i++) {
		for (int j = 0; j < G->numVertexes; j++) {
            if (G->arc[i][j] == INFINITY)
                cout <<  setw(4) << "**";
            else
			    cout << setw(4) << G->arc[i][j];
		}
        cout << endl;
	}
	cout << endl;
}
