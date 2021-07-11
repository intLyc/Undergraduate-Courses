#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <string>

using namespace std;

const int DEGREE = 4; //B���Ķȣ�������2-3-4��
const int DATA_MAX = DEGREE - 1;
const int DATA_MIN = 1; //������С����
const int CHILD_MAX = DATA_MAX + 1;
const int CHILD_MIN = DATA_MIN + 1;

template <typename T>
class BNode {
public:
    BNode() :isLeaf(true), num(0) {}

    bool isLeaf; //�ж��Ƿ���Ҷ�ӽڵ�
    int num; //��������
    T bData[DATA_MAX]; //��������
    BNode<T> *pChild[DEGREE]; //����ָ������
};

template <typename T>
class BTree {
public:
    BTree() {root = NULL;}
    ~BTree() {clear();}
    
    bool insert(T &data);
    bool remove(T &data);
    void display() {displayInConcavo(root, 13*5);}
    bool contain(T &data) {T *t; return search(root, data, t);}
    void clear() {recursive_clear(root); root = NULL;}
    bool get(T &data, T *&get) {return search(root, data, get);}
    void printAuthor(string a) {return printAuthor(root, a);}

private:
    void printAuthor(BNode<T> *pNode, string a);
    bool search(BNode<T> *pNode, T &data, T *&get);

    void insertNonFull(BNode<T> *pNode, T &data); //����������
    void recursive_remove(BNode<T> *pNode, T &data);

    void splitChild(BNode<T> *pParent, int nChildIndex, BNode<T> *pChild); //����
    void mergeChild(BNode<T> *pParent, int index); //�ϲ�
    void deleteNode(BNode<T> *&pNode); 

    void displayInConcavo(BNode<T> *pNode, int count);
    void recursive_clear(BNode<T> *pNode);

    T getPredecessor(BNode<T> *pNode); //��ǰ��
    T getSuccessor(BNode<T> *pNode); //�Һ��

    BNode<T> *root;
};

template <typename T>
bool BTree<T>::insert(T &data) {
    if (contain(data)) { //���ùؼ����Ƿ��Ѿ�����
        return false;
    } else {
        if (root == NULL) { //����Ƿ�Ϊ����
            root = new BNode<T>();
        }
        if (root->num == DATA_MAX) { //�����ڵ��Ƿ�����
            BNode<T> *pNode = new BNode<T>();  //�����µĸ��ڵ�
            pNode->isLeaf = false;
            pNode->pChild[0] = root;
            splitChild(pNode, 0, root);
            root = pNode;  //���¸��ڵ�ָ��
        }
        insertNonFull(root, data);
        return true;
    }
}

template <typename T>
bool BTree<T>::remove(T &data) {
    T *t;
    if (!search(root, data, t)) { //������
        return false;
    } else if (t->amountNow < t->amountSum) {
        cout << "���黹��" << t->amountSum - t->amountNow << "��δ�黹��" << endl
            << "����ղֿ�ʣ���飡" << endl;
        if (t->amountNow > 0) { 
            t->amountSum = t->amountSum - t->amountNow;
            t->amountNow = 0;
        }
        return true;
    }
    if (root->num == 1) { //�����������
        if (root->isLeaf) {
            clear();
            return true;
        } else {
            BNode<T> *pChild1 = root->pChild[0];
            BNode<T> *pChild2 = root->pChild[1];
            if (pChild1->num==DATA_MIN && pChild2->num==DATA_MIN) {
                mergeChild(root, 0);
                deleteNode(root);
                root = pChild1;
            }
        }
    }
    recursive_remove(root, data);
    return true;
}

template <typename T>
void BTree<T>::printAuthor(BNode<T> *pNode, string a) {
    if (pNode==NULL) { //���ڵ�ָ���Ƿ�Ϊ�գ���ýڵ��Ƿ�ΪҶ�ӽڵ�
        return;
    } else {
        for (int i=0; i<pNode->num; ++i) {
            if (a == pNode->bData[i].author) {
                cout << pNode->bData[i] << endl;
            }
        }
        if (pNode->isLeaf) { //���ýڵ��Ƿ�ΪҶ�ӽڵ�
            return;
        } else {
            for (int i=0; i<=pNode->num; ++i)
                printAuthor(pNode->pChild[i], a);
        }
    }
}

template <typename T>
bool BTree<T>::search(BNode<T> *pNode, T &data, T *&get) {
    if (pNode==NULL) { //���ڵ�ָ���Ƿ�Ϊ�գ���ýڵ��Ƿ�ΪҶ�ӽڵ�
        return false;
    } else {
        int i;
        for (i=0; i<pNode->num && data>*(pNode->bData+i); ++i); //�ҵ�ʹdata<=pNode->bData[i]��������С�±�i
        if (i<pNode->num && data==pNode->bData[i]) {
            get = &(pNode->bData[i]);
            return true;
        } else {
            if (pNode->isLeaf) { //���ýڵ��Ƿ�ΪҶ�ӽڵ�
                return false;
            } else {
                return search(pNode->pChild[i], data, get);
            }
        }
    }
}

