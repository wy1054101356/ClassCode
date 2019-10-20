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
void Faction(void);//为了判断返回跳过初始化动态数组
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
void Square(stack *st);//制表符方格
void Traverse(stack *st);
void Traverse2(stack *st);

void SetPos(COORD a)// 建立光标函数 
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, a);
}

void SetPos(int i, int j)// 建立光标位置
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
		<< "   软件161-19-王洋-双栈共享   " << endl
		<< "==============================" << endl
		<< " 1.初始化  2.进栈一  3.出栈一 " << endl
		<< " 4.进栈二  5.出栈二  6.退  出 " << endl
		<< "==============================" << endl 
		<< endl << endl//空出两行输入位置，不打乱方格的排布
		<< "==============================" << endl
		<< endl;
}
void FactionSelect(void)
{
	int choice, size;
	double item;
	//这里写在循环里会报错
	SetPos(1, 6);//定位光标以免破坏栈
	cout << "请输入功能: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		SetPos(1, 6);
		if (st->StackSize != 0)
		{
			cout << "是否销毁原栈?"
				<< endl
				<< " 按Y确认，回车取消： ";
			char Judgment;//输入判断
			getchar();//吃回车
			Judgment = getchar();
			if (Judgment == 'y' || Judgment == 'Y')
			{
				Destroy(st);
				SetPos(1, 7);//包含下一句 是把上面的输入判断的显示擦掉
				cout << "                                    ";
				SetPos(1, 6);
				cout << "请输入栈的大小:  ";
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
		cout << "请输入总栈的大小: ";
		cin >> size;
		if (Create(st, size) == false)
		{
			SetPos(1, 6);
		cout << "输入不合法!                      " << endl;
		system("pause");
		break;
		}
		Create(st, size);
		break;
	case 2://进栈
		if (Full(st) == not_created)
		{
			SetPos(1, 6);
			cout << "栈尚未建立          " << endl;
			system("pause");
			break;
		}
		if (Full(st) == overflow)
		{
			SetPos(1, 6);
			cout << "栈已满！          " << endl;
			system("pause");
			break;
		}
		SetPos(1, 6);
		cout << "请输入进栈一的数据（不超过六位）:   ";
		cin >> item;
		Push(st, item);
		SetPos(1, 6);
		break;
	case 3://出栈
		if (Empty(st) == not_created)
		{
			SetPos(1, 6);
			cout << "栈尚未建立             " << endl;
			system("pause");
			break;
		}
		if (Empty(st) == underflow)
		{
			SetPos(1, 6);
			cout << "栈一已空！           " << endl;
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
			cout << "栈尚未建立          " << endl;
			system("pause");
			break;
		}
		if (Full(st) == overflow)
		{
			SetPos(1, 6);
			cout << "栈已满！          " << endl;
			system("pause");
			break;
		}
		SetPos(1, 6);
		cout << "请输入进栈二的数据（不超过六位）:   ";
		cin >> item;
		Push2(st, item);
		SetPos(1, 6);
		break;
	case 5:
		if (empty2(st) == not_created)
		{
			SetPos(1, 6);
			cout << "栈尚未建立             " << endl;
			system("pause");
			break;
		}
		if (empty2(st) == underflow)
		{
			SetPos(1, 6);
			cout << "栈二已空！           " << endl;
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
		cout << "对不起，输入错误！            " << endl;
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

bool  Create(stack *st, int size)//创建
{
	if (size <= 0)//判断输入的数据是否合法
		return false;
	st->StackSpace = ( double *)malloc(sizeof( double)*size);
	st->StackSize = size;
	st->top = -1;
	st->top2 = st->StackSize;
	return true;
}

void Destroy(stack *st)//销毁
{
	if (st->StackSpace)
		free(st->StackSpace);
	st->StackSpace = NULL;
	st->StackSize = 0;
	st->top = -1;
}

returninfo Empty(stack *st)//判断是否栈空
{
	if (!st->StackSize)
		return not_created;
	if (st->top == -1)
		return underflow;
	else
		return success;
}
returninfo empty2(stack *st)//排除栈一不输入top=-1会出错
{
	if (!st->StackSize)
		return not_created;
	if (st->top2 == st->StackSize)
		return underflow;
	else
		return success;
}
returninfo Full(stack *st)//判断是否栈满
{
	if (!st->StackSize)
		return not_created;
	if (st->top == st->StackSize - 1 || st->top + 1 == st->top2)
		return overflow;
	else
		return success;
}

void Push(stack *st,  double item)//进栈
{
	st->top++;
	st->StackSpace[st->top] = item;
}
void Push2(stack *st,  double item)//进栈
{
	st->top2--;
	st->StackSpace[st->top2] = item;
}

void Pop(stack *st)//出栈
{
	st->top--;
}
void Pop2(stack *st)//出栈
{
	st->top2++;
}
void Square(stack *st)
{

	//写制表符方格
	//方格根据输入数据确定个数
	//横着的向方格写数据会出现表格显示错乱，不好解决就竖着写
	cout << " ┏"
		 << "━━━━━━"
	     << "┓" << endl;//分开写便于修改管理
	for (int i = 1; i < st->StackSize; i++)
	{
		cout << " ┃            ┃" << endl;
		cout << " ┣";
		cout << "━━━━━━";
		cout << "┫" << endl;
	}
	cout << " ┃            ┃" << endl;

	cout << " ┗"
	     << "━━━━━━"
	     << "┛" << endl;
}
void Traverse(stack *st)
{
	if (st->top != -1)
	{
		for (int i = 0, item = 0; i <= st->top; i++)
		{

			//横着的向方格写数据会出现表格显示错乱，不好解决就竖着写
			//setpos中的参数是光标位置
			SetPos(3, 11 + i * 2);//定位进栈数据 根据自己已知，摸索出来的
			cout << st->StackSpace[i];
			SetPos(16, 11 + i * 2);//定位并显示栈顶
			cout << "<--栈一顶";
			cout << endl;
			item = i;//刷掉上一次显示的顶位置同时保证i的值不变
			SetPos(15, 11 + (item - 1) * 2);//定位 需要刷掉的位置
			cout << "            ";//刷掉上一次显示的顶位置
		}
	}
}
void Traverse2(stack *st)
{
	if (st->top2 != st->StackSize)
	{
		for (int i = st->StackSize - 1, item = 0; i >= st->top2; i--)
		{

			//横着的向方格写数据会出现表格显示错乱，不好解决就竖着写
			//setpos中的参数是光标位置
			SetPos(3, 11 + i * 2);//定位进栈数据 根据自己已知，摸索出来的
			cout << st->StackSpace[i];
			SetPos(16, 11 + i * 2);//定位并显示栈顶
			cout << "<--栈二顶";
			cout << endl;
			item = i;//刷掉上一次显示的顶位置同时保证i的值不变
			SetPos(15, 11 + (item + 1) * 2);//定位 需要刷掉的位置
			cout << "            ";//刷掉上一次显示的顶位置
		}
	}
}