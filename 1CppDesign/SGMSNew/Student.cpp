#include <iostream>
#include <string>
#include <iomanip>
#include "Student.h"

Student::Student()
{
    number = "none";
    name = "none";
    math = 0;
    physics = 0;
    english = 0;
}

Student::Student(
    std::string number,
    std::string name,
    double math,
    double physics,
    double english)
{
    this->number = number;
    this->name = name;
    this->math = math;
    this->physics = physics;
    this->english = english;
}

void Student::print_data()
{
    std::cout <<
    "ѧ�ţ�" << std::setw(11) << number <<
    " ������" << std::setw(6) << name <<
    " ��ѧ��" << std::setprecision(3) << std::setw(3) << math <<
    " ����" << std::setprecision(3) << std::setw(3) << physics <<
    " Ӣ�" << std::setprecision(3) << std::setw(3) << english <<
    " ƽ����" << std::setprecision(3) << std::setw(3) << get_average() << std::endl;
}
