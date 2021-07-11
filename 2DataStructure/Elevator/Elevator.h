#ifndef ELEVATOR_H
#define ELEVATOR_H

#include"PList.h"
#include"Passenger.h"

enum state {
	Opening,
	Opened,
	Closing,
	Closed,
	Waiting,
	Up,
	Down,
	In,
	Out,
	Accelerate,
	Decelerate
};

const int test = 40; // ����������ϵ��ݵĳ˿�
const int open = 20; // ����
const int close = 20; // ����
const int in = 25; // ��
const int out = 25; // ��
const int accelerate = 15; // ����
const int up = 51; // ����һ��
const int updecelerate = 14; // ��������
const int down = 61; // ����һ��
const int downdecelerate = 23; // �½�����
const int wait = 300; // ��ֹʱ��

class Elevator {
private:
	state stateNow; // ���ݵ�ǰ״̬
	int floor; // ���ݵ�ǰ���ڲ�
	PList *pList; // �ȴ�����
	int inElevator[10]; // ������
	int all;
	int dir; // �ж����µ����
	int holdtime;
	int record;
	int near;
	int downTime;
	int upTime;

public:
	Elevator();
	~Elevator() {delete pList;}

	state getNowState()const {return stateNow;}
	void setNowState(state t) {stateNow = t;}
	int getFloor()const {return floor;}
	void setfloor(int floor1) {floor = floor1;}
	int getAll()const {return all;}
	void setAll(int num) {all += num;} // numΪ�ⲿ�ϵ��ݵ�����
	int getDir()const {return dir;}
	void setDir(int num) {dir = num;}

	void addPassenger(const Passenger &x);// ��ӳ˿�
	void judgeGiveUp(int &time); // �ж��Ƿ����˷��������ں����ʼ
	bool noPassenger(int &time); // �ж��Ƿ��г˿�����

	void judgeDirction(int &time); // �жϵ������߷���
	void moveDirction(const int floor1, int &time); // �����ı���ݵ�״̬

	bool judgeOpen(int &time); // �ж��Ƿ���
	void OPEN(int &time); // �����Ŵ�

	void judgeClose(int &time); // 40tʱ�����ж��Ƿ����
	void CLOSE(int &time); // ����

	bool judgeOut(int &time); // �жϳ˿ͳ�ȥ
	void OUT(int &time); // �˿ͳ�ȥ

	bool judgeIn(int &time); // �жϳ˿ͽ���
	void IN(int &time); // �˿ͽ���

	void moveUp(int &time); // �����ƶ�
	void moveDown(int &time); // �����ƶ�
};

Elevator::Elevator() {
	stateNow = Waiting;
	floor = 1;
	pList = new PList();
	for (int i=0; i<10; i++)inElevator[i] = 0;
	all = 0;
	dir = -1;
	holdtime = 0;
	record = 0;
	near = 0;
	downTime = 0;
	upTime = 0;
}

void Elevator::addPassenger(const Passenger &x) {
	pList->append(x);
	cout << " ��" << x.getID() << "���˿ͽ���ȴ����� ";
}

void Elevator::judgeGiveUp(int &time) {
	//һ����ϵͳ�����жϸ�ʱ���Ƿ����˷���
	//waittimeΪ���ڵ�ʱ�䣬���ںͳ˿͵ȴ���ʱ��+wait�������жϳ˿��Ƿ����
	Node * ptemp = pList->getHead()->next;
	while (ptemp != NULL) {
		if ((ptemp->data.getWhenWait() + ptemp->data.getWaitTime()) <= time) {
			cout << "��" << ptemp->data.getID() << "���˿��ѷ����ȴ�  ";
			int delid = ptemp->data.getID();
			ptemp = ptemp->next;
			pList->remove(delid);
		}
		else ptemp = ptemp->next;
	}
	noPassenger(time);
}

bool Elevator::noPassenger(int &time) {
	// �����жϵ����Ƿ���ճ˿͵�����
	if (getNowState() == Waiting) {
		if (holdtime == wait && floor != 1) {
			//����ȹ���300t���Ҳ���1¥�Ļ�����ʼ����
			setNowState(Down);
			setDir(0);
			holdtime = 0;
			moveDown(time);
			return true;
		} else if (holdtime == wait && floor == 1) {
			//������ݱ�����һ¥����Ҫ���в���
			cout << "���ݿ������ˣ����ڵȴ�";
			holdtime = 0;
			return true;
		} else if (all == 0 && pList->empty() == true) {
			cout << "���ݿ������ˣ����ڵȴ�";
			holdtime++;
			return true;
		} else {
			judgeDirction(time);
			return false;
		}
	} else {
		judgeDirction(time);
		return false;
	}
}

