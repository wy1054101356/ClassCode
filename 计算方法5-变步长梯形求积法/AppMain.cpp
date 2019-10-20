#include<iostream>
#include<math.h>
#include<fstream>
#include<iomanip>
#include<Windows.h>
using namespace std;
#define MAX 20		//����������
#define eps 0.00005	//�ض����
#define A	0	//��������
#define B	1	//��������

float f(float x) {
	return (1 / (1 + x * x));//���ֺ���	
}
float computeT(float a, float b){
	float h, T = 0;
	h = (b - a) / 2;
	T = h * (f(a) + 2 * T + f(b)) / 2;
	return T;
}
void main(){
	float a, b, T1, T2, S, x, h;
	int i = 1;//��¼����
	a = A; b = B;//�Ѻ긳������������
	char strFileName[100] = "data.csv";//�ļ��� д��Excel���
	ofstream dataFileOut;		//����д���ļ�����	
	dataFileOut.open(strFileName);	//�Զ������ļ�
	cout << "���� 1 / ( 1 + x * x )���������0 �� 1 " << endl;
	dataFileOut << "���� 1 / ( 1 + x * x )���������0 �� 1 \n";
	dataFileOut << "����," << "Tn\n";//д���ļ�
	h = b - a;
	T1 = computeT(a, b);
	while (1) {
		S = 0;
		x = a + h / 2;
		do {
			S += f(x);
			x += h;
		} while (x<b);
		T2 = (T1 + h * S) / 2;
		dataFileOut << i << "," << T2 << "\n";
		cout << "��" << setw(2) << i << "�� Tn = " << setw(8) << T2 << endl;//��ʾÿһ�νض�����
		i++;
		if (fabs(T2 - T1) >= eps){//����ض������������Ҫ��
			T1 = T2;
			h /= 2;
			continue;
		}
		else
			break;
	}
	cout << endl << "�����: " << T2 << endl;
	dataFileOut << "�����:," << T2;
	dataFileOut.close();//�ر��ļ�
	ShellExecute(NULL, TEXT("open"), strFileName, NULL, NULL, SW_NORMAL);//��Excel�ļ�
	return;
}