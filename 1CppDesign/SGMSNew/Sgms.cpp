#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <limits>
#include "Student.h"
#include "Sgms.h"

void Sgms::run()
{
    while(1)
    {
        std::cout
        << "---------------" << std::endl
        << "    ���ܲ˵�    " << std::endl
        << "---------------" << std::endl
        << "1. ¼��ѧ����¼" << std::endl
        << "2. ɾ��ѧ����¼" << std::endl
        << "3. �޸�ѧ����¼" << std::endl
        << "4. ����ѧ����¼" << std::endl
        << "5. �ɼ�ͳ�Ʒ���" << std::endl
        << "6. �ɼ��ߵ�����" << std::endl
        << "7. �ɼ��ļ�����" << std::endl
        << "0. �˳�����" << std::endl
        << "---------------" << std::endl
        << "��������Ҫʹ�õĹ��ܱ��: ";

        int button_1 = 0;
        std::cin >> button_1;
        if(button_1 == 0)break;
        else{
            switch (button_1) {
                case 1:add_record();break;
                case 2:delete_record();break;
                case 3:change_record();break;
                case 4:search_record();break;
                case 5:analyse_record();break;
                case 6:sort_record();break;
                case 7:file_record();break;
            }
        }
        std::cout << "���������ַ��Լ�����";
        std::string key;std::cin >> key;std::cout << std::endl;
    }
}


void Sgms::add_record()
{
    std::cout << "��ֱ����룺ѧ�š���������ѧ�ɼ�������ɼ���Ӣ��ɼ�" << std::endl;
    std::string number, name;double math,physics,english;

    int button_2 = 0;
    do{
        std::cin >> number >> name >> math >> physics >> english;
        Student temp_stu(number,name,math,physics,english);
        List.push_back(temp_stu);
        std::cout << "��¼��ɹ���" << std::endl
                << "1.����¼�� 0.���ؽ��棺";
        std::cin >> button_2;
    }while(button_2 == 1);
}

void Sgms::delete_record()
{
    std::cout << "������Ҫɾ���ļ�¼��ѧ�Ż�����:";
    std::string temp_data;
    std::cin >> temp_data;
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        if(temp_data == (*i).number || temp_data == (*i).name)
        {
            (*i).print_data();
            std::cout << "1.ȷ��ɾ�� 0.ȡ����";
            int button_2 = 0;
            std::cin >> button_2;
            switch (button_2) {
                case 1:{
                    List.erase(i);
                    std::cout << "��ɾ���ɹ���" << std::endl;
                    }break;
                case 0:break;
            }
            break;
        }
        if((i+1) == List.end())std::cout << "��δ�ҵ��˼�¼��" << std::endl;
    }
}

void Sgms::change_record()
{
    std::cout << "������Ҫ�޸ĵļ�¼��ѧ�Ż�����:";
    std::string temp_data;
    std::cin >> temp_data;
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        if(temp_data == (*i).number || temp_data == (*i).name)
        {
            int button_2 = 0;
            std::cout << "��ѡ��Ҫ�޸ĵ���Ŀ��"
                    << "1.��ѧ 2.���� 3.Ӣ�� 4.ѧ�� 5.���� 0.���أ�";
            std::cin >> button_2;
            switch (button_2) {
                case 1:change_data((*i),1);break;
                case 2:change_data((*i),2);break;
                case 3:change_data((*i),3);break;
                case 4:change_data((*i),4);break;
                case 5:change_data((*i),5);break;
                case 0:break;
            }
            break;
        }
        if((i+1) == List.end())std::cout << "��δ�ҵ��˼�¼��" << std::endl;
    }
}

void Sgms::search_record()
{
    std::cout << "1.���˳ɼ� 2.�ֶ����� 0.���أ�";
    int button_2 = 0;
    std::cin >> button_2;
    switch(button_2){
        case 1:{
            std::cout << "������Ҫ���ҵļ�¼��ѧ�Ż�����(��ģ������):";
            std::string temp_data;
            std::cin >> temp_data;
            std::cout << "���ҵĽ��Ϊ��" << std::endl;
            for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
            {
                if((*i).number.find(temp_data) != std::string::npos || (*i).name.find(temp_data) != std::string::npos)
                {
                    (*i).print_data();
                }
            }
        }break;
        case 2:{
            std::cout << "1.��ѧ 2.���� 3.Ӣ�� 4.ƽ���֣�";
            int button_3 = 0;
            std::cin >> button_3;
            print_section(button_3);
        }break;
        case 0:break;
    }
}