template <typename T>
void BTree<T>::insertNonFull(BNode<T> *pNode, T &data) {
    int i = pNode->num; //��ȡ�ڵ��ڹؼ��ָ���
    if (pNode->isLeaf) { //pNode��Ҷ�ӽڵ�
        while (i>0 && data<pNode->bData[i-1]) { //�Ӻ���ǰ�����ҹؼ��ֵĲ���λ��
            pNode->bData[i] = pNode->bData[i-1]; //�����λ
            --i;
        }
        pNode->bData[i] = data; //����ؼ��ֵ�ֵ
        ++pNode->num; //���½ڵ�ؼ��ֵĸ���
    }
    else { //pNode���ڽڵ�
        while(i>0 && data<pNode->bData[i-1]) //�Ӻ���ǰ�����ҹؼ��ֵĲ��������
            --i;
        BNode<T> *pChild = pNode->pChild[i]; //Ŀ���������ָ�� 
        if (pChild->num == DATA_MAX) { //�����ڵ�����
            splitChild(pNode, i, pChild);//���������ڵ�
            if(data>pNode->bData[i])   //ȷ��Ŀ������
                pChild = pNode->pChild[i+1];
        }
        insertNonFull(pChild, data);  //����ؼ��ֵ�Ŀ�������ڵ�
    }
}

template <typename T>
void BTree<T>::recursive_remove(BNode<T> *pNode, T &data) {
    int i=0;
    while(i<pNode->num && data>pNode->bData[i])
        ++i;
    if (i<pNode->num && data==pNode->bData[i]) { //�ؼ���key�ڽڵ�pNode��
        if (pNode->isLeaf) { //pNode�Ǹ�Ҷ�ڵ�
            //��pNode��ɾ��k
            --pNode->num;
            for (; i<pNode->num; ++i) {
                pNode->bData[i] = pNode->bData[i+1];
            }
            return;
        } else { //pNode�Ǹ��ڽڵ�
            BNode<T> *pChildPrev = pNode->pChild[i]; //�ڵ�pNode��ǰ��key���ӽڵ�
            BNode<T> *pChildNext = pNode->pChild[i+1]; //�ڵ�pNode�к���key���ӽڵ�
            if (pChildPrev->num >= CHILD_MIN) { //�ڵ�pChildPrev�����ٰ���CHILD_MIN���ؼ���
                T prevKey = getPredecessor(pChildPrev); //��ȡkey��ǰ���ؼ���
                recursive_remove(pChildPrev, prevKey);
                pNode->bData[i] = prevKey; //�滻��key��ǰ���ؼ���
                return;
            } else if (pChildNext->num>=CHILD_MIN) { //�ڵ�pChildNext�����ٰ���CHILD_MIN���ؼ���
                T nextKey = getSuccessor(pChildNext); //��ȡkey�ĺ�̹ؼ���
                recursive_remove(pChildNext, nextKey);
                pNode->bData[i] = nextKey; //�滻��key�ĺ�̹ؼ���
                return;
            } else { //�ڵ�pChildPrev��pChildNext�ж�ֻ����CHILD_MIN-1���ؼ���
                mergeChild(pNode, i);
                recursive_remove(pChildPrev, data);
            }
        }
    } else { //�ؼ���key���ڽڵ�pNode��
        BNode<T> *pChildNode = pNode->pChild[i]; //����key���������ڵ�
        if (pChildNode->num == DATA_MIN) { //ֻ��t-1���ؼ���
            BNode<T> *pLeft = i>0 ? pNode->pChild[i-1] : NULL; //���ֵܽڵ�
            BNode<T> *pRight = i<pNode->num ? pNode->pChild[i+1] : NULL; //���ֵܽڵ�
            int j;
            if (pLeft && pLeft->num>=CHILD_MIN) { //���ֵܽڵ�������CHILD_MIN���ؼ���
                //���ڵ���i-1�Ĺؼ���������pChildNode��
                for (j=pChildNode->num; j>0; --j) {
                    pChildNode->bData[j] = pChildNode->bData[j-1];
                }
                pChildNode->bData[0] = pNode->bData[i-1];
                
                if (!pLeft->isLeaf) {
                    for (j=pChildNode->num+1; j>0; --j) { //pLeft�ڵ��к��ʵ���Ůָ����ֲ��pChildNode��
                        pChildNode->pChild[j] = pChildNode->pChild[j-1];
                    }
                    pChildNode->pChild[0] = pLeft->pChild[pLeft->num];
                }
                ++pChildNode->num;
                pNode->bData[i-1]/*����ԭ����[i]�����ڸ����˹���*/ = pLeft->bData[pLeft->num-1]; //pLeft�ڵ��е����ؼ���������pNode��
                --pLeft->num;
            } else if (pRight && pRight->num>=CHILD_MIN) { //���ֵܽڵ�������CHILD_MIN���ؼ���
                //���ڵ���i�Ĺؼ���������pChildNode��
                pChildNode->bData[pChildNode->num] = pNode->bData[i];
                ++pChildNode->num;
                pNode->bData[i] = pRight->bData[0]; //pRight�ڵ��е���С�ؼ���������pNode��
                --pRight->num;
                for (j=0; j<pRight->num; ++j) {
                    pRight->bData[j] = pRight->bData[j+1];
                }
                if (!pRight->isLeaf) {
                    pChildNode->pChild[pChildNode->num] = pRight->pChild[0]; //pRight�ڵ��к��ʵ���Ůָ����ֲ��pChildNode��
                    for (j=0; j<=pRight->num; ++j) {
                        pRight->pChild[j] = pRight->pChild[j+1];
                    }
                }
            }
            //�����ֵܽڵ㶼ֻ����CHILD_MIN-1���ڵ�
            else if (pLeft) { //�����ֵܺϲ�
                mergeChild(pNode, i-1);
                pChildNode = pLeft;
            }
            else if (pRight) { //�����ֵܺϲ�
                mergeChild(pNode, i);
            }
        }
        recursive_remove(pChildNode, data);
    }
}

