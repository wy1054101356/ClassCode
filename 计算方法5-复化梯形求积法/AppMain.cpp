#include<iostream>
#include<math.h>
#include<iomanip>
#include<fstream>
#include<Windows.h>
using namespace std;
#define MAX 20 //最大等分区间数	3 5 7 
#define A	0	//积分下限
#define B	1	//积分上限
float f(float x) {
	return (1 / (1 + x * x));//积分函数	
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
	int n;//区间
	float a1 = A, b1 = B;//确定区间
	char strFileName[100] = "data.csv";	//文件名  写入Excel表格
	ofstream dataFileOut;	//进行写入文件操作	
	dataFileOut.open(strFileName);	//自动创建文件
	cout << "积分 1 / ( 1 + x * x )积分区间从0 到 1 " << endl;
	dataFileOut << "积分 1 / ( 1 + x * x )积分区间从0 到 1 \n";//把文档写入文件
	dataFileOut << "区间数n," << "结果T\n";
	for (int i = 1; i<MAX; i++) {
		n = i;//把所有i的值都给区间分数n
		cout << "当 n=" << setw(2) << i << "   T = " << setw(8) << computeT(a1, b1, n) << endl;
		dataFileOut << i << "," << computeT(a1, b1, n) << "\n";//把数据写入文件
	}
	dataFileOut.close();//关闭文件
	ShellExecute(NULL, TEXT("open"), strFileName, NULL, NULL, SW_NORMAL);//打开Excel文件
	return;
}