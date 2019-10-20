#include<iostream>
#include<math.h>
#include<fstream>
#include<iomanip>
#include<Windows.h>
using namespace std;
#define MAX 20		//最大分区次数
#define eps 0.00005	//截断误差
#define A	0	//积分下限
#define B	1	//积分上限

float f(float x) {
	return (1 / (1 + x * x));//积分函数	
}
float computeT(float a, float b){
	float h, T = 0;
	h = (b - a) / 2;
	T = h * (f(a) + 2 * T + f(b)) / 2;
	return T;
}
void main(){
	float a, b, T1, T2, S, x, h;
	int i = 1;//记录步长
	a = A; b = B;//把宏赋给积分上下限
	char strFileName[100] = "data.csv";//文件名 写入Excel表格
	ofstream dataFileOut;		//进行写入文件操作	
	dataFileOut.open(strFileName);	//自动创建文件
	cout << "积分 1 / ( 1 + x * x )积分区间从0 到 1 " << endl;
	dataFileOut << "积分 1 / ( 1 + x * x )积分区间从0 到 1 \n";
	dataFileOut << "次数," << "Tn\n";//写入文件
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
		cout << "第" << setw(2) << i << "次 Tn = " << setw(8) << T2 << endl;//显示每一次截断区间
		i++;
		if (fabs(T2 - T1) >= eps){//如果截断区间满足误差要求
			T1 = T2;
			h /= 2;
			continue;
		}
		else
			break;
	}
	cout << endl << "结果是: " << T2 << endl;
	dataFileOut << "结果是:," << T2;
	dataFileOut.close();//关闭文件
	ShellExecute(NULL, TEXT("open"), strFileName, NULL, NULL, SW_NORMAL);//打开Excel文件
	return;
}