#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<iomanip>
using namespace std;

#define MAX 20		//最大矩阵
#define N	5		//顶点数
#define M	3		//着色个数

int temp[N][N] =	//内置数据
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
	int n, e;//n为顶点数 e为边数
	int ColorCount;		//求解方法数
	int x[MAX];			//颜色

};

bool MGraph::ok(int k)
{
	for (int i = 0; i < k; i++)
	{
		if (a[k][i] && x[k] == x[k])//看已经着色的 与之相连的顶点和他同色与否？
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
			a[i][j] = temp[i-1][j-1];//把内置数据写入
	}
}

void MGraph::NextValue(int k, int m)
{
	int jx;
	do {
		x[k] = (x[k] + 1) % (m + 1);   //尝试下一种颜色

		if (x[k] == 0)
			return;   //已经试完所有颜色，没有可用颜色
		for (int j = 0; j < k; j++)	//若(i, j)是图的边，且相邻结点k和j颜色相同
			if (a[k][j] == x[j] && x[k] == x[j]){	//发生冲突，选下一种颜色
				jx = j;
				break;
			}

		if (jx == k)
			return;	  //成功选择一种颜色返回
	} while (1); //循环尝试颜色

}



void MGraph::mColoring(int k, int m)
{
	do {
		NextValue(k, m);	//为x[k]分配颜色

		if (x[k] == 0)
			break;

		if (k == n - 1){         //得到图G的一种m-着色方案
			for (int i = 0; i < n; i++)
				cout << x[i] << ' ';
			cout << endl;
			ColorCount++;
		}

		else mColoring(k + 1, m);  //已经对前k个结点分配了颜色，尝试其余结点(部分着色)
	} while (1);

}

void MGraph::mColoring(int m)
{

	mColoring(1, m);
}

void main()
{
	int s = 0;
	cout << "当前的图的邻接矩阵为:" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++){
			cout << setw(4) << temp[i][j];//temp启用了0号单元
			if (temp[i][j] > 0)
				s++;
		}
		cout << endl;
	}

	MGraph mGraph(N, s);

	cout << "着色所有可能的解" << endl;
	mGraph.mColoring(M);//从第一个点 一共N(5)个点 m个颜色 邻接图c 传入染色函数 
	cout << "着色可能解的总数为:" << mGraph.getColorCount() << endl;//返回并显示总可行方案次数
	system("pause");
	return;
}