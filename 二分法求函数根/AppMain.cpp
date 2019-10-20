#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<Windows.h>
#define MAX_TIME 30				//定义最大二分次数
float f(float x)
{
	float a;
	a = x*x*x - sin(x) - 4 * x + 1;
	return a;
}
void main()
{
	float a, b, e;//ab为两段值 e为精度，

	float x = 999;//x是中间值 最开始不等于0即可
	int flag;

	printf("请输入 a= ");
	scanf("%f", &a);
	printf("请输入 b= ");
	scanf("%f", &b);

	printf("请输入精度值 : ");
	scanf("%f", &e);

	if (f(a)*f(b)<0)
	{
		for (int i = 0; i<MAX_TIME && f(x) != 0; i++)//定义次数
		{
			
			x = (a + b) / 2;
			if (f(x)<0)
				flag = 0;
			else
				flag = 1;
			printf("第 %2d 次 ", i + 1);
			printf("区间为[ %f ,%f ]  ", a, b);

			if (flag == 0)
				printf(" f((a+b)/2)的符号为 - ");
			else
				printf(" f((a+b)/2)的符号为 + ");

			printf("精度|bi-ai| = %f \n", fabs(b - a));

			if (f(x)*f(a)<0)
			{
				b = x;
				if (fabs(b - a)<e)
					break;
				else
					continue;
			}
			else
			{
				a = x;
				if (fabs(b - a)<e)
					break;
				else
					continue;
			}
		}
		x = (b + a) / 2;
		printf("\n x*x*x - sin(x) - 4 * x + 1=0 的根为 : %f \n\n", x);
	}
	else
	{
		printf("x*x*x - sin(x) - 4 * x + 1=0  无根!\n");
	}
	getchar();
	return;
}