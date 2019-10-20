#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<queue>
#include<vector>
using namespace std;
#define MAX		9
#define N		7

int n = N, k;//������  ����
int dis[MAX];//����
int s[MAX];//ǰ���ڵ�
int t[MAX][MAX];//����ͼ
int temp[N][N] = {
	{ 0, 2, 8, 5, 0, 0, 0 },
	{ 0, 0, 3, 0, 3, 0, 0 },
	{ 0, 0, 0, 0, 0, 4, 0 },
	{ 0, 0, 0, 0, 0, 6, 9 },
	{ 0, 0, 0, 0, 0, 5, 7 },
	{ 0, 0, 0, 0, 0, 0, 2 },
	{ 0, 0, 0, 0, 0, 0, 0 }

};
struct Node {
	int length;
	int i;
	friend bool operator < (Node a, Node b) {
		return a.length > b.length;
	}
};

void shortesetpaths(int v) {
	priority_queue<Node>H;
	Node E;
	E.i = v;
	E.length = 0;
	dis[v] = 0;
	while (1) {
		int j;
		for (j = 0; j < n; j++) {
			if (t[E.i][j] != 0) {
				if (E.length + t[E.i][j] < dis[j]) {
					dis[j] = E.length + t[E.i][j];
					s[j] = E.i;
					if (j != n - 1) {
						Node X;
						X.i = j;
						X.length = dis[j];
						H.push(X);
					}
				}
			}
		}
		if (H.empty())
			break;
		E = H.top();
		H.pop();
	}
}


void show() {
	int j = 0, showNode[MAX];

	cout << "��ԭ�㵽�յ����̾���Ϊ:" << dis[n - 1] << endl;//��̵������һ��������
	cout << "���·��Ϊ: " << n - 1;
	showNode[j] = s[n - 1];
	cout << "<--" << setw(2) << showNode[j];
	while (showNode[j] != 0) {
		j++;
		showNode[j] = s[showNode[j - 1]];
		cout << " <--" << setw(2) << showNode[j];
	}
	cout << endl;
}
void main() {
	//����������д��
	for (int i = 0; i < n; i++) {
		dis[i] = 999;   //�Ѿ��븳���ֵ
		s[i] = -1;	//��ǰû��ǰ�����
		for (int j = 0; j < n; j++)
			if (temp[i][j] > 0)
				t[i][j] = temp[i][j];	//���ڱ߾ͽ��С���ֵ
	}
	shortesetpaths(0);//�ѵ�һ���������֧�޽������·����
	show();//��ʾ���Ľ��
	return;
}