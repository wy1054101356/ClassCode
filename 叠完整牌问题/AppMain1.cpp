
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
	int max;								//����
	do {									//ѭ�������˿������ݣ�ֱ����ȷ����Ϊֹ
		total = 0;							//��ʼ��������Դ
		pokers.clear();

		cout << "������ÿ���˿����������Իس�������" << endl;
		while (1) {
			cin >> temp;
			pokers.push_back(temp);			//������д�뵱ǰ���������
			total += temp;					//�����ܺ�
			if (getchar() == '\n')			//�����س�����ѭ��
				break;
		}
		if (total % pokers.size() != 0)		//�ж�
			cout << "�����˿�����������!" << endl;
	} while (total % pokers.size() != 0);
	showPokers();							//��ʾ����

	pokersAverage = total / pokers.size();	//����ƽ����
	times = 0;		
	
	for (int j = 0; j < pokers.size(); j++){//�Ӵ�С����
		for (int i = 0; i < pokers.size() - 1 - j; i++){
			if (pokers[i] < pokers[i + 1]){
				max = pokers[i];
				pokers[i] = pokers[i + 1];
				pokers[i + 1] = max;
			}
		}
	}
	cout << "�������˿�������:" << endl;
	showPokers();		//��������

	for (int i = 0; i < pokers.size(); i++) {
		if (pokers[i] != pokersAverage) {
			if (pokers[i] > pokersAverage) {
				pokers[i + 1] += pokers[i] - pokersAverage;//�ƶ��˿���
				cout << "��" << times + 1 << "��:�� " << i + 1 << " ������ " << i + 2 << " ��"
					<< "�ƶ��� " << pokers[i] - pokersAverage << " ����" << endl;//��ʾ����
				pokers[i] = pokersAverage;
			}
			times++;		//��������
			showPokers();	//��������
		}
	}
	cout << "�����ƶ�����:" << times << endl;
	return;
}