void Sgms::analyse_record()
{
    double math_average = 0,english_average = 0,physics_average = 0,average_average = 0;
    double math_dev = 0,english_dev = 0,physics_dev = 0,average_dev = 0;
    double math_qua = 0,english_qua = 0,physics_qua = 0,average_qua = 0;

    all_average(math_average,physics_average,english_average,average_average);
    standard_deviation(math_dev,physics_dev,english_dev,average_dev,
        math_average,physics_average,english_average,average_average);
    qualified_rate(math_qua,physics_qua,english_qua,average_qua);

    std::cout << "ƽ���ɼ���" << std::endl
            << "��ѧ��" << std::setprecision(4) << std::setw(4) << math_average
            << " ����" << std::setprecision(4) << std::setw(4) << physics_average
            << " Ӣ�" << std::setprecision(4) << std::setw(4) << english_average
            << " ���壺" << std::setprecision(4) << std::setw(4) << average_average <<std::endl
            << "��׼�" << std::endl
            << "��ѧ��" << std::setprecision(4) << std::setw(4) << math_dev
            << " ����" << std::setprecision(4) << std::setw(4) << physics_dev
            << " Ӣ�" << std::setprecision(4) << std::setw(4) << english_dev
            << " ���壺" << std::setprecision(4) << std::setw(4) << average_dev <<std::endl
            << "�ϸ��ʣ�" << std::endl
            << "��ѧ��" << std::setprecision(3) << std::setw(3) << math_qua << "%"
            << " ����" << std::setprecision(3) << std::setw(3) << physics_qua << "%"
            << " Ӣ�" << std::setprecision(3) << std::setw(3) << english_qua << "%"
            << " ���壺" << std::setprecision(3) << std::setw(3) << average_qua << "%" << std::endl;
}

void Sgms::sort_record()
{
    if(List.size() != 0){
        int i,j;Student T;
        for(i = 0;i < (int)List.size()-1;i++)
        {
            for(j = 0;j < (int)List.size()-1-i;j++)
            {
                if(List[j].get_average() < List[j+1].get_average()
                    && fabs(List[j].get_average()-List[j+1].get_average()) > 1E-6)
                {T = List[j];List[j] = List[j+1];List[j+1] = T;}
                if(fabs(List[j].get_average()-List[j+1].get_average()) <= 1E-6)
                {
                    if(List[j].math < List[j+1].math
                        && fabs(List[j].math-List[j+1].math) > 1E-6)
                    {T = List[j];List[j] = List[j+1];List[j+1] = T;}
                    if(fabs(List[j].math-List[j+1].math) <= 1E-6)
                    {
                        if(List[j].physics < List[j+1].physics
                            && fabs(List[j].physics-List[j+1].physics) > 1E-6)
                        {T = List[j];List[j] = List[j+1];List[j+1] = T;}
                        if(fabs(List[j].physics-List[j+1].physics) <= 1E-6)
                        {
                            if(List[j].english < List[j+1].english
                                && fabs(List[j].english-List[j+1].english) > 1E-6)
                            {T = List[j];List[j] = List[j+1];List[j+1] = T;}
                            if(fabs(List[j].english-List[j+1].english) <= 1E-6)
                            {
                                if(std::stoll(List[j].number) < std::stoll(List[j+1].number)
                                    && fabs(std::stoll(List[j].number)-std::stoll(List[j+1].number)) > 1E-6)
                                {T = List[j];List[j] = List[j+1];List[j+1] = T;}
                            }
                        }
                    }
                }
            }
        }
        std::cout << "������ɹ���" << std::endl
                << "1.�鿴 0.����:";
        int button_2 = 0;
        std::cin >> button_2;
        switch (button_2) {
            case 1:{
                for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
                {(*i).print_data();}
            }break;
            case 0:break;
        }
    }
}

