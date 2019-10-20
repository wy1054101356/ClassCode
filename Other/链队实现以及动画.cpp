#include<iostream>
#include<windows.h>
#include<iomanip>
#include<stdlib.h>
#include<iomanip>
#include<string.h>
#include<time.h>
#include<conio.h>
int count=0; 
//这里有std::cout cin 是因为std这个类里有变量count和这个程序里面的count一起会出错
enum returninfo { not_created,success, overflow, underflow};

typedef struct node
{
	int data;
	struct node *next;
}queueNode;
queueNode *rear;
queueNode *frout;

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

void linkQueue(void)
{
	frout = (struct node*)malloc(sizeof(struct node));
	frout->next = NULL;
	rear = frout;
	count = 0;
}
void insert(int &item)
{
	queueNode *newnodep = (struct node*)malloc(sizeof(struct node));
	newnodep->data = item;
	rear->next = newnodep;
	rear = rear->next;
	count++;
}

void remove()
{
	queueNode *temmp = frout->next;
	frout->next = temmp->next;
	free(temmp);
	count--;
}

void clearQueue(void)
{
	queueNode *searchp = frout->next;
	queueNode *followp = frout;
	while (searchp != rear)
	{
		followp = searchp;
		searchp = searchp->next;
		free (followp);
	}
	frout->next = NULL;
	rear = frout;
	count = 0;
}

bool empty(void)//判断队是否空
{
	if (count==0)
		return false;
	else
		return true;
}

void traverse(void)
{
	int i,j=0;
	queueNode *searchp;
	searchp = frout->next;
	SetPos(0, 10);//定位坐标
		std::cout << "frout";//显示对头
	for(i=0;searchp!=rear->next; )//
	{
		if(8 + i * 16>60)//横着输入判断快到右边界后换下一行输入
		{
			j++;//换行 纵坐标改变
			i=0;//横坐标归零
		}

		SetPos(8 + i * 16, 9 + j * 3 );
		std::cout << "┏"<< "━━━━"<< "┓" << std::endl;
		SetPos(6 + i * 14, 10 + j * 3);
		std::cout << "→"<< "┃"<< std::setw(7) << searchp->data << " ┃" << std::endl;
		//如果中间一行数字显示错乱，请在6+i*14 中把14改成16 原因是因为操作系统的不同
		SetPos(8 + i * 16, 11 + j * 3);
		std::cout << "┗" << "━━━━" << "┛";
		i++;//需要随时用到和改变i的数值，不写到循环中
		searchp = searchp->next;
	}//显示队尾
	/*
	SetPos(-3 + i * 16, 12 + j * 3);
	std::cout << "∧";
	SetPos(-3 + i * 16, 13 + j * 3);
	std::cout << "│";
	SetPos(-4 + i * 16, 14 + j * 3);
	std::cout << "";
	std::cout << std::endl;
	上面的取消了主要是自动输入会错乱导致！
	*/
SetPos(28, 7);
}
void insertStochastic()
{
	srand((unsigned)time(NULL));
	while(getchar()=='\n')
	{
	queueNode *newnodep = (struct node*)malloc(sizeof(struct node));
	newnodep->data = rand() % 1001; 
	rear->next = newnodep;
	rear = rear->next;
	count++;
	traverse();
	}	;
}

returninfo getFrout(int &item)
{
	if (!empty())
		return underflow;
	item = frout->next->data;
	return success;
}


void ShowMenu(void)
{
	std::cout
		<< "====================================" << std::endl
		<< "      软件161-19-王洋-队列的操作      " << std::endl
		<< "====================================" << std::endl
		<< " 1.数据进队  2.数据出队  3.显示长度 " << std::endl
		<< " 4.遍历数据  5.销毁现队  6.自动输入  7.退出 " << std::endl
		<< "==============================" << std::endl
		<< std::endl << std::endl//空出两行输入位置，不打乱方格的排布
		<< "==============================" << std::endl
		<< std::endl;
}

void FactionSelect(void)
{
	int choice;
	int item;
	SetPos(1, 6);//定位光标以免破坏栈
	std::cout << "请输入功能: ";
	std::cin >> choice;
	switch (choice)
	{
	case 1://进队
		SetPos(1, 6);
		std::cout << "请输入进栈一的数据（不超过六位）:   ";
		std::cin >> item;
		insert(item);	
		break;
	case 2://出队
		SetPos(1, 6);
		if (empty() == false)
		{
			std::cout << "队已空！          " << std::endl;
			system("pause");
			break;
		}
		remove();
		if (count == 0)
		{
			linkQueue();
		}
		std::cout << "数据成功出队!";
		break;
	case 3://显示站头
		SetPos(1, 6);
		if (empty() == false)
		{
			std::cout << "队已空         " << std::endl;
			system("pause");
			break;
		}
		std::cout
			<< "当前队总长为:  "
			<< count << std::endl;
		system("pause");
		break;
	case 4://遍历
		queueNode *searchp;
		SetPos(1, 6);
		if (empty() == false)
		{
			std::cout << "队已空       " << std::endl;
			system("pause");
			break;
		}	
		searchp = frout->next;
		std::cout << "当前队中数据为: ";
		while (searchp != rear->next)
		{
			std::cout << searchp->data;
			std::cout << " ";
			searchp = searchp->next;
		}
		SetPos(1, 7);
		system("pause");
		break;
	case 5:
		SetPos(1, 6);
		if (empty() == false)
		{
			std::cout << "队已空          " << std::endl;
			system("pause");
			break;
		}
		std::cout
		        << "是否销毁原队?          "
				<< std::endl
				<< " 按Y确认，回车取消： ";
		char Judgment;//输入判断
		getchar();//吃回车
		Judgment = getchar();
		if (Judgment == 'y' || Judgment == 'Y')
		{
			clearQueue();
			break;
		}
		else
		{
			system("cls");
			break;
		}
		break;
	case 6:
		SetPos(1, 6);
		std::cout<<"按回车产生一个随机数数据，可持续按！ "<<std::endl;
		std::cout<<" 按任意字符键，回车后退出！ ";
		getchar();
		insertStochastic();
		break;
	case 7:
		SetPos(1, 6);
		system("pause");
		exit(0);
	default:
		SetPos(1, 6);
		std::cout << "对不起，输入错误！              " << std::endl;
		system("pause");
		break;
	}
}
void faction(void)
{
	while (1)
	{
		ShowMenu();
		if(count!=0)
			traverse();
		FactionSelect();
		system("cls");
	}
	system("pause");
}

void main()
{
	SetConsoleTitle("软件161-19-王洋-实验002 链队基本操作");
	system("color f0");
	linkQueue();
	faction();
}
