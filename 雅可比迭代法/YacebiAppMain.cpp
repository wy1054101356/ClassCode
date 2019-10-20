#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<Windows.h>
using namespace std;
#define N 4								//阶数
#define MAX 100							//最大迭代次数
#define EPS 0.0001						//精度（输出打印的时候按计算控制）
#define strFileName "数据文件.csv"		//表格文件

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

	ofstream ServiceFileOut;			//进行写入文件操作	
	ServiceFileOut.open(strFileName);	//自动创建文件

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			a[i][j] = aa[i - 1][j - 1];
		b[i] = bb[i - 1];
	}

	for (int i = 1; i <= N; i++)
		x[i] = 0;						//赋予初值

	ServiceFileOut << "次数,x1,x2,x3,x4\n ";//写入首栏信息
	for (int i = 1; i <= N; i++)
		ServiceFileOut <<x[i]<< ",";

	ServiceFileOut<< "\n";
	do {								//开始迭代
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

		ServiceFileOut <<k<<",";		//写入首栏信息

		for (int i = 1; i <= N; i++)
			ServiceFileOut << y[i] << ",";
		ServiceFileOut << "\n";

		for (int i = 1; i <= N; i++)
			x[i] = y[i];
	} while (norm > EPS);				//在精度控制内继续循环

	if (norm < EPS) {
		ServiceFileOut << "结果\n";
		ServiceFileOut << "迭代次数,x1,x2,x3,x4\n";
		ServiceFileOut << k << ",";

		for (int i = 1; i <= N; i++)
			ServiceFileOut << x[i] << ",";
	}
	
	ServiceFileOut.close();				//关闭文件写入
	ShellExecute(NULL, "open", strFileName, NULL, NULL, SW_NORMAL);//打开文件
	return;
}