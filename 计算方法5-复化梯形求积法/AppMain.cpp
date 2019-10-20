#include<iostream>
#include<math.h>
#include<iomanip>
#include<fstream>
#include<Windows.h>
using namespace std;
#define MAX 20 //���ȷ�������	3 5 7 
#define A	0	//��������
#define B	1	//��������
float f(float x) {
	return (1 / (1 + x * x));//���ֺ���	
}
float computeT(float a, float b, int n){
	float h, T = 0;
	h = (b - a) / n;
	for (int i = 1; i<n; i++)
		T += f(a + i * h);
	T = h * (f(a) + 2 * T + f(b)) / 2;
	return(T);
}
void main(){
	int n;//����
	float a1 = A, b1 = B;//ȷ������
	char strFileName[100] = "data.csv";	//�ļ���  д��Excel���
	ofstream dataFileOut;	//����д���ļ�����	
	dataFileOut.open(strFileName);	//�Զ������ļ�
	cout << "���� 1 / ( 1 + x * x )���������0 �� 1 " << endl;
	dataFileOut << "���� 1 / ( 1 + x * x )���������0 �� 1 \n";//���ĵ�д���ļ�
	dataFileOut << "������n," << "���T\n";
	for (int i = 1; i<MAX; i++) {
		n = i;//������i��ֵ�����������n
		cout << "�� n=" << setw(2) << i << "   T = " << setw(8) << computeT(a1, b1, n) << endl;
		dataFileOut << i << "," << computeT(a1, b1, n) << "\n";//������д���ļ�
	}
	dataFileOut.close();//�ر��ļ�
	ShellExecute(NULL, TEXT("open"), strFileName, NULL, NULL, SW_NORMAL);//��Excel�ļ�
	return;
}