#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <typename T>
struct BTNode {
    T data;
    int count;
    BTNode<T> *lc, *rc;
    BTNode(): lc(NULL), rc(NULL), count(1) {}
    BTNode(T x, BTNode<T> *l=NULL, BTNode<T> *r=NULL)
        :data(x), lc(l), rc(r), count(1) {}
};

template <typename T>
class BinTree {
public:
    BinTree(): root(NULL) {}
    ~BinTree() {destory();}
    void Print_CinPre() {
        for (int i=0; i<vecPre.size(); i++) cout << vecPre[i];
        cout << endl;
    }
    void Print_CinIn() {
        for (int i=0; i<vecIn.size(); i++) cout << vecIn[i];
        cout << endl;
    }
    void Print_CinPost() {
        for (int i=0; i<vecPost.size(); i++) cout << vecPost[i];
        cout << endl;
    }
    void destory() {return destory(root);} //ɾ�����нڵ�
    void CreateBinTree_PreIn(); // ǰ���������������
    void CreateBinTree_PostIn(); // �����������������
    void CreateBinTree_List(); // �������������
    bool IsEmpty() {return (!root)?true:false;} // �ж��Ƿ�Ϊ��
    int Height() {return Height(root);} // ��ȡ�������߶�
    int Size() {return Size(root);} // ��ȡ�������������
    int getLevel(BTNode<T> *current); // ��ȡ��ǰ�ڵ�߶�
    BTNode<T> *Parent(BTNode<T> *current) { // ��ȡ��ǰ�ڵ�ĸ��ڵ�ָ��
        return (!root || root==current)?NULL:Parent(root, current);
    }
    BTNode<T> *getRoot()const {return root;} // ��ȡ���ڵ�ָ��
    void preOrder() { // ǰ�����
        vector<T> vec;
        preOrder(root, vec);
        for (int i=0; i<vec.size(); i++) cout << vec[i];
        cout << endl;
    }
    void inOrder() { // �������
        vector<T> vec;
        inOrder(root, vec);
        for (int i=0; i<vec.size(); i++) cout << vec[i];
        cout << endl;
    }
    void postOrder() { // �������
        vector<T> vec;
        postOrder(root, vec);
        for (int i=0; i<vec.size(); i++) cout << vec[i];
        cout << endl;
    }
    void Print() {Print(root);} // ���뷨���������

    int LeafNodeNum() {return LeafNodeNum(root);} // 5-23(1)��ȡҶ�������
    void Conversion() {Conversion(root);} // 5-23(2)��ת���������������Һ��ӣ�
    bool Find_PrintAncestor(T x); // 5-26���ҽ�㲢����������Ƚڵ�
    BTNode<T> *Find(T x) {return Find(root ,x);} //���ҽ�㲢���ؽ��ָ��
    void PrintAncestor(BTNode<T> *subTree); // ����������Ƚ��
    bool IsBst(); // �ж��Ƿ�����
    void Insert(T tdata) {Insert(tdata, root);} // �����㣬������count++
    void RemoveMax(); // ɾ�������

protected:
    BTNode<T> *root;
    vector<T> vecPre, vecIn, vecPost;
    void destory(BTNode<T> *subTree);
    BTNode<T> *CreateBinTree_PreIn(int preStart, int preEnd, int inStart, int inEnd);
    BTNode<T> *CreateBinTree_PostIn(int preStart, int postEnd, int inStart, int inEnd);
    int Height(BTNode<T> *subTree);
    int Size(BTNode<T> *subTree);
    BTNode<T> *Parent(BTNode<T> *subTree, BTNode<T> *current);
    void preOrder(BTNode<T> *subTree, vector<T> &out);
    void inOrder(BTNode<T> *subTree, vector<T> &out);
    void postOrder(BTNode<T> *subTree, vector<T> &out);
    void Print(BTNode<T> *subTree);

    int LeafNodeNum(BTNode<T> *subTree);
    void Conversion(BTNode<T> *subTree);
    BTNode<T> *Find(BTNode<T> *subTree, T x);
    void Insert(T tdata, BTNode<T> *&subTree);
};

template <typename T>
void BinTree<T>::destory(BTNode<T> *subTree) {
    if (subTree) {
        destory(subTree->lc);
        destory(subTree->rc);
        delete subTree;
    }
};

