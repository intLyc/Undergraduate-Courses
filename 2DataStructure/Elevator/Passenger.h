#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>

using namespace std;

class Passenger {
private:
	int id;
	int nowFloor;
	int goFloor;
	int whenWait;
	int waitTime;

public:
	Passenger() :id(0), nowFloor(0), goFloor(0), whenWait(0), waitTime(0) {}

	void setData(int id1);
	void setData(int id1, int nowFloor1, int goFloor1, int whenWait1, int waitTime1);

	void setID(int id1) {id = id1;}
	void setNowFloor(int nowFloor1) {nowFloor = nowFloor1;}
	void setGoFloor(int goFloor1) {goFloor = goFloor1;}
	void setWhenWait(int whenWait1) {whenWait = whenWait1;}
	void setWaitTime(int waitTime1) {waitTime = waitTime1;}

	int getID()const {return id;}
	int getNowFloor()const {return nowFloor;}
	int getGoFloor()const {return goFloor;}
	int getWhenWait()const {return whenWait;}
	int getWaitTime()const {return waitTime;}
};

void Passenger::setData(int id1) {
	id = id1; int i = 1;
	while (i) {
		cout << "�������" << id << "λ�˿͵���Ϣ" << endl;
		cout << "�ó˿�Ŀǰ����һ�㣺"; cin >> nowFloor;
		cout << "�ó˿�ȥ��һ�㣺"; cin >> goFloor;                                                                                                                          
		cout << "�ó˿ͺ�ʱ�ϵ��ݣ�"; cin >> whenWait;
		cout << "�ó˿����ȴ�ʱ�䣺"; cin >> waitTime;
		if (nowFloor > 9 || nowFloor < 0) {
			cout << "�˿�Ŀǰ��¥�������������룡" << endl;
		}
		if (goFloor > 9 || goFloor < 0) {
			cout << "�˿�Ҫȥ��¥�������������룡" << endl;
		}
		else i = 0;
	}
}

void Passenger::setData(int id1, int nowFloor1, int goFloor1, int whenWait1, int waitTime1) {
	id = id1;
	nowFloor = nowFloor1;
	goFloor = goFloor1;
	whenWait = whenWait1;
	waitTime = waitTime1;
}

#endif // PASSENGER_H