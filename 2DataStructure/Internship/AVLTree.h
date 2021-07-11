#include <iostream>
#include "stack.h"

using namespace std;

template <typename T>
struct AVLNode {
    int bf;
    T data;
    AVLNode<T> *left, *right;
    AVLNode(): left(NULL), right(NULL), bf(0) {}
    AVLNode(T x, AVLNode<T> *l=NULL, AVLNode<T> *r=NULL)
        :data(x), left(l), right(r), bf(0) {}
};

template <typename T>
class AVLTree {
public:
    AVLTree(): root(NULL) {}
    ~AVLTree() {destory(root);}
    void Init(); // ��ʼ����
    bool Search(const T x) {return Search(x, root)? true: false;} // ����
    bool Insert(T el) {return Insert(root, el);} // ����
    bool Remove(T x) {return Remove(root, x);}  //ɾ��
    void Print() {Print(root);}  // ���

protected:
    AVLNode<T> *root;
    void destory(AVLNode<T> *&ptr);
    AVLNode<T> *Search(T x, AVLNode<T> *&ptr);
    bool Insert(AVLNode<T> *&ptr, T el);
    bool Remove(AVLNode<T> *&ptr, T x);
    void Print(AVLNode<T> *ptr);
    void RotateL(AVLNode<T> *&ptr);
    void RotateR(AVLNode<T> *&ptr);
    void RotateLR(AVLNode<T> *&ptr);
    void RotateRL(AVLNode<T> *&ptr);
    int getLevel(AVLNode<T> *current);
    AVLNode<T> *Parent(AVLNode<T> *ptr, AVLNode<T> *current);
};

template <typename T>
void AVLTree<T>::Init() {
    destory(root); root = NULL;
    T item; T ref;
    cout << "Your ref(To end input): ";
    cin >> ref;
    cout << "Input data(End with ref): ";
    cin >> item;
    while(item != ref) {
        Insert(item);
        cout << "Input data(End with ref): ";
        cin >> item;
    }
};

template <typename T>
void AVLTree<T>::destory(AVLNode<T> *&ptr) {
    if (ptr) {
        destory(ptr->left);
        destory(ptr->right);
        delete ptr;
    }
};

template <typename T>
AVLNode<T> *AVLTree<T>::Search(T x, AVLNode<T> *&ptr) {
    if (!ptr) return NULL;
    else if (x < ptr->data) return Search(x, ptr->left);
    else if (x > ptr->data) return Search(x, ptr->right);
    else return ptr;
};

template <typename T>
bool AVLTree<T>::Insert(AVLNode<T> *&ptr, T el) {
    AVLNode<T> *pr = NULL, *p = ptr, *q; int d;
    stack<AVLNode<T> *> st;
    while (p) {
        if (el == p->data) return false;
        pr = p; st.push(pr);
        if (el < p->data) p = p->left;
        else p = p->right;
    }
    p = new AVLNode<T>(el);
    if (!p) {cout << "no space!" << endl; exit(1);}
    if (!pr) {ptr = p; return true;}
    if (el < pr->data) pr->left = p;
    else pr->right = p;
    while (!st.empty()) {
        pr = st.top(); st.pop();
        if (p == pr->left) pr->bf--;
        else pr->bf++;
        if (pr->bf == 0) break;
        if (pr->bf == 1 || pr->bf == -1) p = pr;
        else {
            d = (pr->bf < 0)? -1: 1;
            if (p->bf == d) {
                if (d == -1) RotateR(pr);
                else RotateL(pr);
            } else {
                if (d == -1) RotateLR(pr);
                else RotateRL(pr);
            }
            break;
        }
    }
    if (st.empty()) ptr = pr;
    else {
        q = st.top();
        if (q->data > pr->data) q->left = pr;
        else q->right = pr;
    }
    return true;
};


