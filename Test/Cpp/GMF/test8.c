#include <stdio.h>

int main()
{
    char str[40], a;
    int i = 0, big = 0, small = 0, other = 0;
    scanf("%s", &str);
    a = str[0];
    while (a != '#')
    {
        //��дӢ����ĸ
        if ((int)a >= (int)'A' && (int)a <= (int)'Z')
        {
            big++;
        }
        //СдӢ����ĸ
        else if ((int)a >= (int)'a' && (int)a <= (int)'z')
        {
            small++;
        }
        //��������
        else
        {
            other++;
        }
        a = str[++i];
    }
    printf("��д��ĸ�ĸ�����%d\nСд��ĸ�ĸ�����%d\n������ĸ�ĸ�����%d\n", big, small, other);
    return 0;
}