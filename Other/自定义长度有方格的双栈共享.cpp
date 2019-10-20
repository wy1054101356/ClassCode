#include<iostream>
#include<windows.h>
#include<iomanip>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
using namespace std;
typedef struct SequentialStack
{
	double *StackSpace;
	int StackSize;
	int top;
	int top2;

}stack;

stack *st;

enum returninfo { not_created, success, overflow, underflow };

void ShowMenu(void);
void Faction(void);//Ϊ���жϷ���������ʼ����̬����
void FactionSelect(void);
void InitStack(stack *st);
bool Create(stack *st, int size);
void Destroy(stack *st);
returninfo Empty(stack *st);
returninfo empty2(stack *st);
returninfo Full(stack *st);
void Push(stack *st, double item);
void Push2(stack *st, double item);
void Pop(stack *st);
void Pop2(stack *st);
void Square(stack *st);//�Ʊ������
void Traverse(stack *st);
void Traverse2(stack *st);

void SetPos(COORD a)// ������꺯�� 
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, a);
}

void SetPos(int i, int j)// �������λ��
{
	COORD pos = { i, j };
	SetPos(pos);
}

void main()
{
	system("color f0");
	st = (stack *)malloc(sizeof(stack));
	InitStack(st);
	Faction();
}

void Faction(void)
{
	while (1)
	{
		ShowMenu();
		if (st->StackSize != 0)
		{
			Square(st);
			Traverse(st);
			Traverse2(st);
		}
		FactionSelect();
		system("cls");
	}
	system("pause");
}
void ShowMenu(void)
{
	cout
		<< "==============================" << endl
		<< "   ���161-19-����-˫ջ����   " << endl
		<< "==============================" << endl
		<< " 1.��ʼ��  2.��ջһ  3.��ջһ " << endl
		<< " 4.��ջ��  5.��ջ��  6.��  �� " << endl
		<< "==============================" << endl 
		<< endl << endl//�ճ���������λ�ã������ҷ�����Ų�
		<< "==============================" << endl
		<< endl;
}
void FactionSelect(void)
{
	int choice, size;
	double item;
	//����д��ѭ����ᱨ��
	SetPos(1, 6);//��λ��������ƻ�ջ
	cout << "�����빦��: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		SetPos(1, 6);
		if (st->StackSize != 0)
		{
			cout << "�Ƿ�����ԭջ?"
				<< endl
				<< " ��Yȷ�ϣ��س�ȡ���� ";
			char Judgment;//�����ж�
			getchar();//�Իس�
			Judgment = getchar();
			if (Judgment == 'y' || Judgment == 'Y')
			{
				Destroy(st);
				SetPos(1, 7);//������һ�� �ǰ�����������жϵ���ʾ����
				cout << "                                    ";
				SetPos(1, 6);
				cout << "������ջ�Ĵ�С:  ";
				cin >> size;
				Create(st, size);
				break;
			}
			else
			{
				system("cls");
				Faction();
			}
		}
		cout << "��������ջ�Ĵ�С: ";
		cin >> size;
		if (Create(st, size) == false)
		{
			SetPos(1, 6);
		cout << "���벻�Ϸ�!                      " << endl;
		system("pause");
		break;
		}
		Create(st, size);
		break;
	case 2://��ջ
		if (Full(st) == not_created)
		{
			SetPos(1, 6);
			cout << "ջ��δ����          " << endl;
			system("pause");
			break;
		}
		if (Full(st) == overflow)
		{
			SetPos(1, 6);
			cout << "ջ������          " << endl;
			system("pause");
			break;
		}
		SetPos(1, 6);
		cout << "�������ջһ�����ݣ���������λ��:   ";
		cin >> item;
		Push(st, item);
		SetPos(1, 6);
		break;
	case 3://��ջ
		if (Empty(st) == not_created)
		{
			SetPos(1, 6);
			cout << "ջ��δ����             " << endl;
			system("pause");
			break;
		}
		if (Empty(st) == underflow)
		{
			SetPos(1, 6);
			cout << "ջһ�ѿգ�           " << endl;
			system("pause");
			break;
		}
		Pop(st);
		SetPos(1, 6);
		break;
	case 4:
		if (Full(st) == not_created)
		{
			SetPos(1, 6);
			cout << "ջ��δ����          " << endl;
			system("pause");
			break;
		}
		if (Full(st) == overflow)
		{
			SetPos(1, 6);
			cout << "ջ������          " << endl;
			system("pause");
			break;
		}
		SetPos(1, 6);
		cout << "�������ջ�������ݣ���������λ��:   ";
		cin >> item;
		Push2(st, item);
		SetPos(1, 6);
		break;
	case 5:
		if (empty2(st) == not_created)
		{
			SetPos(1, 6);
			cout << "ջ��δ����             " << endl;
			system("pause");
			break;
		}
		if (empty2(st) == underflow)
		{
			SetPos(1, 6);
			cout << "ջ���ѿգ�           " << endl;
			system("pause");
			break;
		}
		Pop2(st);
		SetPos(1, 6);
		break;
	case 6:
		system("pause");
		exit(0);
	default:
		SetPos(1, 6);
		cout << "�Բ����������            " << endl;
		system("pause");
		break;
	}
}