// ����
// template <typename T>
// bool AVLTree<T>::Remove(AVLNode<T> *&ptr, T x) {
//     AVLNode<T> *pr = NULL, *p = ptr, *q, *ppr; int d, dd = 0;
//     stack<AVLNode<T> *> st;
//     while (p) {
//         if (x == p->data) break;
//         pr = p; st.push(pr);
//         if (x < p->data) p = p->left;
//         else p = p->right;
//     }
//     if (!p) return false;
//     if (p->left && p->right) {
//         pr = p; st.push(pr);
//         q = p->left;
//         while (q->right) {
//             pr = q; st.push(pr);
//             q = q->right;
//         }
//         p->data = q->data;
//         p = q;
//     }
//     if (p->left) q = p->left;
//     else q = p->right;
//     if (!pr) ptr = q;
//     else {
//         if (pr->left == p) pr->left = q;
//         else pr->right = q;
//         while (!st.empty()) {
//             pr = st.top(); st.pop();
//             if (!pr->left && !pr->right) {
//                 pr->bf = 0;
//                 continue;
//             }
//             if (pr->right == q) pr->bf--;
//             else pr->bf++;
//             if (!st.empty()) {
//                 ppr = st.top();
//                 dd = (ppr->left == pr)? -1: 1;
//             }
//             else dd = 0;
//             if (pr->bf == 1 || pr->bf == -1) break;
//             if (pr->bf != 0) {
//                 if (pr->bf < 0) {d = -1; q = pr->left;}
//                 else {d = 1; q = pr->right;}
//                 if (q->bf == 0) {
//                     if (d == -1) {
//                         RotateR(pr); 
//                         pr->bf = 1; pr->left->bf = -1;
//                     } else {
//                         RotateL(pr);
//                         pr->bf = -1; pr->right->bf = 1;
//                     }
//                     if (dd == -1) ppr->left = pr;
//                     else if (dd == 1) ppr->right = pr;
//                     break;
//                 }
//                 if (q->bf == d) {
//                     if (d == -1) RotateR(pr);
//                     else RotateL(pr);
//                 } else {
//                     if (d == -1) RotateLR(pr);
//                     else RotateRL(pr);
//                 }
//                 if (dd == -1) ppr->left = pr;
//                 else if (dd == 1) ppr->right = pr;
//             }
//             q = pr;
//         }
//         if (st.empty()) ptr = pr; 
//     }
//     delete p; return true;
// };

