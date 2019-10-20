#include<iostream>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<iomanip>

using namespace std;

#define N 4
//					 0	PI/6	  PI/4		PI/3	  PI/2
double xx1[N + 1] = { 0,	0.523599, 0.785398, 1.0472,	  1.5708 };
double yy1[N + 1] = { 0,	0.5,	  0.707107, 0.866025, 1 };
void juncha(double xx1[N + 1], double yy1[N + 1], double f[N + 1][N + 1])
{
	for (int i = 0; i <= N; i++)
		f[i][0] = yy1[i];
	for (int j = 1; j <= N; j++)
		for (int i = j; i <= N; i++)
			f[i][j] = (f[i][j - 1] - f[i - 1][j - 1]) / (xx1[i] - xx1[i - j]);

	cout << endl << setw(12) << "Xi" << setw(12) << "F(Xi)";


	for (int j = 1; j <= N; j++)
		cout << setw(9) << j << "jie";
	cout<< endl;

	for (int j = 1; j <= 20; j++)
		cout << "- -";
	cout << endl;

	for (int i = 0; i <= N; i++) {
		cout << setw(12) << xx1[i];
		for (int j = 0; j <= i; j++)
			cout << setw(12) << f[i][j];
		cout << endl;
	}
	for (int j = 1; j <= 20; j++)
		cout << "- -";
	cout << endl;

}

void main()
{
	int number, k;
	double p, t;
	double f[N + 1][N + 1];
	float X;

	juncha(xx1, yy1, f);

	cout << "请输入插入点的个数: ";
	cin >> number;

	for (int i = 1; i <= number; i++) {
		cout << endl << "请输入 X" << i << " =";
		cin >> X;
		p = f[N][N];
		for (int k = N - 1; k >= 0; k--)
			p = p * (X - xx1[k]) + f[k][k];
		cout << "p(" << X << ") = " << p << endl;
	}
	return;
}

