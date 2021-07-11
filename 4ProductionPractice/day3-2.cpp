#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

/* ���ܣ��ַ������ִ�����
 * ������char* �ַ���ָ��, char* ���ַ���ָ��
 * ����ֵ��int ����
 * ���ߣ����ӳ�20171002448
 */
int countSubStr(char *p, char *sub)
{
    char *q = p;
    int count = 0;
    while (*q != '\0')
    {
        q = strstr(q, sub);
        if (q != NULL)
        {
            count++;
            q += strlen(sub);
        }
        else
            break;
    }
    return count;
}

/* ���ܣ��ַ������Ӵ���������
 * ��������
 * ����ֵ��void
 * ���ߣ����ӳ�20171002448
 */
void test1()
{
    char p[] = "abcd1111222abcd333444abcd555666aa";
    char sub[] = "abcd";
    cout << "������" << countSubStr(p, sub) << endl;
}

/* ���ܣ��ַ����и���key��value
 * ������char* �ַ�������ָ��, int �ַ������鳤��, char* key�ַ���ָ��, char *value�ַ���ָ��
 * ����ֵ��bool �Ƿ��ҵ�
 * ���ߣ����ӳ�20171002448
 */
bool getValueStr(char arr[][20], int arr_len, char *key, char *value)
{
    // ȥ���ո�
    for(int num=0; num<arr_len; num++){
        int i=0;
        while(arr[num][i] != '\0') {
            if(arr[num][i] == ' ') {
                int j=i;
                while(arr[num][j] != '\0') {
                    arr[num][j] = arr[num][j+1];
                    j++;
                }
                continue;
            }
            i++;
        }
        //cout << arr[num] << endl;
    }
    
    // �ж�value�Ƿ����
    int num=0,i=0,j=0;
    bool flag = false;
    for(num=0; num<arr_len; num++){
        while(arr[num][i] != '=') {
            if(key[j] == arr[num][i]) {
                i++; j++;
            } else {
                i=0; j=0;
                break;
            }
        }
        if(j==strlen(key)) { //success
            flag = true;
            break;
        }
    }
    if(!flag) return false;

    // ����value
    j=0; i++;
    while(arr[num][i] != '\0') {
        value[j]=arr[num][i];
        i++; j++;
    }
    value[j] = '\0';
    return true;
}

/* ���ܣ��ַ����и���key��value����
 * ��������
 * ����ֵ��void
 * ���ߣ����ӳ�20171002448
 */
void test2()
{
    char arr[][20] = {
        "key1 = value1",
        "key2 =   value2",
        "  key3= value3",
        "key4    = value4"
    };
    int arr_len = sizeof(arr) / sizeof(arr[0]);
    char key[] = "key3";
    char value[10];
    getValueStr(arr, arr_len, key, value);
    cout << "key: " << key << endl;
    cout << "value: " << value << endl;
}

int main()
{
    test1();
    test2();
    return 0;
}