template <typename T>
void BinTree<T>::CreateBinTree_PreIn() {
    destory(); root = NULL;
    vecPre.clear(); vecIn.clear();
    cout << "ǰ��(';'��ʾ����)��";
    T c; cin >> c;
    while (';' != (char)c) {
        vecPre.push_back(c);
        cin >> c;
    }
    cout << "����(';'��ʾ����)��";
    cin >> c;
    while (';' != (char)c) {
        vecIn.push_back(c);
        cin >> c;
    } 
    if(vecPre.size() != vecIn.size()) {
        cout << "error:ǰ�����򳤶Ȳ���ȣ�" << endl;
        return;
    }
    if (vecPre.size()==0 || vecIn.size()==0) return;
    root = CreateBinTree_PreIn(0, vecPre.size()-1, 0, vecIn.size()-1);
};

template <typename T>
BTNode<T> *BinTree<T>::CreateBinTree_PreIn(int preStart, int preEnd, int inStart, int inEnd) {
    if(preStart>preEnd || inStart > inEnd) return NULL;
    BTNode<T> *p = new BTNode<T>(vecPre[preStart]);
    for(int i=inStart; i<=inEnd; i++) {
        if(vecIn[i] == vecPre[preStart]){
            p->lc = CreateBinTree_PreIn(preStart+1, preStart+i-inStart, inStart, i-1);
            p->rc = CreateBinTree_PreIn(preStart+i-inStart+1, preEnd, i+1, inEnd);
        }
    }
    return p;
}

template <typename T>
void BinTree<T>::CreateBinTree_PostIn() {
    destory(); root = NULL;
    vecPost.clear(); vecIn.clear();
    cout << "����(';'��ʾ����)��";
    T c; cin >> c;
    while (';' != (char)c) {
        vecPost.push_back(c);
        cin >> c;
    }
    cout << "����(';'��ʾ����)��";
    cin >> c;
    while (';' != (char)c) {
        vecIn.push_back(c);
        cin >> c;
    }
    if(vecPost.size() != vecIn.size()) {
        cout << "error:�������򳤶Ȳ���ȣ�" << endl;
        return;
    }
    if (vecPost.size()==0 || vecIn.size()==0) return;
    root = CreateBinTree_PostIn(0, vecPost.size()-1, 0, vecIn.size()-1);
};

template <typename T>
BTNode<T> *BinTree<T>::CreateBinTree_PostIn(int postStart, int postEnd, int inStart, int inEnd) {
    if(postStart > postEnd || inStart > inEnd) return NULL;
    BTNode<T> *p = new BTNode<T>(vecPost[postEnd]);
    for(int i=inStart; i<=inEnd; i++) {
        if(vecIn[i] == vecPost[postEnd]) {
            p->lc = CreateBinTree_PostIn(postStart, postStart-inStart+i-1, inStart, i-1);
            p->rc = CreateBinTree_PostIn(postStart-inStart+i, postEnd-1, i+1, inEnd);
        }
    }
    return p;
}

template <typename T>
void BinTree<T>::CreateBinTree_List() {
    destory(); root = NULL;
    stack<BTNode<T> *> s;
    BTNode<T> *p, *t; int k;
    cout << "�����(';'��ʾ����)��";
    T c; cin >> c;
    while (';' != (char)c) {
        switch ((char)c) {
            case '(': s.push(p); k=1; break;
            case ')': t=s.top(); s.pop(); break;
            case ',': k=2; break;
            default: p = new BTNode<T>(c);
                if (!root) root = p;
                else if (1 == k) {
                    t = s.top(); t->lc = p;
                } else {
                    t = s.top(); t->rc = p;
                }
        }
        cin >> c;
    }
};

template <typename T>
int BinTree<T>::Height(BTNode<T> *subTree) {
    if (!subTree) return 0;
    else {
        int i = Height(subTree->lc);
        int j = Height(subTree->rc);
        return (i<j)? j+1: i+1;
    }
};

template <typename T>
int BinTree<T>::Size(BTNode<T> *subTree) {
    if (!subTree) return 0;
    else return 1+Size(subTree->lc)+Size(subTree->rc);
};