void Sgms::file_record()
{
    std::cout << "1.��ȡ�ļ� 2.д���ļ� 0.���أ�";
    int button_2 = 0;
    std::cin >> button_2;
    switch (button_2) {
        case 1:{
            std::ifstream ifile("Grade.txt");
            std::string temp_number,temp_name;
            double temp_math,temp_physics,temp_english;
            while(1)
            {
                if(ifile.eof())break;
                ifile >> temp_number >> temp_name >> temp_math >> temp_physics >> temp_english;
                Student temp_stu(temp_number,temp_name,temp_math,temp_physics,temp_english);
                List.push_back(temp_stu);
            }
            std::cout << "����ȡ�ɹ���" << std::endl
                    << "1.�鿴 0.����:";
            int button_3 = 0;
            std::cin >> button_3;
            switch (button_3) {
                case 1:{
                    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
                    {(*i).print_data();}
                }break;
                case 0:break;
            }
        }break;
        case 2:{
            std::ofstream ofile("Grade.txt");
            if (ofile.is_open())
            {
                for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
                {
                    ofile << std::endl
                        << (*i).number << " "
                        << (*i).name << " "
                        << (*i).math << " "
                        << (*i).physics << " "
                        << (*i).english;
                }
                ofile.close();
                std::cout << "��д��ɹ���" << std::endl;
            }
            else std::cout << "���ļ��޷��򿪣�" << std::endl;
        }break;
        case 0:break;
    }
}


void Sgms::change_data(Student &temp_stu,int x)
{
    std::cout << "�������޸ĺ�����ݣ�";
    switch (x) {
        case 1:temp_stu.math = double_cin();break;
        case 2:temp_stu.physics = double_cin();break;
        case 3:temp_stu.english = double_cin();break;
        case 4:temp_stu.number = string_cin();break;
        case 5:temp_stu.name = string_cin();break;
    }
    std::cout << "���޸ĳɹ���" << std::endl;
}

void Sgms::print_section(int x)
{
    std::cout << "������ɼ��ֶε���ͷ�����߷֣�";
    double bottom = 0,top = 100;
    std::cin >> bottom >> top;
    std::cout << "���ҵĽ��Ϊ��" << std::endl;
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        switch (x) {
            case 1:if((*i).math >= bottom && (*i).math <= top)(*i).print_data();break;
            case 2:if((*i).physics >= bottom && (*i).physics <= top)(*i).print_data();break;
            case 3:if((*i).english >= bottom && (*i).english <= top)(*i).print_data();break;
            case 4:if((*i).get_average() >= bottom && (*i).get_average() <= top)(*i).print_data();break;
        }
    }
}

void Sgms::all_average(
    double &math_average,double &physics_average,double &english_average,double &average_average)
{
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        math_average += (*i).math;
        physics_average += (*i).physics;
        english_average += (*i).english;
        average_average += (*i).get_average();
    }
    math_average /= List.size();
    physics_average /= List.size();
    english_average /= List.size();
    average_average /= List.size();
}

void Sgms::standard_deviation(
    double &math_dev,double &physics_dev,double &english_dev,double &average_dev,
    double math_average,double physics_average,double english_average,double average_average)
{
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        math_dev += ((*i).math - math_average)*((*i).math - math_average);
        physics_dev += ((*i).physics - physics_average)*((*i).physics - physics_average);
        english_dev += ((*i).english - english_average)*((*i).english - english_average);
        average_dev += ((*i).get_average() - average_average)*((*i).get_average() - average_average);
    }
    math_dev = sqrt(math_dev/List.size());
    physics_dev = sqrt(physics_dev/List.size());
    english_dev = sqrt(english_dev/List.size());
    average_dev = sqrt(average_dev/List.size());
}

void Sgms::qualified_rate(
    double &math_qua,double &physics_qua,double &english_qua,double &average_qua)
{
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        if((*i).math >= 60)math_qua += 1;
        if((*i).physics >= 60)physics_qua += 1;
        if((*i).english >= 60)english_qua += 1;
        if((*i).get_average() >= 60)average_qua += 1;
    }
    math_qua = (math_qua/List.size())*100;
    physics_qua = (physics_qua/List.size())*100;
    english_qua = (english_qua/List.size())*100;
    average_qua = (average_qua/List.size())*100;
}