void Elevator::judgeDirction(int &time) {
	// ʹ�øú��������жϵ��ݵ�����
	near = floor; // ��ʼ��near��ֵ��Ϊ��ֹ�������������������ʱ���ɿ���ʹ��MoveDirction����
	int upoutfar = 0, downoutfar = 10; // ����2����¼���³�ȥ��Զ����ı���
	int upinfar = 0, downinfar = 10; // ����2����¼���½�����Զ����ı���
	if (stateNow == Closed) {
		if (getAll() == 0 && pList->empty() == true) {
			setNowState(Waiting);
			return;
		}
		if (floor == 1) {
			setNowState(Up); setDir(1);
		}
		if (floor == 9) {
			setNowState(Down); setDir(0);
		}
		if (getAll() != 0) {//��������������
			//��ʱ��Ҫ���ֵ��ݵ����з��򣬷��������������
			bool key = false;
			for (int i=floor; i<10; i++) {
				if (inElevator[i] != 0) {
					near = i;
					upoutfar = i;
					setNowState(Up);
					setDir(1);
					key = true;
					break;
				}
			}
			if (key == false) {
				for (int i=1; i<floor; i++) {
					if (inElevator[i] != 0) {
						near = i;
						downoutfar = i;
						setNowState(Down);
						setDir(0);
						break;
					}
				}
			}
		}
		if (pList->empty() == false) {//������ȴ����˲�Ϊ��
			Node * ptemp = pList->getHead()->next;
			while (ptemp != NULL) {
				if (getDir() == 1) {//ֻ�����г˿�
					if (ptemp->data.getNowFloor() > floor) {//�˿�����¥���ڵ���¥���ϣ��������п��ܵ���ǰ������
						//��ʼ�����������еĳ˿ͣ����ҽ����ж��Ƿ���Ҫ���е�
						if (ptemp->data.getGoFloor() > ptemp->data.getNowFloor()) {
							//������������У��������ڵ������з����¥�ϣ���Ҫǰ������
							if (ptemp->data.getGoFloor() > upoutfar)upoutfar = ptemp->data.getGoFloor();
						} else {
							if (ptemp->data.getNowFloor() > upoutfar)upoutfar = ptemp->data.getNowFloor();
						}
					}
					if (upinfar == 0 && upoutfar == 0) { setNowState(Down); setDir(0); }
					if (upinfar <= upoutfar)near = upoutfar;
					else near = upinfar;
				} else if (getDir() == 0) {//ֻ�����г˿�
					if (ptemp->data.getNowFloor() < floor) {//�˿�����¥���ڵ���¥���£��������п��ܵ���ǰ������
						//��ʼ�����������еĳ˿ͣ����ҽ����ж��Ƿ���Ҫ���е�
						if (ptemp->data.getGoFloor() < ptemp->data.getNowFloor()) {
							//������������У��������ڵ������з����¥�£���Ҫǰ������
							if (ptemp->data.getGoFloor() < downoutfar)downoutfar = ptemp->data.getGoFloor();
						}
						if (ptemp->data.getGoFloor() > ptemp->data.getNowFloor()) {
							if (ptemp->data.getNowFloor() < downoutfar)downoutfar = ptemp->data.getNowFloor();
						}
					}
					if (downinfar == 10 && downoutfar == 10) { setNowState(Up); setDir(1); }
					if (downinfar <= downoutfar)near = downinfar;
					else near = downoutfar;
				}
				ptemp = ptemp->next;
			}
		}

	}
	if (stateNow == Waiting) {
		Node * ptemp = pList->getHead()->next;
		int time_now = 0;
		while (ptemp != NULL) {
			int Time_now = ptemp->data.getWhenWait();//���ڼ�¼���Ȱ�����
			time_now = Time_now;
			if (ptemp->data.getWhenWait() < time_now){//��ѡ�����Ȱ������ˣ�Ȼ����иı���ݵķ���
				time_now = ptemp->data.getWhenWait();
			}
			ptemp = ptemp->next;
		}
		ptemp = pList->getHead()->next;
		while (ptemp != NULL) {
			int up(floor), down(floor);
			if (ptemp->data.getWhenWait() == time_now) {
				int x = ptemp->data.getGoFloor() - ptemp->data.getNowFloor();
				//��ʱ�����4�����������ֻ����2���ǵ������У�2���ǵ�������
				if ((x > 0 && (ptemp->data.getNowFloor() > floor)) || (x<0 && (ptemp->data.getNowFloor()>floor))) {
					setNowState(Up);
					setDir(1);
					upinfar = ptemp->data.getNowFloor();
					if (up < upinfar) {
						up = upinfar;
					}
				} else if ((x > 0 && (ptemp->data.getNowFloor() < floor)) || (x < 0 && (ptemp->data.getNowFloor() < floor))) {
					setNowState(Down);
					setDir(0);
					downinfar = ptemp->data.getNowFloor();
					if (down > downinfar) {
						down = downinfar;
					}
				}
				if (down != floor&&up != floor) {//������ͬʱ��������ʱ���������ϵ�ԭ��
					setNowState(Up); near = upinfar; setDir(1);
				} else if (up != floor) {//ֻ�����е�����
					setNowState(Up); near = upinfar; setDir(1);
				} else if (down != floor) {//ֻ�����е�����
					setNowState(Down); near = downinfar; setDir(0);
				}
				if (floor == 1) { setNowState(Up); setDir(1); }
			}
			ptemp = ptemp->next;
		}
		if (near == floor)  OPEN(time);
	}
	if (stateNow == Up) {
		if (getAll() != 0) {//����������
			for (int i = 1; i < 10; i++) {
				if (inElevator[i] != 0) {
					if (i >= near) {
						upinfar = i;
					}
				}
			}
		}
		if (pList->empty() == false) {
			Node * ptemp = pList->getHead()->next;
			while (ptemp != NULL) {
				if (ptemp->data.getNowFloor() >= near) {
					if (ptemp->data.getGoFloor() >= upoutfar) {
						upoutfar = ptemp->data.getGoFloor();
					}
					if (ptemp->data.getNowFloor() >= upoutfar) {
						upoutfar = ptemp->data.getNowFloor();
					}
				}
				ptemp = ptemp->next;
			}
		}
		if (upinfar >= upoutfar) near = upinfar;
		else near = upoutfar;
	}
	if (stateNow == Down) {
		//downinfar = 10, downoutfar = 10;
		if (getAll() != 0) {//����������
			for (int i = 1; i < 10; i++) {
				if (inElevator[i] != 0) {
					if (i <= near) {
						downinfar = i;
						break;
					}
				}
			}
		}
		if (pList->empty() == false) {
			Node * ptemp = pList->getHead()->next;
			while (ptemp != NULL) {
				if (ptemp->data.getNowFloor() <= near) {
					if (ptemp->data.getNowFloor() <= downoutfar) {
						downoutfar = ptemp->data.getNowFloor();
					}
					if (ptemp->data.getGoFloor() <= downoutfar) {
						downoutfar = ptemp->data.getGoFloor();
					}
				}
				ptemp = ptemp->next;
			}
		}
		if (getAll() == 0 && pList->empty() == true)near = 1;
		else if (downinfar >= downoutfar)near = downoutfar;
		else near = downinfar;
	}
	moveDirction(near, time);
}

