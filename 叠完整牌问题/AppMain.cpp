/*
#include<iostream>
#include<iomanip>
#include<conio.h>
#include<vector>
using namespace std;

vector<int> pokers;							//���ﳢ��ʹ������

void showPokers()							//��ʾ�˿���ÿ�����
{
	cout << "====================================" << endl;
	cout << "����:";
	for (int i = 0; i < pokers.size(); i++)
		cout << setw(3) << i + 1;
	cout << endl;

	cout << "����:";
	for (int i = 0; i < pokers.size(); i++)
		cout << setw(3) << pokers[i];
	cout << endl;
	cout << "====================================" << endl;
	return;
}

void main() 
{
	int total;								//�˿���������
	int temp;								//�˿���ÿ������
	int pokersAverage;						//����ƽ����
	int times;								//��������

	do {
		total = 0;							//��ʼ��������Դ
		pokers.clear();

		cout << "������ÿ���˿����������Իس�������" << endl;
		while(1){
			cin >> temp;
			pokers.push_back(temp);			//������д�뵱ǰ���������
			total += temp;					//����
			if (getchar() == '\n')			//�����س�����ѭ��
				break;
		}
		if (total % pokers.size() != 0)		//�ж�һ��
			cout << "�����˿�����������!" << endl;
	} while (total % pokers.size() != 0);
	
	showPokers();							//��ʾһ������

	pokersAverage = total / pokers.size();	//����ƽ����
	times = 0;								//��������
	for (int i = 0; i < pokers.size(); i++) {

		//�����Ҫ�ƶ�
		if (pokers[i] != pokersAverage) {
			//�����ǰ����ƽ��
			if (pokers[i] > pokersAverage) {
				pokers[i + 1] += pokers[i] - pokersAverage;//�ƶ��˿���
				cout << "��" << times + 1 << "��:�� " << i + 1 << " ������ " << i + 2 << " ��"
					<< "�ƶ��� " << pokers[i] - pokersAverage << " ����" << endl;//��ʾ����
				pokers[i] = pokersAverage;
			}
			else {
				pokers[i + 1] -= pokersAverage - pokers[i];	//�ƶ��˿���
				cout << "��" << times + 1 << "��:�� " << i + 2 << " ������ " << i + 1 << " ��"
					 << "�ƶ��� " << pokersAverage - pokers[i] << " ����" << endl;//��ʾ����
				pokers[i] = pokersAverage;//�ı��˿�������
			}
			times++;		//��������
			showPokers();	//��������
		}
	}
	cout << "�����ƶ�����:" << times << endl;
	return;
}
*/