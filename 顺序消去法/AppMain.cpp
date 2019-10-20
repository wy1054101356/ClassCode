#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<iostream>
using namespace std;


#define n 4
int main()
{
	int k, i, j, r;
	double c, a[n][n + 1] =
	{
		{ 8,7, 0,0,  0 },
		{ 6,12,5,0, -2 },
		{ 0,4, 9,3,  8 },
		{ 0,0, 1,2,  6 },
	};
	
	/*
	double c, a[n][n + 1] =
	{
	{ 5, 7, 0, 0 ,0 },
	{ 19, 12, 5, 0 ,-2 },
	{ 50, 14,  9, 3 ,8 },
	{ 10, 02,  3, 2 ,6 }
	};
	*/
	printf("线性方程组如下\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%10.15f(x%d)", a[i][j], j + 1);

			if (j < n - 1)
				printf(" +");
			if (j == n - 1)
				printf(" = ");

		}
		printf("%10.15f", a[i][n]);
		printf("\n");

	}
	printf("\n");

	double eps = 0.0005;

	for (k = 0; k < n - 1; k++)
	{
		r = k;
		for (i = k; i < n; i++)
			if (fabs(a[i][k]) > fabs(a[r][k]))
				r = i;

		if (fabs(a[r][k]) < eps)

		{
			cout << "\n消元失败！" << endl;
			exit(0);
		}
		if (r > k)
		{
			for (j = k; j < n + 1; j++)
			{
				c = a[k][j];
				a[k][j] = a[r][j];
				a[r][j] = c;
			}
		}
		for (i = k + 1; i < n; i++)
		{
			a[i][k] = a[i][k] / a[k][k];

			for (j = k + 1; j < n + 1; j++)
				a[i][j] = a[i][j] - a[i][k] * a[k][j];

		}
	}

	a[n - 1][n] = a[n - 1][n] / a[n - 1][n - 1];

	for (k = n - 2; k >= 0; k--)
	{
		c = 0;

		for (j = k + 1; j < n + 1; j++)
			c = c + a[k][j] * a[j][n];

		a[k][n] = (a[k][n] - c) / a[k][k];

	}
	printf("高斯顺序消元法结果为：\n");

	for (k = 0; k < n; k++)
		printf("x(%d)=%10.15f \n", k + 1, a[k][n]);

	system("pause");

	return 0;
}