void Elevator::moveDirction(const int near, int &time) {
	//nearΪ�˿͵�������Զ��¥��
	if (near < floor) {
		setNowState(Down);
		setDir(0);
		moveDown(time);
		return;
	}
	if (near > floor) {
		setNowState(Up);
		setDir(1);
		moveUp(time);
		return;
	}
	if (getNowState() == Opening) {
		OPEN(time);
		return;
	}
	if (getNowState() == In) {
		IN(time);
		judgeClose(time);
		return;
	}
	if (getNowState() == Out) {
		OUT(time);
		judgeClose(time);
		return;
	}
	if (getNowState() == Opened) {
		judgeClose(time);
		if (judgeOut(time))OUT(time);
		if (judgeIn(time))IN(time);
		return;
	}
	if (getNowState() == Closing) {
		CLOSE(time);
		return;
	}
	if (near == floor&&pList->empty() == true && getAll() == 0) {
		setNowState(Waiting);
		noPassenger(time);
		return;
	}
	if (near == floor) {
		setNowState(Opening);
		OPEN(time);
		return;
	}
}

bool Elevator::judgeOpen(int &time) {//�жϴ�¥���Ƿ�������Ҫ����
	if (judgeIn(time) || judgeOut(time)) {
		OPEN(time);
		return true;
	}
	else return false;
}

