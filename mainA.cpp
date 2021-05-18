#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;
void cr(string str);
void de(string str);
void req(string str);
void to(int i);
void init();

class PCB {
public:
	string id;
	int priority;
	int R1 = 0;
	int R2 = 0;
	int R3 = 0;
	int R4 = 0;
	int needR1 = 0;
	int needR2 = 0;
	int needR3 = 0;
	int needR4 = 0;
};
class resourceTable {
public:
	int R1 = 1;
	int R2 = 2;
	int R3 = 3;
	int R4 = 4;
};

static string running;
static vector<PCB> pb;//���ȼ�Ϊ0����
static vector<PCB> pb1;//���ȼ�Ϊ1����
static vector<PCB> pb2;//���ȼ�Ϊ2����
static resourceTable rs;//��Դ��
static vector<PCB> stopPb;//��������

int main() {
	string str;
	string res="init";
	init();
	while (true) {
			//�ж�shell����
			cout << res<<endl;
			getline(cin,str);
			if (str.substr(0, 2) == "cr") {
				cr(str);
				to(0);
			}
			if (str.substr(0, 2) == "to") {
				to(1);
			}
			if (str.substr(0, 3) == "req") {
				req(str);
				to(0);
			}
			if (str.substr(0, 2) == "de") {
				de(str);
				to(0);
			}
			res += " ";
			res += running;
	}
}
//to����ÿ��ִ��ʱ�ж��Ƿ��и����ȼ����̣�����У��л���to����Ϊ1ʱ����ʾ������һ��ʱ��Ƭ
void to(int i) {
	if (!pb2.empty()) {
		running = pb2[0].id;
	}
	else if (!pb1.empty()) {
		running = pb1[0].id;
	}
	else {
		running = pb[0].id;
	}
	if (i == 1) {
		if (!pb2.empty()) {
				PCB tempPCB = pb2[0];
				vector<PCB>::iterator k = pb2.begin();
				pb2.erase(k);
				pb2.push_back(tempPCB);
				running = pb2[0].id;
				return;
			}
			if (!pb1.empty()) {
				PCB tempPCB = pb1[0];
				vector<PCB>::iterator k = pb1.begin();
				pb1.erase(k);
				pb1.push_back(tempPCB);
				running = pb1[0].id;
				return;
			}
			if (!pb.empty()) {
				PCB tempPCB = pb[0];
				vector<PCB>::iterator k = pb.begin();
				pb.erase(k);
				pb.push_back(tempPCB);
				running = pb[0].id;
				return;
			}
	}
}
//��������
void cr(string str) {
	cout << "ִ��cr" << endl;
	string processName = str.substr(3, 1);
	cout << "Process name is " << processName<<endl;
	string priority = str.substr(5, 1);
	cout << "priority is " << priority << endl;
	PCB newPCB;
	newPCB.id = processName;
	newPCB.priority = atoi(priority.c_str());
	if (newPCB.priority == 1) {
		pb1.push_back(newPCB);
	}
	if (newPCB.priority == 0) {
		pb.push_back(newPCB);
	}
	if (newPCB.priority == 2) {
		pb2.push_back(newPCB);
	}
}
//������Դ�����жϣ�������㣬������������stopPb
void req(string str) {
	cout << "ִ��req" << endl;
	string resource = str.substr(4, 2);
	cout << "resource is " << resource<<endl;
	string resourceNum = str.substr(7, 1);
	int num = atoi(resourceNum.c_str());
	cout << "resource number is " << num<<endl;
	int flag = 0;
	if (resource == "R1") {
		if (rs.R1 - num >= 0) {
			cout << "R1����ɹ�" << endl;
			rs.R1 -= num;
			flag = 1;
		}
		else {
			cout << "R1����" << endl;
			flag = 2;
		}
	}
	if (resource == "R2") {
		if (rs.R2 - num >= 0) {
			cout << "R2����ɹ�" << endl;
			rs.R2 -= num;
			flag = 3;
		}
		else {
			cout << "R2����" << endl;
			flag = 4;
		}
	}
	if (resource == "R3") {
		if (rs.R3 - num >= 0) {
			cout << "R3����ɹ�" << endl;
			rs.R3 -= num;
			flag = 5;
		}
		else {
			cout << "R3����" << endl;
			flag = 6;
		}
	}
	if (resource == "R4") {
		if (rs.R4 - num >= 0) {
			cout << "R4����ɹ�" << endl;
			rs.R4 -= num;
			flag = 7;
		}
		else {
			cout << "R4����" << endl;
			flag = 8;
		}
	}
		for (int i = 0; i < pb.size(); ++i) {
			if (pb[i].id == running) {
				switch (flag)
				{
				case 1:
					pb[i].R1 += num;
					break;
				case 2:
				{pb[i].needR1 += num;
				PCB temp = pb[i];
				stopPb.push_back(temp);
				pb.erase(pb.begin() + i);
				break; }
				case 3:
					pb[i].R2 += num;
					break;
				case 4:
				{pb[i].needR2 += num;
				PCB temp = pb[i];
				stopPb.push_back(temp);
				pb.erase(pb.begin() + i);
				break; }
				case 5:
					pb[i].R3 += num;
					break;
				case 6:
				{pb[i].needR3 += num;
				PCB temp = pb[i];
				stopPb.push_back(temp);
				pb.erase(pb.begin() + i);
				break; }
				case 7:
					pb[i].R4 += num;
					break;
				case 8:
				{pb[i].needR4 += num;
				PCB temp = pb[i];
				stopPb.push_back(temp);
				pb.erase(pb.begin() + i);
				break; }
				}
			}
		}
		for (int i = 0; i < pb1.size(); ++i) {
			if (pb1[i].id == running) {
				switch (flag)
				{
				case 1:
					pb1[i].R1 += num;
					break;
				case 2:
				{pb1[i].needR1 += num;
				PCB temp = pb1[i];
				stopPb.push_back(temp);
				pb1.erase(pb1.begin() + i);
				break; }
				case 3:
					pb1[i].R2 += num;
					break;
				case 4:
				{pb1[i].needR2 += num;
				PCB temp = pb1[i];
				stopPb.push_back(temp);
				pb1.erase(pb1.begin() + i);
				break; }
				case 5:
					pb1[i].R3 += num;
					break;
				case 6:
				{pb1[i].needR3 += num;
				PCB temp = pb1[i];
				stopPb.push_back(temp);
				pb1.erase(pb1.begin() + i);
				break; }
				case 7:
					pb1[i].R4 += num;
					break;
				case 8:
				{pb1[i].needR4 += num;
				PCB temp = pb1[i];
				stopPb.push_back(temp);
				pb1.erase(pb1.begin() + i);
				break; }
				}
			}
		}
		for (int i = 0; i < pb2.size(); ++i) {
			if (pb2[i].id == running) {
				switch (flag)
				{
				case 1:
					pb2[i].R1 += num;
					break;
				case 2:
				{pb2[i].needR1 += num;
				PCB temp = pb2[i];
				stopPb.push_back(temp);
				pb2.erase(pb2.begin() + i);
				break; }
				case 3:
					pb2[i].R2 += num;
					break;
				case 4:
				{pb2[i].needR2 += num;
				PCB temp = pb2[i];
				stopPb.push_back(temp);
				pb2.erase(pb2.begin() + i);
				break; }
				case 5:
					pb2[i].R3 += num;
					break;
				case 6:
				{pb2[i].needR3 += num;
				PCB temp = pb2[i];
				stopPb.push_back(temp);
				pb2.erase(pb2.begin() + i);
				break; }
				case 7:
					pb2[i].R4 += num;
					break;
				case 8:
				{pb2[i].needR4 += num;
				PCB temp = pb2[i];
				stopPb.push_back(temp);
				pb2.erase(pb2.begin() + i);
				break; }
				}
			}
		}
}
//ɾ����������Դ�������Դ���պ���������������ĳһ����Ҫ��������뵽�������
void de(string str) {
	cout << "ִ��de" << endl;
	string deName = str.substr(3, 1);
	for (int i = 0; i < pb.size(); ++i) {
		if (pb[i].id == deName) {
			rs.R1 += pb[i].R1;
			rs.R2 += pb[i].R2;
			rs.R3 += pb[i].R3;
			rs.R4 += pb[i].R4;
			pb.erase(pb.begin() + i);
		}
	}
	for (int i = 0; i < pb1.size(); ++i) {
		if (pb1[i].id == deName) {
			rs.R1 += pb1[i].R1;
			rs.R2 += pb1[i].R2;
			rs.R3 += pb1[i].R3;
			rs.R4 += pb1[i].R4;
			pb1.erase(pb1.begin() + i);
		}
	}
	for (int i = 0; i < pb2.size(); ++i) {
		if (pb2[i].id == deName) {
			rs.R1 += pb2[i].R1;
			rs.R2 += pb2[i].R2;
			rs.R3 += pb2[i].R3;
			rs.R4 += pb2[i].R4;
			pb2.erase(pb2.begin() + i);
		}
	}
	for (int i = 0; i < stopPb.size(); ++i) {
		if (stopPb[i].id == deName) {
			rs.R1 += stopPb[i].R1;
			rs.R2 += stopPb[i].R2;
			rs.R3 += stopPb[i].R3;
			rs.R4 += stopPb[i].R4;
			stopPb.erase(stopPb.begin() + i);
		}
	}
	for (int i = 0; i < stopPb.size(); ++i) {
		if (stopPb[i].needR1 <= rs.R1 && stopPb[i].needR2 <= rs.R2 && stopPb[i].needR3 <= rs.R3 && stopPb[i].needR4 <= rs.R4) {
			PCB temp;
			stopPb[i].R1 += stopPb[i].needR1;
			stopPb[i].needR1 = 0;
			stopPb[i].R2 += stopPb[i].needR2;
			stopPb[i].needR2 = 0;
			stopPb[i].R3 += stopPb[i].needR3;
			stopPb[i].needR3 = 0;
			stopPb[i].R4 += stopPb[i].needR4;
			stopPb[i].needR4 = 0;
			temp = stopPb[i];
			if (stopPb[i].priority==0)
			{
				pb.push_back(temp);
			}
			if (stopPb[i].priority == 1)
			{
				pb1.push_back(temp);
			}
			if (stopPb[i].priority == 2)
			{
				pb2.push_back(temp);
			}
			stopPb.erase(stopPb.begin() + i);
		}
	}
}
//��ʼ������
void init() {
	PCB newPCB;
	newPCB.priority = 0;
	newPCB.id = "init";
	pb.push_back(newPCB);
	running = "init";
}