void InitStack(stack *st)
{
	st->StackSpace = NULL;
	st->StackSize = 0;
	st->top = -1;
	st->top2 = 0;
}

bool  Create(stack *st, int size)//����
{
	if (size <= 0)//�ж�����������Ƿ�Ϸ�
		return false;
	st->StackSpace = ( double *)malloc(sizeof( double)*size);
	st->StackSize = size;
	st->top = -1;
	st->top2 = st->StackSize;
	return true;
}

void Destroy(stack *st)//����
{
	if (st->StackSpace)
		free(st->StackSpace);
	st->StackSpace = NULL;
	st->StackSize = 0;
	st->top = -1;
}

returninfo Empty(stack *st)//�ж��Ƿ�ջ��
{
	if (!st->StackSize)
		return not_created;
	if (st->top == -1)
		return underflow;
	else
		return success;
}
returninfo empty2(stack *st)//�ų�ջһ������top=-1�����
{
	if (!st->StackSize)
		return not_created;
	if (st->top2 == st->StackSize)
		return underflow;
	else
		return success;
}
returninfo Full(stack *st)//�ж��Ƿ�ջ��
{
	if (!st->StackSize)
		return not_created;
	if (st->top == st->StackSize - 1 || st->top + 1 == st->top2)
		return overflow;
	else
		return success;
}

void Push(stack *st,  double item)//��ջ
{
	st->top++;
	st->StackSpace[st->top] = item;
}
void Push2(stack *st,  double item)//��ջ
{
	st->top2--;
	st->StackSpace[st->top2] = item;
}

void Pop(stack *st)//��ջ
{
	st->top--;
}
void Pop2(stack *st)//��ջ
{
	st->top2++;
}
void Square(stack *st)
{

	//д�Ʊ������
	//���������������ȷ������
	//���ŵ��򷽸�д���ݻ���ֱ����ʾ���ң����ý��������д
	cout << " ��"
		 << "������������"
	     << "��" << endl;//�ֿ�д�����޸Ĺ���
	for (int i = 1; i < st->StackSize; i++)
	{
		cout << " ��            ��" << endl;
		cout << " ��";
		cout << "������������";
		cout << "��" << endl;
	}
	cout << " ��            ��" << endl;

	cout << " ��"
	     << "������������"
	     << "��" << endl;
}
void Traverse(stack *st)
{
	if (st->top != -1)
	{
		for (int i = 0, item = 0; i <= st->top; i++)
		{

			//���ŵ��򷽸�д���ݻ���ֱ����ʾ���ң����ý��������д
			//setpos�еĲ����ǹ��λ��
			SetPos(3, 11 + i * 2);//��λ��ջ���� �����Լ���֪������������
			cout << st->StackSpace[i];
			SetPos(16, 11 + i * 2);//��λ����ʾջ��
			cout << "<--ջһ��";
			cout << endl;
			item = i;//ˢ����һ����ʾ�Ķ�λ��ͬʱ��֤i��ֵ����
			SetPos(15, 11 + (item - 1) * 2);//��λ ��Ҫˢ����λ��
			cout << "            ";//ˢ����һ����ʾ�Ķ�λ��
		}
	}
}
void Traverse2(stack *st)
{
	if (st->top2 != st->StackSize)
	{
		for (int i = st->StackSize - 1, item = 0; i >= st->top2; i--)
		{

			//���ŵ��򷽸�д���ݻ���ֱ����ʾ���ң����ý��������д
			//setpos�еĲ����ǹ��λ��
			SetPos(3, 11 + i * 2);//��λ��ջ���� �����Լ���֪������������
			cout << st->StackSpace[i];
			SetPos(16, 11 + i * 2);//��λ����ʾջ��
			cout << "<--ջ����";
			cout << endl;
			item = i;//ˢ����һ����ʾ�Ķ�λ��ͬʱ��֤i��ֵ����
			SetPos(15, 11 + (item + 1) * 2);//��λ ��Ҫˢ����λ��
			cout << "            ";//ˢ����һ����ʾ�Ķ�λ��
		}
	}
}