void Elevator::OPEN(int &time) {
	if (getNowState() != Opening) {
		setNowState(Opening);
		record = 0;
		return;
	}
	if (record < open) {
		record++;
		cout << "���ݿ�����";
		return;
	} else {//������ɺ�
		record = 0;
		cout << "�������";
		setNowState(Opened);
		if (judgeOut(time))OUT(time);
		if (judgeIn(time))IN(time);
		judgeClose(time);
	}
}

void Elevator::judgeClose(int &time) {
	if (getNowState() == Opened){
		if (record < test) {
			record++;
			cout << "���ڹ��ż��";
			return;
		} else {
			cout << "���ż�����";
			if (getNowState() == Opened) {
				record = 0;
				CLOSE(time);
				return;
			} else {//���ƿ���ɾ��    
				record = 0;
				return;
			}
		}
	}
	else return;
}

void Elevator::CLOSE(int &time) {
	if (record < close) {
		record++;
		setNowState(Closing);
		cout << "�������ڹ�����";
	} else {
		record = 0;
		cout << "�����Ѿ�����";
		setNowState(Closed);
		if (near == floor) {//�����Ѿ������������¥�㣬���ܻ����4�����
			if (pList->empty() == false || getAll() != 0) {//�ȴ��������˻������Ҳ����
				Node * ptemp = pList->getHead()->next; int OutPeople = 0;
				while (ptemp != NULL) {
					if (ptemp->data.getNowFloor() == floor)OutPeople += 1;
					if (getAll() != 0 && OutPeople != 0) {//���������ˣ���������       �ж�ȥ�ķ���
						if (getDir() == 1 && (ptemp->data.getGoFloor() > floor)) {//�������У��˿����У�����
							setNowState(Opening);
						} else if (getDir() == 0 && (ptemp->data.getGoFloor() < floor)) {//�������У��˿����У�����
							setNowState(Opening);
						}
					}
					if (getAll() == 0 && OutPeople != 0) {//����û�ˣ���������
						if (getDir() == 1) {//��������
							if (ptemp->data.getGoFloor() > floor)
								setNowState(Opening);
							else if (ptemp->data.getGoFloor() < floor) {
								setDir(0); setNowState(Opening);
							}
						}
						if (getDir() == 0) {//��������
							if (ptemp->data.getGoFloor() < floor)
								setNowState(Opening);
							else if (ptemp->data.getGoFloor() > floor) {
								setDir(1); setNowState(Opening);
							}
						}
					}
					if (getAll() != 0 && OutPeople == 0) {
						//���������ˣ�����û�ˣ���ʱӦ�÷��Ƿ�����ͳ˿����л������У����ȱ�������õ��˿�Ҫȥ����
						for (int i = 1; i < 10; i++) {
							if (inElevator[i] != 0) {
								if (i < floor) { setNowState(Down); setDir(0); }
								if (i > floor) { setNowState(Up); setDir(1); }
							}
						}
					}
					ptemp = ptemp->next;
				}
			} else if (pList->empty() == true && getAll() == 0){//�ȴ�����û�ˣ�����Ҳû��
				setNowState(Waiting); setDir(-1);
			}
		} else if (near != floor) {
			if (getDir() == 1) {
				setDir(1); setNowState(Up);
			}
			if (getDir() == 0) {
				setDir(0); setNowState(Down);
			}
		}
		noPassenger(time);
	}
}

bool Elevator::judgeOut(int &time) {
	if (getAll() != 0) {
		int j = floor;
		if (inElevator[j] != 0)return true;
	}
	return false;
}

void Elevator::OUT(int &time) {
	if (record < out) {
		if (getNowState() == Opened) {
			record++;
			cout << "�˿������µ���";
			if (inElevator[floor] != 0) {
				cout << "�ڸò�һ����ȥ" << inElevator[floor] << "����";
				setAll(-inElevator[floor]);
				inElevator[floor] = 0;
			}
			setNowState(Out);
			return;
		}
		if (getNowState() == Out) {
			record++;
			cout << "�˿������µ���";
			return;
		}
	} else {
		cout << "��������Ҫ�µĳ˿Ͷ�����ȥ";
		record = 0;
		setNowState(Opened);
	}
}

