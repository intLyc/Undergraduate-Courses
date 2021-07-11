/**
 * ������Ϣ����ϵͳ
 * ʵ���ˣ�
 * - ���ļ�������Ϣ������ÿһ��ѡ��Ὣ�ļ��е�����д���ڴ棬���������ģ��֮����д���ļ�
 * - ��һ�����ܣ�¼�������¼
 * - �ڶ������ܣ����Ҳ�ɾ����¼
 * - ���������ܣ������¼
 * - ���ĸ����ܣ�������Ϣ��¼
 * - ��������ܣ�����������������������ʾ
 * ʱ�䣺2018/6/28
 */

#include<stdio.h>
#include<string.h>

#define N 50     //����ṹ�������ĳ���
#define IS_EXIST 23333     //�����ýṹ����ڵı�־

//������Ϣ�ṹ��
typedef struct SongInfo
{
    char name[20];     //������
    char author[20];   //����
    char singer[20];   //�ݳ���
    char pub_date[6];  //��������(yyyymm)

    int _exist;     //�������ɸѡ�������ֵ����IS_EXIST,֤���ýṹ�����
}SI;

//////////������������//////////

//���ļ������ļ��е����ݶ�ȡ���ṹ��������
int readfile(SI *slist)
{
    int i = 0;
    FILE* rfile = fopen("song.txt","r");     //���ļ�����ʽΪֻ�����ļ���Ϊ"song.txt"
    if(!rfile)    //�ж��Ƿ�����ļ�
    {
        printf("open file error\n");
        return -1;
    }
    while(!feof(rfile))     //���ļ��ж�ȡ��Ϣ
    {
        fscanf(rfile,"%s%s%s%s",
            &slist[i].name,&slist[i].author,
            &slist[i].singer,&slist[i].pub_date);
        slist[i]._exist = IS_EXIST;
        i++;
    }
    if (fclose(rfile) != 0)     //�ж��Ƿ�ر����ļ�
    {
        printf("close file error\n");
        return -1;
    }
    return 0;
}

//����ṹ�������е����ݵ��ļ�
int writefile(SI *slist)
{
    int i;
    FILE* wfile = fopen("song.txt","w");     //���ļ�����ʽΪֻд������ʽд��
    if(!wfile)     //�ж��Ƿ�����ļ�
    {
        printf("open file error\n");
        return -1;
    }
    for(i=0;i<N;i++)     //����ʽд���ļ�
    {
        if(slist[i]._exist == IS_EXIST)
        {
            fprintf(wfile,"\n%s %s %s %s",
            slist[i].name,slist[i].author,
            slist[i].singer,slist[i].pub_date);
        }
    }
    if (fclose(wfile) != 0)     //�ж��Ƿ�ر����ļ�
    {
        printf("close file error\n");
        return -1;
    }
}

//��ӡ�����ṹ�����������
void print_data(SI si)
{
    printf("��������%10s ���ߣ�%10s �ݳ��ߣ�%10s �������£�%6s\n",
                si.name,si.author,
                si.singer,si.pub_date);
}

//////////�����˵�������//////////

//1.¼��
void add_record()
{
    int i;
    int button_2 = 0;     //ѡ�ť���ڶ��㣩
    SI si[N];     //������ʱ�����ļ������ݵĽṹ������
    readfile(si);   //��ȡ�ļ�

    for (i = 0; i < N; i++)
    {
        if(si[i]._exist != IS_EXIST)     //ɸѡ��¼�����ݵĽṹ��
        {
            printf("��ֱ���������������ߡ��ݳ��ߡ���������\n");
            scanf("%s%s%s%s",
                &si[i].name,&si[i].author,
                &si[i].singer,&si[i].pub_date);
            si[i]._exist = IS_EXIST;
            printf("1.����¼�� 0.���ؽ��棺");
            scanf("%d",&button_2);
            if(button_2 != 1)break;     //����"1"֮�����¼��
        }
    }

    writefile(si);    //д���ļ�
}

//2.ɾ��
void delete_record()
{
    int i;
    char temp_name[20];     //��ʱ�ַ����������������
    SI si[N];     //������ʱ�����ļ������ݵĽṹ������
    readfile(si);    //��ȡ�ļ�

    printf("������Ҫɾ���ĸ��������֣�");
    scanf("%s",&temp_name);
    for (i = 0; i < N; i++)
    {
        if(si[i]._exist != IS_EXIST)     //��ѭ����δ¼�����ݵĽṹ��֮������ѭ��
        {
            printf("δ�ҵ������¼��\n");
            system("pause");
            break;
        }
        else if(!strcmp(si[i].name,temp_name))     //�Ƚ�������ַ����������е���Ϣ�Ƿ����
        {
            int button_2 = 0;     //ѡ�ť���ڶ��㣩

            print_data(si[i]);

            printf("1.ȷ��ɾ�� 0.ȡ����");     //�ҵ����������ļ�¼��ȷ���Ƿ�ɾ��
            scanf("%d",&button_2);
            if(button_2 != 1)break;
            else si[i]._exist = 0;
        }
    }

    writefile(si);    //д���ļ�
}

