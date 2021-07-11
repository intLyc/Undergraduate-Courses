/**
 * ��׺���ʽת��׺���ʽ
 */

#include <iostream>
#include <string>
#include "stack.h"
using namespace std;

bool isd(char ch) { //�ж��Ƿ�Ϊ������
    switch(ch) {
        case '+': return false;
        case '-': return false;
        case '*': return false;
        case '/': return false;
        case '(': return false;
        case ')': return false;
        case ';': return false;
    }
    return true;
}

int isp(char ch) { //ջ��Ԫ�ص�ֵ
    switch(ch) {
        case '+': return 3;
        case '-': return 3;
        case '*': return 5;
        case '/': return 5;
        case '(': return 1;
        case ')': return 6;
        case ';': return 0;
    }
}

int icp(char ch) { //ջ��Ԫ�ص�ֵ
    switch(ch) {
        case '+': return 2;
        case '-': return 2;
        case '*': return 4;
        case '/': return 4;
        case '(': return 6;
        case ')': return 1;
        case ';': return 0;
    }
}

string fun(const string &str) {
    stack<char> oper;
    string out;
    int k = 0;
    for (int i=0; str[i] != ';'; i++) {
        switch(str[i]) {
            case '+': {
                while(1) {
                    if (!oper.empty() && (oper.top()=='/' || oper.top()=='*' || oper.top()=='+' || oper.top()=='-')) {
                        out.append(1,oper.top());
                        oper.pop();
                    }
                    else {
                        oper.push(str[i]);
                        break;
                    }
                }
            } break;
            case '-': {
                while(1) {
                    if (!oper.empty() && (oper.top()=='/' || oper.top()=='*' || oper.top()=='+' || oper.top()=='-')) {
                        out.append(1,oper.top());
                        oper.pop();
                    }
                    else {
                        oper.push(str[i]);
                        break;
                    }
                }
            } break;
            case '*': {
                while(1) {
                    if (!oper.empty() && (oper.top() == '/' || oper.top() == '*')) {
                        out.append(1,oper.top());
                        oper.pop();
                    }
                    else {
                        oper.push(str[i]);
                        break;
                    }
                }
            } break;
            case '/': {
                while(1) {
                    if (!oper.empty() && (oper.top() == '/' || oper.top() == '*')) {
                        out.append(1,oper.top());
                        oper.pop();
                    }
                    else {
                        oper.push(str[i]);
                        break;
                    }
                }
            } break;
            case '(': {
                oper.push(str[i]);
            } break;
            case ')': {
                while(oper.top() != '(') {
                    out.append(1,oper.top());
                    oper.pop();
                }
                oper.pop();
            } break;
            default: {
                out.append(1,str[i]);
            }
        }
    }
    while (!oper.empty()) {
        out.append(1,oper.top());
        oper.pop();
    }
    return out;
}

string fun2(const string &str) {
    stack<char> st;
    string out;
    int k = 0;
    char ch = ';', ch1; // ch:���ʽ��һ��Ԫ��,ch1:ջ��Ԫ��
    st.push(ch);
    ch = str[k++];
    while(!st.empty()) {
        if(isd(ch)) {out.append(1,ch); ch = str[k++];}
        else {
            ch1 = st.top();

            // ������ʽ�Ƿ���ȷ
            if(ch1 == ')') return "���ʽ����ȱ��ǰ����";
            else if(ch1 == '(' && ch == ';') return "���ʽ����ȱ�ٺ�����";

            else if(isp(ch1) < icp(ch)) {
                st.push(ch); ch = str[k++];
            }
            else if(isp(ch1) > icp(ch)) {
                st.pop(); out.append(1,ch1);
            }
            else {
                st.pop();
                if(ch1 == '(') ch = str[k++];
            }
        }
    }
    return out;
}

// string fun3(stack<char> st, const string &str, int size, int k) {
//     ch = str[k];
//     if(!st.empty() && k==size-1) {

//     }
//         if(isd(ch)) {out.append(1,ch); ch = str[k++];}
//         else {
//             ch1 = st.top();

//             // ������ʽ�Ƿ���ȷ
//             if(ch1 == ')') return "���ʽ����ȱ��ǰ����";
//             else if(ch1 == '(' && ch == ';') return "���ʽ����ȱ�ٺ�����";

//             else if(isp(ch1) < icp(ch)) {
//                 st.push(ch); ch = str[k++];
//             }
//             else if(isp(ch1) > icp(ch)) {
//                 st.pop(); out.append(1,ch1);
//             }
//             else {
//                 st.pop();
//                 if(ch1 == '(') ch = str[k++];
//             }
//         }
//     }
// }

int main() {
    string str;
    while (cin >> str) {
        //cout << fun(str) << endl;
        cout << fun2(str) << endl;
        //cout << fun3(str) << endl;
    }
    return 0;
}