template<class T>
bool  AVLTree<T>::Remove(AVLNode<T>*&t, T val)
{
	if (t == nullptr) return false;

	AVLNode<T> *tmp = t;
	AVLNode<T> *pre_tmp = nullptr;
	AVLNode<T> *ppre_tmp = nullptr;
	AVLNode<T> *it_tmp = nullptr;
	stack<AVLNode<T>*> st;
	int sign, lable; // ���ű��
	int flag = 0; // ������ǣ����ľ������

	while (tmp != nullptr) {
		if (tmp->data == val) break; // �ҵ�����ѭ��

		pre_tmp = tmp;
		st.push(pre_tmp);

		if (tmp->data > val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	if (tmp == nullptr) return false; // δ�ҵ�������
	else if (tmp->left!= nullptr && tmp->right != nullptr) {
		pre_tmp = tmp; // �����������ӵĽڵ�ת��Ϊֻ��һ�����ӵĽڵ㣬������Ѱ�������������ֱ��ǰ������
		st.push(pre_tmp);

		it_tmp = tmp->left;
		while (it_tmp->right!= nullptr) {
			pre_tmp = it_tmp;
			st.push(pre_tmp);
			it_tmp = it_tmp->right;
		}
		tmp->data = it_tmp->data; // ����Ҫɾ���Ľڵ�
		tmp = it_tmp; // tmpָ��Ҫɾ���Ľڵ㣬��������ǰ��delete tmp
	}

	if (tmp->left!= nullptr) {  // �������жϷ�ʽ�ᵼ��ɾ��һ���ڵ�������û�к��ӽڵ�Ľڵ�ʱ���������Ӿ�Ϊ�գ�ֱ������else
		it_tmp = tmp->left;
	} else {
		it_tmp = tmp->right;
	}

	if (pre_tmp == nullptr)
		t = it_tmp;
	else {
		if (pre_tmp->left== tmp) { // ����ֱ������else���������ڴ˴�����flag������ʶ����������pre_tmp�����ӻ����Һ��ӡ�
			flag = 0;
			pre_tmp->left= it_tmp;
		} else {
			flag = 1;
			pre_tmp->right = it_tmp;
		}

		while (!st.empty()) {
			pre_tmp = st.top();
			st.pop();

			if (pre_tmp->left == it_tmp && flag == 0) // �˴�flag=0����ֹpre_tmp������Ϊ�գ��Һ���ͬ��Ϊ�գ�ֱ�ӽ���else
				pre_tmp->bf++;
			else
				pre_tmp->bf--;

			if (!st.empty())
			{
				ppre_tmp = st.top();
				if (ppre_tmp->left == pre_tmp)
				{
					sign = -1; // sign����ʶ�����游�ڵ�����ӻ����Һ��ӣ��������ӻ�����
					flag = 0;
				} else {
					sign = 1;
					flag = 1;
				}
			}
		    else sign = 0; // ջ�գ��������Ƚڵ㲻���ڣ�pre_tmp��Ϊ���ڵ㣬��������ҲҪд�ϣ�����sign��ֵ����������

			if (pre_tmp->bf == -1 || pre_tmp->bf == 1)
				break; // �Ѿ�ƽ�⣬ֱ������
			if (pre_tmp->bf != 0) { //m_bfΪ+2/-2
				if (pre_tmp->bf < 0) {
					lable = -1; // lable��ʾ���ڵ���ţ��������������ͬ�����
					it_tmp = pre_tmp->left;
				} else {
					lable = 1;
					it_tmp = pre_tmp->right;
				}

				if (it_tmp->bf == 0) { // pre_tmp�Ľϸ�������ͷ�ڵ�m_bfΪ0
					if (lable == -1) {
						RotateR(pre_tmp);
						pre_tmp->bf = 1;
						pre_tmp->right->bf = -1;
					} else {
						RotateL(pre_tmp);
						pre_tmp->bf = -1;
						pre_tmp->left->bf = 1;
					}
					break; // ֱ����������û�����ӣ���Ҫ����д������
				}

				if (it_tmp->bf == lable) { // ͬ�� 
					lable == 1 ? RotateL(pre_tmp) : RotateLR(pre_tmp);
				} else { // ���
					lable == -1 ? RotateLR(pre_tmp): RotateRL(pre_tmp);
				}
				if (sign == -1)
					ppre_tmp->left = pre_tmp;
				else if (sign == 1) // else if��ȷ��ʽ
					ppre_tmp->right = pre_tmp;
			}
			it_tmp = pre_tmp; // ����
		}
		if (st.empty()) // ջΪ�գ����ڵ�
			t = pre_tmp;
		else { // ��һ��else�ο�����û�У����Ǵ�ģ������д�˴���breakֱ������whileѭ�����ᵼ�����Ӳ��ϣ����ݶ�ʧ
			ppre_tmp = st.top();
			if (ppre_tmp->data > pre_tmp->data)
				ppre_tmp->left = pre_tmp;
			else
				ppre_tmp->right = pre_tmp;
		}
	}
	delete tmp;
	tmp = nullptr;
	return true;
}

template <typename T>
void AVLTree<T>::Print(AVLNode<T> *ptr) {
    if (!ptr) return;
    Print(ptr->right);
    int x = getLevel(ptr) - 1;
    while (x--) cout << '\t';
    cout << ptr->data << endl;
    Print(ptr->left);
};

template <typename T>
void AVLTree<T>::RotateL(AVLNode<T> *&ptr) {
    AVLNode<T> *subL = ptr;
    ptr = subL->right;
    subL->right = ptr->left;
    ptr->left = subL;
    ptr->bf = subL->bf = 0;
};

template <typename T>
void AVLTree<T>::RotateR(AVLNode<T> *&ptr) {
    AVLNode<T> *subR = ptr;
    ptr = subR->left;
    subR->left = ptr->right;
    ptr->right = subR;
    ptr->bf = subR->bf = 0;
};

template <typename T>
void AVLTree<T>::RotateLR(AVLNode<T> *&ptr) {
    AVLNode<T> *subR = ptr, *subL = subR->left;
    ptr = subL->right;
    subL->right = ptr->left;
    ptr->left = subL;
    if (ptr->bf <= 0) subL->bf = 0;
    else subL->bf = -1;
    subR->left = ptr->right;
    ptr->right = subR;
    if (ptr->bf == -1) subR->bf = 1;
    else subR->bf = 0;
    ptr->bf = 0;
};

template <typename T>
void AVLTree<T>::RotateRL(AVLNode<T> *&ptr) {
    AVLNode<T> *subL = ptr, *subR = subL->right;
    ptr = subR->left;
    subR->left = ptr->right;
    ptr->right = subR;
    if (ptr->bf >= 0) subR->bf = 0;
    else subR->bf = 1;
    subL->right = ptr->left;
    ptr->left = subL;
    if (ptr->bf == 1) subL->bf = -1;
    else subL->bf = 0;
    ptr->bf = 0;
};

template <typename T>
int AVLTree<T>::getLevel(AVLNode<T> *current) {
    if (root == current) return 1;
    else return 1 + getLevel(Parent(root, current));
};

template <typename T>
AVLNode<T> *AVLTree<T>::Parent(AVLNode<T> *ptr, AVLNode<T> *current) {
    if (!ptr) return NULL;
    if (ptr->left == current || ptr->right == current) return ptr;
    AVLNode<T> *p = Parent(ptr->left, current);
    if (p) return p;
    else return Parent(ptr->right, current);
};
