
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
	return (3 * x*x - cos(x) - 4);		//f(x)�ĵ���

}

float iterate(float x)
{
	float x1;
	x1 = x - f(x) / df(x);				//ţ�ٵ�������
	return (x1);
}
void main()
{
	float x0, x1, eps, d;		//eps ��⾫��
	int k = 0;
	printf("�����������ֵ��");
	scanf("%f", &x0);

	printf("�����뾫��: ");
	scanf("%f", &eps);

	printf("\ ����		Xk       ��� \n");
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
		printf("x*x*x - sin(x) - 4 * x + 1 f(x)=0 �� ��Ϊ : %f   k=%d\n", x1, k);
	else
		printf("û���ҵ�!\n");
	getch();
	return;
}