//3.���
void scan_record()
{
    int i;
    SI si[N];     //������ʱ�����ļ������ݵĽṹ������
    readfile(si);    //��ȡ�ļ�

    printf("��ѯ���Ľ��Ϊ:\n");
    for(i = 0; i<N; i++)     //��ӡ�����з������������ļ�¼
    {
        if(si[i]._exist == IS_EXIST)     //ɸѡ����¼�����ݵļ�¼
        {
            print_data(si[i]);
        }
    }
    system("pause");     //��ͣ

    writefile(si);     //д���ļ�
}

//4.��ѯ
void search_record()
{
    int i;
    char data[20];     //������ʱ������������ݵ��ַ���
    SI si[N];     //������ʱ�����ļ������ݵĽṹ������
    readfile(si);     //��ȡ�ļ�

    printf("����������������߻��ݳ�����������Ϣ��");
    scanf("%s",&data);
    printf("���ҵĽ��Ϊ:\n");
    for(i = 0; i<N; i++)     //�����з��������ļ�¼��ӡ����
    {
        if(si[i]._exist == IS_EXIST)     //ɸѡ����¼�����ݵļ�¼
            if(!strcmp(data,si[i].name) || 
                !strcmp(data,si[i].author) ||
                !strcmp(data,si[i].singer))
            {
                print_data(si[i]);
            }
    }
    system("pause");     //��ͣ

    writefile(si);     //д���ļ�
}

//5.������ʾ
void sort_record()
{
    int i,j;
    int x=0;     //����һ����ʱ���α�����������¼�����ݵļ�¼������
    SI si[N];     //������ʱ�����ļ������ݵĽṹ������
    SI temp_si;     //������ʱ�ṹ����Ϊ�����ṹ���������������ڽṹ���ý��
    readfile(si);    //��ȡ�ļ�

    printf("�����Ľ��Ϊ:\n");
    for(i = 0; i<N; i++)    //�������¼�����ݵļ�¼������
    {
        if(si[i]._exist == IS_EXIST)x += 1;
    }
    for(i = 0; i<x-1; i++)     //ð������
    {
        for(j = 0; j<x-i-1; j++)
        {
            if(strcmp(si[j].author,si[j+1].author)>0)     //���ռ�¼�����߽�����������
            {
                temp_si = si[j];
                si[j] = si[j+1];
                si[j+1] = temp_si;
            }
        }
    }
    for(i = 0; i<N; i++)     //��ӡ�����������м�¼
    {
        if(si[i]._exist == IS_EXIST)print_data(si[i]);
    }
    system("pause");     //��ͣ

    writefile(si);     //д���ļ�
}

//////////�����к����������߼������//////////

//���к���
void Run()
{
    while(1)     //����ѭ����ÿ������һ��ģ��ͷ��ز˵�
    {
        int button_1 = 0;     //ѡ�ť����һ�㣩

        //�˵�
        printf("---���ܲ˵�---\n");
        printf("1.¼�������Ϣ\n");
        printf("2.ɾ��������Ϣ\n");
        printf("3.���������Ϣ\n");
        printf("4.��ѯ������Ϣ\n");
        printf("5.������ʾ��Ϣ\n");
        printf("0.�˳�����ϵͳ\n");
        printf("-------------\n");
        printf("��ѡ��");

        scanf("%d",&button_1);     //����ѡ�ť����һ�㣩
        if(button_1 == 0)break;     //Ϊ"0"ʱ�Ƴ�
        else{
            switch(button_1){                    //switch
                case 1:add_record();break;       //����"1"����¼��ģ��
                case 2:delete_record();break;    //����"2"����ɾ��ģ��
                case 3:scan_record();break;      //����"3"�������ģ��
                case 4:search_record();break;    //����"4"�������ģ��
                case 5:sort_record();break;      //����"5"��������ģ��
                default:                         //����������½���˵�
                    printf("������0-5֮������֣�\n");
                    system("pause");
                    break;
            }
        }
    }
}

//////////����������//////////

int main()
{
    Run();     //����
    return 0;
}