template <typename T>
void BTree<T>::splitChild(BNode<T> *pParent, int nChildIndex, BNode<T> *pChild) {
    //��pChild���ѳ�pLeftNode��pChild�����ڵ�
    BNode<T> *pRightNode = new BNode<T>(); //���Ѻ���ҽڵ�
    pRightNode->isLeaf = pChild->isLeaf;
    pRightNode->num = DATA_MIN;
    int i;
    for (i=0; i<DATA_MIN; ++i) { //�����ؼ��ֵ�ֵ
        pRightNode->bData[i] = pChild->bData[i+CHILD_MIN];
    }
    if (!pChild->isLeaf) { //�������Ҷ�ӽڵ㣬�������ӽڵ�ָ��
        for (i=0; i<CHILD_MIN; ++i) {
            pRightNode->pChild[i] = pChild->pChild[i+CHILD_MIN];
        }
    }
    
    pChild->num = DATA_MIN; //�����������Ĺؼ��ָ���

    for (i=pParent->num; i>nChildIndex; --i) { //�����ڵ��е�nChildIndex������йؼ��ֵ�ֵ������ָ�������һλ
        pParent->pChild[i+1] = pParent->pChild[i];
        pParent->bData[i] = pParent->bData[i-1];
    }
    ++pParent->num; //���¸��ڵ�Ĺؼ��ָ���
    pParent->pChild[nChildIndex+1] = pRightNode; //�洢������ָ��
    pParent->bData[nChildIndex] = pChild->bData[DATA_MIN]; //�ѽڵ���м�ֵ�ᵽ���ڵ�
}

template <typename T>
void BTree<T>::mergeChild(BNode<T> *pParent, int index) {
    BNode<T> *pChild1 = pParent->pChild[index];
    BNode<T> *pChild2 = pParent->pChild[index+1];
    //��pChild2���ݺϲ���pChild1
    pChild1->num = DATA_MAX;
    pChild1->bData[DATA_MIN] = pParent->bData[index];//�����ڵ�index��ֵ����
    int i;
    for (i=0; i<DATA_MIN; ++i) {
        pChild1->bData[i+DATA_MIN+1] = pChild2->bData[i];
    }
    if (!pChild1->isLeaf) {
        for (i=0; i<CHILD_MIN; ++i) {
            pChild1->pChild[i+CHILD_MIN] = pChild2->pChild[i];
        }
    }

    //���ڵ�ɾ��index��key��index�����ǰ��һλ
    --pParent->num;
    for(i=index; i<pParent->num; ++i) {
        pParent->bData[i] = pParent->bData[i+1];
        pParent->pChild[i+1] = pParent->pChild[i+2];
    }
    deleteNode(pChild2);  //ɾ��pChild2
}

template <typename T>
void BTree<T>::deleteNode(BNode<T> *&pNode) {
    if (pNode!=NULL) {
        delete pNode;
        pNode = NULL;
    }
}

template <typename T>
void BTree<T>::displayInConcavo(BNode<T> *pNode, int count) {
    if (pNode!=NULL) {
        int i, j;
        for (i=0; i<pNode->num; ++i) {
            if (!pNode->isLeaf) {
                displayInConcavo(pNode->pChild[i], count-13);
            }
            for (j=count; j>=0; --j) {
                cout<<"-";
            }
            cout<<pNode->bData[i]<<endl;
        }
        if (!pNode->isLeaf) {
            displayInConcavo(pNode->pChild[i], count-13);
        }
    }
}

template <typename T>
void BTree<T>::recursive_clear(BNode<T> *pNode) {
    if (pNode!=NULL) {
        if (!pNode->isLeaf) {
            for(int i=0; i<=pNode->num; ++i)
                recursive_clear(pNode->pChild[i]);
        }
        deleteNode(pNode);
    }
}

template <typename T>
T BTree<T>::getPredecessor(BNode<T> *pNode) {
    while (!pNode->isLeaf) {
        pNode = pNode->pChild[pNode->num];
    }
    return pNode->bData[pNode->num-1];
}

template <typename T>
T BTree<T>::getSuccessor(BNode<T> *pNode) {
    while (!pNode->isLeaf) {
        pNode = pNode->pChild[0];
    }
    return pNode->bData[0];
}

#endif // BTREE_H