bool Elevator::judgeIn(int &time) {//�������δ�����򷵻�true�����Լ�������
	//Ŀǰ��Ҫ���ƣ���Ϊ���Ȱ���ɾ����������飬������Ҫ�����и��ж�
	if (getAll() != 13) {
		if (!pList->empty()) {//��Ϊ����ִ��if���
			Node * ptemp = pList->getHead()->next; int upnum1 = 0, downnum1 = 0;
			while (ptemp != NULL) {
				if (ptemp->data.getNowFloor() == floor) {
					if ((ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) && (getDir() > 0)) {
						//�˿��������ߵ�
						return true;
					}
					if ((ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) && (getDir() == 0)) {
						//�˿�����
						return true;
					}
					int floor1 = near;
					for (int i=floor1+1; i<10; i++) { // ����BUG
						if (inElevator[i] != 0) {
							near = i;
						}
					}
					if (near == ptemp->data.getNowFloor()) {
						//�ﵽ���������¥�㣬���������ݷ���ͬ���򲻸ı䷽�򣬲����������
						//����������ͬ����ı䷽���������������У�����������ͬ�����
						if (getDir() == 1) {
							if (ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) {
								setDir(1); upnum1++;
							}
							if (ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) {
								setDir(0); downnum1++;
							}
							if (upnum1 != 0 && downnum1 != 0)setDir(1);
						} else if (getDir() == 0) {
							if (ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) {
								setDir(1); upnum1++;
							}
							if (ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) {
								setDir(0);  downnum1++;
							}
							if (upnum1 != 0 && downnum1 != 0)setDir(0);
						}
						return true;
					}
				}
				// if (ptemp->data.getNowFloor() > floor) {
				// 	setNowState(Up);
				// 	setDir(1);
				// }
				ptemp = ptemp->next;
			}
		}
	}
	return false;
}

void Elevator::IN(int &time) {
	if (getAll() < 13) {
		if (record < in) {
			if (getNowState() == Opened) {
				record++;
				Node * ptemp = pList->getHead()->next;
				while (ptemp != NULL) {
					if (ptemp->data.getNowFloor() == floor){//�����˵��ڵ���¥�㣬����ܽ����ж�
						if ((ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) && (getDir() > 0)) {
							//�˿��������ߵ�
							cout << "��" << ptemp->data.getID() << "���˿����ڽ������";
							inElevator[ptemp->data.getGoFloor()] += 1;
							setAll(1);
							pList->remove(ptemp->data.getID());
							setNowState(In);
							return;
						}
						if ((ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) && (getDir() == 0)) {
							//�˿�����
							cout << "��" << ptemp->data.getID() << "���˿����ڽ������";
							inElevator[ptemp->data.getGoFloor()] += 1;
							setAll(1);
							pList->remove(ptemp->data.getID());
							setNowState(In);
							return;
						}
					}
					ptemp = ptemp->next;
				}
			}
			if (getNowState() == In) {
				record++;
				cout << "�˿����ڽ������";
				return;
			}
		} else {
			cout << "�˿��Ѿ��������";
			record = 0;
			setNowState(Opened);
		}
	} else {
		cout << "�����������Ѿ��ﵽ���ֵ";
		setNowState(Closing);
	}
}

void Elevator::moveUp(int &time) {
	if (record < accelerate) {
		record++;
		cout << "�������ڼ�����¥";
		return;
	}
	if (record < up+accelerate) {
		record++;
		cout << "��������������¥";
		return;
	} else {
		floor++;
		record = 0;
		if (judgeOpen(time) == false) {
			record = accelerate+1;
			moveUp(time);
		}
		else {
			cout << "��������������¥" << endl;
			while (upTime <= updecelerate) {
				cout << time+1 << "tʱ��  ";
				cout << "������" << getFloor()-1 << "��  ";
				if (upTime == updecelerate) cout << "�����ѵ���"; 
				else cout << "�������ڼ�����¥" << endl;
				upTime++;
				time++;
			}
			upTime = 0;
			setNowState(Opening);
		}
	}

}

void Elevator::moveDown(int &time) {
	if (record < accelerate) {
		record++;
		cout << "�������ڼ�����¥";
		return;
	}
	if (record < down+accelerate) {
		record++;
		cout << "��������������¥";
		return;
	} else {
		floor--;
		record = 0;
		if (judgeOpen(time) == false) {
			record = accelerate+1;
			moveDown(time);
		}
		else {
			cout << "��������������¥" << endl;
			while (downTime <= downdecelerate) {
				cout << time+1 << "tʱ��  ";
				cout << "������" << getFloor()+1 << "��  ";
				if (downTime == downdecelerate) cout << "�����ѵ���"; 
				else cout << "�������ڼ�����¥" << endl;
				downTime++;
				time++;
			}
			downTime = 0;
			setNowState(Opening);
		}
	}
}

#endif // ELEVATOR_H