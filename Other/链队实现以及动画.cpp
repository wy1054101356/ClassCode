#include<iostream>
#include<windows.h>
#include<iomanip>
#include<stdlib.h>
#include<iomanip>
#include<string.h>
#include<time.h>
#include<conio.h>
int count=0; 
//������std::cout cin ����Ϊstd��������б���count��������������countһ������
enum returninfo { not_created,success, overflow, underflow};

typedef struct node
{
	int data;
	struct node *next;
}queueNode;
queueNode *rear;
queueNode *frout;

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

bool empty(void)//�ж϶��Ƿ��
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
	SetPos(0, 10);//��λ����
		std::cout << "frout";//��ʾ��ͷ
	for(i=0;searchp!=rear->next; )//
	{
		if(8 + i * 16>60)//���������жϿ쵽�ұ߽����һ������
		{
			j++;//���� ������ı�
			i=0;//���������
		}

		SetPos(8 + i * 16, 9 + j * 3 );
		std::cout << "��"<< "��������"<< "��" << std::endl;
		SetPos(6 + i * 14, 10 + j * 3);
		std::cout << "��"<< "��"<< std::setw(7) << searchp->data << " ��" << std::endl;
		//����м�һ��������ʾ���ң�����6+i*14 �а�14�ĳ�16 ԭ������Ϊ����ϵͳ�Ĳ�ͬ
		SetPos(8 + i * 16, 11 + j * 3);
		std::cout << "��" << "��������" << "��";
		i++;//��Ҫ��ʱ�õ��͸ı�i����ֵ����д��ѭ����
		searchp = searchp->next;
	}//��ʾ��β
	/*
	SetPos(-3 + i * 16, 12 + j * 3);
	std::cout << "��";
	SetPos(-3 + i * 16, 13 + j * 3);
	std::cout << "��";
	SetPos(-4 + i * 16, 14 + j * 3);
	std::cout << "";
	std::cout << std::endl;
	�����ȡ������Ҫ���Զ��������ҵ��£�
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
		<< "      ���161-19-����-���еĲ���      " << std::endl
		<< "====================================" << std::endl
		<< " 1.���ݽ���  2.���ݳ���  3.��ʾ���� " << std::endl
		<< " 4.��������  5.�����ֶ�  6.�Զ�����  7.�˳� " << std::endl
		<< "==============================" << std::endl
		<< std::endl << std::endl//�ճ���������λ�ã������ҷ�����Ų�
		<< "==============================" << std::endl
		<< std::endl;
}

void FactionSelect(void)
{
	int choice;
	int item;
	SetPos(1, 6);//��λ��������ƻ�ջ
	std::cout << "�����빦��: ";
	std::cin >> choice;
	switch (choice)
	{
	case 1://����
		SetPos(1, 6);
		std::cout << "�������ջһ�����ݣ���������λ��:   ";
		std::cin >> item;
		insert(item);	
		break;
	case 2://����
		SetPos(1, 6);
		if (empty() == false)
		{
			std::cout << "���ѿգ�          " << std::endl;
			system("pause");
			break;
		}
		remove();
		if (count == 0)
		{
			linkQueue();
		}
		std::cout << "���ݳɹ�����!";
		break;
	case 3://��ʾվͷ
		SetPos(1, 6);
		if (empty() == false)
		{
			std::cout << "���ѿ�         " << std::endl;
			system("pause");
			break;
		}
		std::cout
			<< "��ǰ���ܳ�Ϊ:  "
			<< count << std::endl;
		system("pause");
		break;
	case 4://����
		queueNode *searchp;
		SetPos(1, 6);
		if (empty() == false)
		{
			std::cout << "���ѿ�       " << std::endl;
			system("pause");
			break;
		}	
		searchp = frout->next;
		std::cout << "��ǰ��������Ϊ: ";
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
			std::cout << "���ѿ�          " << std::endl;
			system("pause");
			break;
		}
		std::cout
		        << "�Ƿ�����ԭ��?          "
				<< std::endl
				<< " ��Yȷ�ϣ��س�ȡ���� ";
		char Judgment;//�����ж�
		getchar();//�Իس�
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
		std::cout<<"���س�����һ����������ݣ��ɳ������� "<<std::endl;
		std::cout<<" �������ַ������س����˳��� ";
		getchar();
		insertStochastic();
		break;
	case 7:
		SetPos(1, 6);
		system("pause");
		exit(0);
	default:
		SetPos(1, 6);
		std::cout << "�Բ����������              " << std::endl;
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
	SetConsoleTitle("���161-19-����-ʵ��002 ���ӻ�������");
	system("color f0");
	linkQueue();
	faction();
}
