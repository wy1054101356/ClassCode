#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<Windows.h>
using namespace std;
#define N 4								//����
#define MAX 100							//����������
#define EPS 0.0001						//���ȣ������ӡ��ʱ�򰴼�����ƣ�
#define strFileName "�����ļ�.csv"		//����ļ�

static double aa[N][N] ={
	{ 8, 7, 0, 0},
	{ 6, 12,5, 0},
	{ 0, 4, 9, 3},
	{ 0, 0, 1, 2}
};
static double bb[N] = { 0, -2, 8, 6 };

void main()
{
	int k = 0;
	double d, s, sum, norm;
	double a[N + 1][N + 1], b[N + 1], x[N + 1], y[N + 1];

	ofstream ServiceFileOut;			//����д���ļ�����	
	ServiceFileOut.open(strFileName);	//�Զ������ļ�

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			a[i][j] = aa[i - 1][j - 1];
		b[i] = bb[i - 1];
	}

	for (int i = 1; i <= N; i++)
		x[i] = 0;						//�����ֵ

	ServiceFileOut << "����,x1,x2,x3,x4\n ";//д��������Ϣ
	for (int i = 1; i <= N; i++)
		ServiceFileOut <<x[i]<< ",";

	ServiceFileOut<< "\n";
	do {								//��ʼ����
		k++;
		if (k > MAX) {
			printf("\n faild");
			break;
		}
		norm = 0;
		for (int i = 1; i <= N; i++) {
			sum = 0.0;
			for (int j = 1; j <= N; j++)
				if (j != i)
					sum += a[i][j] * x[j];
			y[i] = (b[i] - sum) / a[i][i];
			d = fabs(y[i] - x[i]);
			if (norm < d)
				norm = d;
		}

		ServiceFileOut <<k<<",";		//д��������Ϣ

		for (int i = 1; i <= N; i++)
			ServiceFileOut << y[i] << ",";
		ServiceFileOut << "\n";

		for (int i = 1; i <= N; i++)
			x[i] = y[i];
	} while (norm > EPS);				//�ھ��ȿ����ڼ���ѭ��

	if (norm < EPS) {
		ServiceFileOut << "���\n";
		ServiceFileOut << "��������,x1,x2,x3,x4\n";
		ServiceFileOut << k << ",";

		for (int i = 1; i <= N; i++)
			ServiceFileOut << x[i] << ",";
	}
	
	ServiceFileOut.close();				//�ر��ļ�д��
	ShellExecute(NULL, "open", strFileName, NULL, NULL, SW_NORMAL);//���ļ�
	return;
}