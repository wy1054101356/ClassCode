#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<Windows.h>
#define MAX_TIME 30				//���������ִ���
float f(float x)
{
	float a;
	a = x*x*x - sin(x) - 4 * x + 1;
	return a;
}
void main()
{
	float a, b, e;//abΪ����ֵ eΪ���ȣ�

	float x = 999;//x���м�ֵ �ʼ������0����
	int flag;

	printf("������ a= ");
	scanf("%f", &a);
	printf("������ b= ");
	scanf("%f", &b);

	printf("�����뾫��ֵ : ");
	scanf("%f", &e);

	if (f(a)*f(b)<0)
	{
		for (int i = 0; i<MAX_TIME && f(x) != 0; i++)//�������
		{
			
			x = (a + b) / 2;
			if (f(x)<0)
				flag = 0;
			else
				flag = 1;
			printf("�� %2d �� ", i + 1);
			printf("����Ϊ[ %f ,%f ]  ", a, b);

			if (flag == 0)
				printf(" f((a+b)/2)�ķ���Ϊ - ");
			else
				printf(" f((a+b)/2)�ķ���Ϊ + ");

			printf("����|bi-ai| = %f \n", fabs(b - a));

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
		printf("\n x*x*x - sin(x) - 4 * x + 1=0 �ĸ�Ϊ : %f \n\n", x);
	}
	else
	{
		printf("x*x*x - sin(x) - 4 * x + 1=0  �޸�!\n");
	}
	getchar();
	return;
}