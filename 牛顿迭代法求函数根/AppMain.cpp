
#include<stdio.h>
#include<math.h>
#include<conio.h>
#define maxrept 100


float f(float x)
{
	return (x*x*x - sin(x) - 4 * x + 1);//f(x)
}

float df(float x)
{	
	return (3 * x*x - cos(x) - 4);		//f(x)的导数

}

float iterate(float x)
{
	float x1;
	x1 = x - f(x) / df(x);				//牛顿迭代函数
	return (x1);
}
void main()
{
	float x0, x1, eps, d;		//eps 求解精度
	int k = 0;
	printf("请输入迭代初值：");
	scanf("%f", &x0);

	printf("请输入精度: ");
	scanf("%f", &eps);

	printf("\ 次数		Xk       误差 \n");
	printf("\ %d      %f	 %f\n", k, x0, fabs(x0));

	do
	{
		k++;
		x1 = iterate(x0);
		printf("\ %d      %f	 %f\n", k, x0, fabs(x0-x1));

		d = fabs(x1 - x0);
		x0 = x1;
	} while ((d >= eps)&&(k<maxrept));

	if (k<maxrept)
		printf("x*x*x - sin(x) - 4 * x + 1 f(x)=0 的 根为 : %f   k=%d\n", x1, k);
	else
		printf("没有找到!\n");
	getch();
	return;
}