template <typename T>
int BinTree<T>::getLevel(BTNode<T> *current) {
    if (root == current) return 1;
    else return 1 + getLevel(Parent(current));
};

template <typename T>
BTNode<T> *BinTree<T>::Parent(BTNode<T> *subTree, BTNode<T> *current) {
    if (!subTree) return NULL;
    if (subTree->lc == current || subTree->rc == current) return subTree;
    BTNode<T> *p = Parent(subTree->lc, current);
    if (p) return p;
    else return Parent(subTree->rc, current);
};

template <typename T>
void BinTree<T>::preOrder(BTNode<T> *subTree, vector<T> &out) {
    if (subTree) {
        out.push_back(subTree->data);
        preOrder(subTree->lc, out);
        preOrder(subTree->rc, out);
    }
};

template <typename T>
void BinTree<T>::inOrder(BTNode<T> *subTree, vector<T> &out) {
    if (subTree) {
        inOrder(subTree->lc, out);
        out.push_back(subTree->data);
        inOrder(subTree->rc, out);
    }
};

template <typename T>
void BinTree<T>::postOrder(BTNode<T> *subTree, vector<T> &out) {
    if (subTree) {
        postOrder(subTree->lc, out);
        postOrder(subTree->rc, out);
        out.push_back(subTree->data);
    }
};  

template <typename T>
void BinTree<T>::Print(BTNode<T> *subTree) {
    if (!subTree) return;
    Print(subTree->rc);
    int x = getLevel(subTree) - 1;
    while (x--) cout << '\t';
    cout << subTree->data << endl;
    Print(subTree->lc);
};

template <typename T>
int BinTree<T>::LeafNodeNum(BTNode<T> *subTree) {
    if (!subTree) return 0;
    else if (!subTree->lc && !subTree->rc) return 1;
    else {
        int i = LeafNodeNum(subTree->lc);
        int j = LeafNodeNum(subTree->rc);
        return i+j;
    }
};

template <typename T>
void BinTree<T>::Conversion(BTNode<T> *subTree) {
    if (subTree) {
        BTNode<T> *p = subTree->lc;
        subTree->lc = subTree->rc;
        subTree->rc = p;
        Conversion(subTree->lc);
        Conversion(subTree->rc);
    }
};

template <typename T>
bool BinTree<T>::Find_PrintAncestor(T x) {
    BTNode<T> *p = Find(root, x);
    if (!p) return false;
    PrintAncestor(p);
};

template <typename T>
BTNode<T> *BinTree<T>::Find(BTNode<T> *subTree, T x) {
    if (!subTree) return NULL;
    if (x == subTree->data) return subTree;
    else {
        BTNode<T> *p = Find(subTree->lc, x);
        if (p) return p;
        else return Find(subTree->rc, x);
    }
};

template <typename T>
void BinTree<T>::PrintAncestor(BTNode<T> *subTree) {
    if (!subTree) return;
    BTNode<T> *p = Parent(root, subTree);
    if (p != root) {
        cout  << " <- " << p->data;
        PrintAncestor(p);
    }
    else if (p == root) cout << " <- "<< p->data << endl;
};

template <typename T>
bool BinTree<T>::IsBst() {
    vector<T> vec;
    inOrder(root, vec);
    int size = vec.size();
    for (int i=0; i<size-1; i++) {
        if (vec[i] >= vec[i+1]) {
            return false;
        }
    }
    return true;
}

template <typename T>
void BinTree<T>::Insert(T tdata, BTNode<T> *&subTree) {
    if (!subTree) subTree = new BTNode<T>(tdata);
    else {
        if (subTree->data == tdata) subTree->count++;
        else if (tdata < subTree->data)
            Insert(tdata, subTree->lc);
        else Insert(tdata, subTree->rc);
    }
}

template <typename T>
void BinTree<T>::RemoveMax() {
    BTNode<T> *subTree = root;
    if (!subTree) return;
    stack<BTNode<T> *> st;
    while(subTree->rc) {
        st.push(subTree);
        subTree = subTree->rc;
    }
    if (subTree->lc) {
        if (st.empty()) {
            root = subTree->lc;
        } else {
            st.top()->rc = subTree->lc;
        }
    } else {
        if (st.empty()) {
            root = NULL;
        } else {
            st.top()->rc = NULL;
        }
    }
    delete subTree;
}
