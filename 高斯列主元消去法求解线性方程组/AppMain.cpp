#include<conio.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<Windows.h>
using namespace std;
#define N 4

void main()
{
	static double a[N][N] =			//系数矩阵
	{
		{ 8, 7 , 0, 0 },
		{ 6, 12, 5, 0 },
		{ 0, 4,  9, 3 },
		{ 0, 0,  1, 2 },
	};

	double b[N] = { 0,-2, 8, 6 };		//值矩阵
	/*
	static double a[N][N] =				//系数矩阵
	{

	{ 5, 7 , 0, 0 },
	{ 19, 12, 5, 0 },
	{ 50, 14,  9, 3 },
	{ 10, 2,  3, 2 },

	};
	double b[N] = { 0,-2, 8, 6 };		//值矩阵
	*/


	double x[N] = { 0, 0, 0, 0 };
	float r, s, e;
	int p, flag = 1;
	printf("线性方程组如下\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%10.15fx%d", a[i][j], j + 1);
			if (j < N - 1)
				printf(" +");
		}
		printf("= %10.15f", b[i]);
		printf("\n");

	}
	printf("\n");

	printf("线性方程组的系数矩阵如下\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%10.15f", a[i][j]);

		printf("%10.15f", b[i]);
		printf("\n");

	}
	printf("\n");

	for (int k = 0; k < N - 1; k++)
	{
		p = k;
		e = a[k][k];
		for (int i = k; i < N; i++)
			if (fabs(a[i][k]) > e)
			{
				e = fabs(a[i][k]);
				p = i;
			}
		for (int j = k; j < N; j++)
		{
			s = a[k][j];
			a[k][j] = a[p][j];
			a[p][j] = s;
		}
		s = b[k];
		b[k] = b[p];
		b[p] = s;
		if (a[k][k] == 0)
		{
			printf("\n");
			flag = 0;
			break;
		}
		else
		{
			for (int i = k + 1; i < N; i++)
			{
				r = a[i][k] / a[k][k];
				if (a[k][k] != 0)
				{
					for (int j = k; j < N; j++)
						a[i][j] = a[i][j] - r * a[k][j];
				}
				b[i] = b[i] - r * b[k];
			}

		}
	}

	printf("系数矩阵化简如下\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%10.15f", a[i][j]);
		printf("%10.15f", b[i]);
		printf("\n");
	}

	printf("\n");

	if (flag)
	{
		x[N - 1] = b[N - 1] / a[N - 1][N - 1];
		for (int i = N - 2; i >= 0; i--)
		{
			s = b[i];
			for (int j = i + 1; j < N; j++)
				s = s - a[i][j] * x[j];

			x[i] = s / a[i][i];
		}

		printf("方程组的根如下\n");

		for (int i = 0; i < N; i++)
			printf(" x(%d)=%10.15f\n", i + 1, x[i]);
	}
	else
		printf("此线性方程组无根!\n");
	system("pause");
	return;
}