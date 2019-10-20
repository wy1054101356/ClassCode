#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<queue>
#include<vector>
using namespace std;
#define MAX		9
#define N		7

int n = N, k;//结点个数  边数
int dis[MAX];//距离
int s[MAX];//前驱节点
int t[MAX][MAX];//有向图
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

	cout << "从原点到终点的最短距离为:" << dis[n - 1] << endl;//最短的在最后一个数据中
	cout << "最短路径为: " << n - 1;
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
	//把内置数据写入
	for (int i = 0; i < n; i++) {
		dis[i] = 999;   //把距离赋最大值
		s[i] = -1;	//当前没有前驱结点
		for (int j = 0; j < n; j++)
			if (temp[i][j] > 0)
				t[i][j] = temp[i][j];	//存在边就进行、赋值
	}
	shortesetpaths(0);//把第一个点送入分支限界求最短路径中
	show();//显示最后的结果
	return;
}