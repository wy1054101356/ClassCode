#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<time.h>
#define MAX 9999
using namespace std;
double closestPoints(double x[], double y[], int n) 
{
	double x1, x2, y1, y2;                      //��¼�±�
	double dist, minDist = MAX;
	for (int i = 0; i<n; i++)
	{ 
		for (int j = i + 1; j<n; j++) 
		{
			dist = (x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]);       //�������
			cout << "(" << x[i] << "," << y[i] << ")-(" << x[j] << "," << y[j] << ")" << "�����Ϊ��" << sqrt(dist) << endl;;      //�������
			
			if (dist<minDist)
			{
				minDist = dist;
				x1 = x[i]; y1 = y[i];
				x2 = x[j]; y2 = y[j];
			}
			
		}
	}
	cout << "������Ϊ��(" << x1 << "," << y1 << ")-(" << x2 << "," << y2 << ")"<< endl;;      //�������
	return minDist;
}
int main() 
{
	double x[100], y[100];
	double minDist;
	int n;
	cout << "�����ĸ�����\n";
	cin >> n;
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++)
	{
		x[i] = rand() % 20 - 10;
		y[i] = rand() % 20 - 10;
		cout << "(" << x[i] << ", " << y[i] << ")"<<endl;
	}
	
	minDist = closestPoints(x, y, n);
	cout << "�����Ϊ��" << sqrt(minDist)<<endl;
	return 0;
}