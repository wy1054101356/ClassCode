#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<iomanip>
using namespace std;

#define MAX 20		//������
#define N	5		//������
#define M	3		//��ɫ����

int temp[N][N] =	//��������
{
	{ 0,1,1,0,1 },
{ 1,0,1,0,1 },
{ 1,1,0,1,0 },
{ 0,0,1,0,1 },
{ 1,1,0,1,0 }
};


class MGraph
{
public:
	MGraph(int v, int s);
	void mColoring(int k, int m);
	void mColoring(int m);
	void NextValue(int k, int m);
	bool ok(int k);
	int getColorCount() { return ColorCount; }

private:
	int a[MAX][MAX];
	int n, e;//nΪ������ eΪ����
	int ColorCount;		//��ⷽ����
	int x[MAX];			//��ɫ

};

bool MGraph::ok(int k)
{
	for (int i = 0; i < k; i++)
	{
		if (a[k][i] && x[k] == x[k])//���Ѿ���ɫ�� ��֮�����Ķ������ͬɫ���
			return false;
	}
	return true;
}


MGraph::MGraph(int v, int s)
{
	n = v;
	e = s/2;
	cout << n << " " << e << endl;
	ColorCount = 0;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++)
			a[i][j] = temp[i-1][j-1];//����������д��
	}
}

void MGraph::NextValue(int k, int m)
{
	int jx;
	do {
		x[k] = (x[k] + 1) % (m + 1);   //������һ����ɫ

		if (x[k] == 0)
			return;   //�Ѿ�����������ɫ��û�п�����ɫ
		for (int j = 0; j < k; j++)	//��(i, j)��ͼ�ıߣ������ڽ��k��j��ɫ��ͬ
			if (a[k][j] == x[j] && x[k] == x[j]){	//������ͻ��ѡ��һ����ɫ
				jx = j;
				break;
			}

		if (jx == k)
			return;	  //�ɹ�ѡ��һ����ɫ����
	} while (1); //ѭ��������ɫ

}



void MGraph::mColoring(int k, int m)
{
	do {
		NextValue(k, m);	//Ϊx[k]������ɫ

		if (x[k] == 0)
			break;

		if (k == n - 1){         //�õ�ͼG��һ��m-��ɫ����
			for (int i = 0; i < n; i++)
				cout << x[i] << ' ';
			cout << endl;
			ColorCount++;
		}

		else mColoring(k + 1, m);  //�Ѿ���ǰk������������ɫ������������(������ɫ)
	} while (1);

}

void MGraph::mColoring(int m)
{

	mColoring(1, m);
}

void main()
{
	int s = 0;
	cout << "��ǰ��ͼ���ڽӾ���Ϊ:" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++){
			cout << setw(4) << temp[i][j];//temp������0�ŵ�Ԫ
			if (temp[i][j] > 0)
				s++;
		}
		cout << endl;
	}

	MGraph mGraph(N, s);

	cout << "��ɫ���п��ܵĽ�" << endl;
	mGraph.mColoring(M);//�ӵ�һ���� һ��N(5)���� m����ɫ �ڽ�ͼc ����Ⱦɫ���� 
	cout << "��ɫ���ܽ������Ϊ:" << mGraph.getColorCount() << endl;//���ز���ʾ�ܿ��з�������
	system("pause");
	return;
}