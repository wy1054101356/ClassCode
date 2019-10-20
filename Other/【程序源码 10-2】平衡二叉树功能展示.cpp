//ƽ�����������չʾ
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>	
#include <iomanip.h>
#include<windows.h>	
#define TRUE 1
#define FALSE 0
const int Lbalance=1;//���
const int Ebalance=0;//�ȸ�
const int Rbalance=-1;//�Ҹ�
int taller=0;//taller��ӳT�������
int shorter=0;//shorter��ӳT�䰫���
//�����������н��Ķ������
class BSTNode{
public:
	int data;//���ֵ
	int balancefactor;//����ƽ������
	BSTNode *lchild, *rchild;
};
//�����������Ķ������
class balancetree{
public:
	BSTNode* CreatNode(int nodeValue);
	void PreOrder(BSTNode* T);
	void InOrder(BSTNode* T);
	void postOrder(BSTNode* T);
	BSTNode* R_Rotate(BSTNode* p);
	BSTNode* L_Rotate(BSTNode* p);
	BSTNode* LeftBalance(BSTNode* T);
	BSTNode* RightBalance(BSTNode* T);
	BSTNode* InsertAVL(BSTNode* T, int e);
	BSTNode* LeftBalance1(BSTNode* p);
	BSTNode* RightBalance1(BSTNode* p);
	BSTNode* Delete(BSTNode* q, BSTNode* r);
	BSTNode* DeleteAVL(BSTNode* p, int e);
	BSTNode* BuildTree(BSTNode* r);
	void PrintBSTree(BSTNode* p,int i);   
};
BSTNode* balancetree::CreatNode(int nodeValue)
{
	BSTNode *node; 
	node = new BSTNode;
	node->data = nodeValue;
	node->balancefactor = 0;
	node->lchild = NULL;
	node->rchild = NULL;
	return node;
}
void balancetree::PreOrder(BSTNode* T)
{
	if(T->data) 
	{
		cout<<setw(4)<<T->data<<setw(6)<<T->balancefactor;
		if (T->lchild )
			cout<<setw(8)<<T->lchild->data;
		else 
			cout<<setw(8)<<"��";
		if (T->rchild )
			cout<<setw(8)<<T->rchild->data;
		else 
			cout<<setw(8)<<"��";
		cout<<endl;
	}
	if(T->lchild) //�ݹ�����ȸ�����
		PreOrder(T->lchild);   	
	if(T->rchild)//�ݹ�����ȸ�����
		PreOrder(T->rchild); 
}
void balancetree::InOrder(BSTNode* T)
{
	if(T->lchild) InOrder(T->lchild);//�ݹ�����и�����   
	if(T->data) //�������ֵ
	{
		cout<<setw(4)<<T->data<<setw(6)<<T->balancefactor;
		if (T->lchild ) 
			cout<<setw(8)<<T->lchild->data; 
		else 
			cout<<setw(8)<<"��";
		if (T->rchild ) 
			cout<<setw(8)<<T->rchild->data; 
		else 
			cout<<setw(8)<<"��";
		cout<<endl;
	}	
	if(T->rchild) InOrder(T->rchild);//�ݹ�����и����� 
}
void balancetree::postOrder(BSTNode* T)
{
	if(T->lchild) //�ݹ���ú������
		postOrder(T->lchild);  
	if(T->rchild) //�ݹ���ú������
		postOrder(T->rchild); 
	if(T->data) //�������ֵ
	{
		cout<<setw(4)<<T->data<<setw(6)<<T->balancefactor;
		if (T->lchild ) 
			cout<<setw(8)<<T->lchild->data; 
		else 
			cout<<setw(8)<<"��";
		if (T->rchild ) 
			cout<<setw(8)<<T->rchild->data; 
		else 
			cout<<setw(8)<<"��";
		cout<<endl;
	}	
}
BSTNode* balancetree::R_Rotate(BSTNode* p)
{
	BSTNode *lc;//����BSTNode* ��ʱ����
	lc=p->lchild;//lcָ���*p�������������
	p->lchild=lc->rchild;	//lc���������ҽ�Ϊ*p��������
	lc->rchild=p;			
	p=lc;//pָ���µĸ����
	return p;//�����µĸ����
}
BSTNode* balancetree::L_Rotate(BSTNode* p)
{
	BSTNode *rc;//����BSTNode* ��ʱ����
	rc=p->rchild;//rcָ���*p�������������
	p->rchild=rc->lchild;	//rc���������ҽ�Ϊ*p��������
	rc->lchild=p;
	p=rc;//pָ���µĸ����
	return p;//�����µĸ����
}
BSTNode* balancetree::LeftBalance(BSTNode* T)
{
	BSTNode *lc,*rd;
	lc=T->lchild;//lcָ��*T�������������
	switch(lc->balancefactor)//���*T��������ƽ���
		//������Ӧ��ƽ�⴦��
	{
	case Lbalance:
		//�½�������*T�����ӵ��������ϣ�Ҫ������������
		T->balancefactor=lc->balancefactor=Ebalance;
		T=R_Rotate(T);
		break;
	case Rbalance:
		//�½�������*T�����ӵ��������ϣ�Ҫ��˫������
		rd=lc->rchild;//rdָ��*T�����ӵ���������
		switch(rd->balancefactor)
			//�޸�*T�������ӵ�ƽ������
		{
		case Lbalance:
			T->balancefactor=Rbalance;
			lc->balancefactor=Ebalance;
			break;
		case Ebalance:
			T->balancefactor=lc->balancefactor=Ebalance;
			break;
		case Rbalance:
			T->balancefactor=Ebalance;
			lc->balancefactor=Lbalance;
			break;
		}
		rd->balancefactor=Ebalance;
		T->lchild=L_Rotate(T->lchild);
		//��*T������������ƽ�⴦��
		T=R_Rotate(T);
		//��*T����������
	}
	return T;
}
BSTNode* balancetree::RightBalance(BSTNode* T)
{
	BSTNode *rc,*ld;
	rc=T->rchild;//rcָ��*T�������������
	switch(rc->balancefactor)//���*T��������ƽ���
		//������Ӧ��ƽ�⴦��
	{
	case Rbalance://�½�������*T���Һ��ӵ���������
		//Ҫ������������
		T->balancefactor=rc->balancefactor=Ebalance;
		T=L_Rotate(T);
		break;
	case Lbalance://�½�������*T���Һ��ӵ���������
		//Ҫ��˫������
		ld=rc->lchild;//ldָ��*T���Һ��ӵ���������
		switch(ld->balancefactor)
			//�޸�*T�����Һ��ӵ�ƽ������
		{
		case Lbalance:
			T->balancefactor=Lbalance;
			rc->balancefactor=Ebalance;
			break;
		case Ebalance:
			T->balancefactor=rc->balancefactor=Ebalance;
			break;
		case Rbalance:
			T->balancefactor=Ebalance;
			rc->balancefactor=Rbalance;
			break;
		}
		ld->balancefactor=Ebalance;
		T->rchild=R_Rotate(T->rchild);
		//��*T���Һ���������ƽ�⴦��
		T=L_Rotate(T);
		//��*T����������
	}
	return T;
}
BSTNode* balancetree::InsertAVL(BSTNode* T, int e)
{
	BSTNode *p;
	//�����½�㣬��������tallerΪTRUE
	if(!T)
	{
		T=new BSTNode;
		T->data=e;
		T->lchild=T->rchild=NULL;
		T->balancefactor=Ebalance;
		taller=TRUE;
	}
	else
	{
		//���д��ں�e����ͬ�ؼ��ֵĽ�����ٲ���
		if(e==T->data)
		{
			taller=FALSE;
			return NULL;
		}
		//ֵС�������������������������
		if(e < T->data)
		{			
			p=InsertAVL(T->lchild,e); 
			//���뵽������������������
			if(p)
			{
				T->lchild=p;
				if(taller)
				{
					switch(T->balancefactor)//���*T��ƽ���
					{
					case Lbalance://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
						T=LeftBalance(T);
						taller=FALSE;
						break;
					case Ebalance://ԭ����������ͬ�ߣ��������������߶�ʹ������
						T->balancefactor=Lbalance;
						taller=TRUE;
						break;
					case Rbalance://ԭ�����������������ߣ��������������ȸ�
						T->balancefactor=Ebalance;
						taller=FALSE;
						break;
					}
				}
			}
		}
		//������*T��������������
		else
		{
			//���뵽��������ʹ����������
			p=InsertAVL(T->rchild,e);
			if (p)
			{
				T->rchild=p;
				if(taller)
				{
					switch(T->balancefactor)//���*T��ƽ���
					{
					case Lbalance://ԭ�����������������ߣ��������������ȸ�
						T->balancefactor=Ebalance;
						taller=FALSE;
						break;
					case Ebalance://ԭ����������ͬ�ߣ��������������߶�ʹ������
						T->balancefactor=Rbalance;
						taller=TRUE;
						break;
					case Rbalance://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
						T=RightBalance(T);	
						taller=FALSE;
						break;
					}
				}
			}
		}
	}
	return T;
}

BSTNode* balancetree::LeftBalance1(BSTNode* p)
{
	BSTNode  *tempp1,*tempp2;//����������ʱָ��
	//����������������
	if(p->balancefactor==1)
	{
		p->balancefactor=0;
		shorter=1;
	}
	else 
		if(p->balancefactor==0)
		{
			p->balancefactor=-1;
			shorter=0;
		}
		else
		{
			tempp1=p->rchild;
			if(tempp1->balancefactor==0)
			{
				p->rchild = tempp1->lchild;
				tempp1->lchild = p;
				tempp1->balancefactor = 1;
				p->balancefactor = -1;
				p = tempp1;
				shorter = 0;
			}
			else 
				if(tempp1->balancefactor==-1)
				{
					p->rchild=tempp1->lchild;
					tempp1->lchild=p;
					tempp1->balancefactor=p->balancefactor=0;
					p=tempp1;
					shorter=1;
				}
				else
				{
					tempp2=tempp1->lchild;
					tempp1->lchild=tempp2->rchild;
					tempp2->rchild=tempp1;
					p->rchild=tempp2->lchild;
					tempp2->lchild=p;
					if(tempp2->balancefactor==0)
					{
						p->balancefactor=0;
						tempp1->balancefactor=0;
					}
					else 
						if(tempp2->balancefactor==-1)
						{
							p->balancefactor=1;
							tempp1->balancefactor=0;
						}
						else
						{
							p->balancefactor=0;
							tempp1->balancefactor=-1;
						}
						tempp2->balancefactor=0;
						p=tempp2;
						shorter=1;
				}
		}
		return p;
}
BSTNode* balancetree::RightBalance1(BSTNode* p)
{
	BSTNode  *tempp1,*tempp2;//����������ʱָ��
	if(p->balancefactor==-1)
	{
		p->balancefactor=0;
		shorter=1;
	}
	else 
		if(p->balancefactor==0)
		{
			p->balancefactor=1;
			shorter=0;
		}
		else
		{
			tempp1=p->lchild;
			if(tempp1->balancefactor==0)
			{
				p->lchild=tempp1->rchild;
				tempp1->rchild= p;
				tempp1->balancefactor=-1;
				p->balancefactor=1;
				p=tempp1;
				shorter=0;
			}
			else 
				if(tempp1->balancefactor==1)
				{
					p->lchild=tempp1->rchild;
					tempp1->rchild=p;
					tempp1->balancefactor=p->balancefactor=0;
					p=tempp1;
					shorter=1;
				}
				else
				{
					tempp2=tempp1->rchild;
					tempp1->rchild = tempp2->lchild;
					tempp2->lchild = tempp1;
					p->lchild = tempp2->rchild;
					tempp2->rchild = p;
					if(tempp2->balancefactor == 0)
					{
						p->balancefactor = 0;
						tempp1->balancefactor = 0;
					}
					else 
						if(tempp2->balancefactor == 1)
						{
							p->balancefactor = -1;
							tempp1->balancefactor = 0;
						}
						else
						{
							p->balancefactor=0;
							tempp1->balancefactor=1;
						}
						tempp2->balancefactor=0;
						p=tempp2;
						shorter=1;
				}
		}
		return p;
}

BSTNode* balancetree::Delete(BSTNode* q, BSTNode* r)
{
	if(r->rchild==NULL)
		//������������Ϊ������������߲�������䰫��
	{
		q->data=r->data;
		q=r;
		r=r->lchild;
		free(q);
		shorter=1;
	}
	else//�����ݹ�������ɾ��
	{
		r->rchild=Delete(q,r->rchild);
	} 
	return r;
}
BSTNode* balancetree::DeleteAVL(BSTNode* p, int e)
{
	BSTNode *q;
	//������ɾ��
	if(p==NULL) return NULL;
	else 
		if(e < p->data)
			//��ɾ��ֵС�ڵ�ǰ���ֵ�������������������
		{
			p->lchild = DeleteAVL(p->lchild,e);
			if(shorter==1) 
				p=LeftBalance1(p);
			return p;
		}
		else 
			if(e > p->data)//��ɾ��ֵ���ڵ�ǰ���ֵ�������������������
			{
				p->rchild=DeleteAVL(p->rchild,e);
				if(shorter==1) 
					p=RightBalance1(p);
				return p;
			}
			else//�ҵ���
			{
				q=p;//��p�洢����ʱ����q����
				if(p->rchild==NULL)//���p��������Ϊ���������������һ��
				{
					p=p->lchild;
					free(q);
					shorter=1;			//��������䰫��
				}
				else
					//���p��������Ϊ���������������һ��
					if(p->lchild==NULL)
					{
						p=p->rchild;
						free(q);
						shorter=1;
					}
					else
					{
						//��ɾ�����������ĵõ����µ������ĸ���㸳ֵ��q������
						q->lchild=Delete(q,q->lchild);
						//������ߵ��䰫����Ҫִ��ɾ�������ƽ�⴦��
						if(shorter==1) 
							q=LeftBalance1(q);
						p=q;
					}
			}
			return p;
}
BSTNode* balancetree::BuildTree(BSTNode* r)
{
	char select;
	//����������㲻Ϊ�գ������ѹ��������˳����� 
    if (r != NULL)
    {
        cout << "����ƽ�����Ѿ�����!" << endl;
		cout << "�Ƿ��½�����ƽ������y/n��";
		cin>>select;
		if (select == 'y'){
			r = NULL;
		}
		if (select == 'n'){
			return r;
		}
    }    
    //�����Ϊ����ʼ����
	cout << "��ʼ������������������ֵ���ÿո�ָ�����0��Ϊ��������" << endl;
    int nodeValue;
    cin >> nodeValue;
    while  (nodeValue)	
    {
        BSTNode *node = CreatNode(nodeValue);		
        //�����Ϊ�գ��򽫴˽������Ϊ����㣬���򽫴˽����Ϊ�Ǹ�������
        if (r == NULL) 
			r = node; 
		else  
			r=InsertAVL(r,nodeValue);
        cin >> nodeValue;//��ȡ�û��������ֵ
    }
    return r;    
}
void balancetree::PrintBSTree(BSTNode* p,int i)
{
	int j;
	if(!p)
	{
		cout<<"NULL"<<endl;
	}
	else
	{

	   if(p->rchild)
	   {
		   PrintBSTree(p->rchild,i+1);
	   }
	   
	   if(i>1)
	   {
		   for(j=1;j<=i-1;j++)
		   {
			   cout<<"  ";
		   }
		   if(j=i)
		   {
			   cout<<"��";
		   }   
	   }
	   cout<<p->data<<endl;
	   if(p->lchild)
	   {
		   PrintBSTree(p->lchild,i+1);
	   }
	}
} 
//�˵��������
class menu
{
public:
	menu();
	int PrintMenu();
	void selectmenu(int choice);
protected:
	balancetree *head;
	BSTNode *root;
	
};
menu::menu()
{
	root=NULL;
}
int menu::PrintMenu()
{
	int userChose;
	cout << "  ƽ�����������չʾ   " << endl;                    
	cout << "***********************" << endl;
	cout << "  1. ����һ��ƽ�������" << endl;                    
	cout << "  2. ��ƽ��������������" << endl;                  
	cout << "  3. ������ɾ��һ������" << endl;                   
	cout << "  4. �ȸ��������ƽ����" << endl;                    
	cout << "  5. �и��������ƽ����" << endl;                  
	cout << "  6. ����������ƽ����" << endl;                   
	cout << " ע�������������˳�����" << endl;               
	cout << "***********************" << endl;
	cout << "��ѡ����Ĳ���:";
	cin >> userChose;
	return userChose;
}
void menu::selectmenu(int choice){
	int number;
	switch (choice)
	{
	case 1 : 
		root = head->BuildTree(root);
		cout << "ƽ����������£�" << endl;
		head->PrintBSTree(root,1);
		break;
	case 2 :
		if (root == NULL)
		{
			cout << "����ƽ����δ����!"<<endl;
			break;
		}    
		cout << "���������ݣ�������Ҫ�����ֵ��" << endl;
		cin >> number;
		root = head->InsertAVL(root,number);
		cout << "ƽ����������£�" << endl;
		head->PrintBSTree(root,1);
		break;
	case 3 :
		if (root == NULL)
		{
			cout << "����ƽ����δ����!"<<endl;
			break;
		}    
		cout << "ɾ�����ݣ�������Ҫɾ����ֵ��" << endl;
		cin >> number;
		root = head->DeleteAVL(root,number);
		cout << "ƽ����������£�" << endl;
		head->PrintBSTree(root,1);
		break;
	case 4 :
		if (root == NULL)
		{
			cout << "����ƽ����δ����!"<<endl;
			break;
		}    
		cout << "�ȸ��������ƽ���������" << endl;
		cout<<"********************"<<endl;
		cout<<" ���� "<<"ƽ������ "<<"������ "<<"������"<<endl;
		head->PreOrder(root);
		cout<<"********************"<<endl;
		cout << "ƽ����������£�" << endl;
		head->PrintBSTree(root,1);
		break;
	case 5 :
		if (root == NULL)
		{
			cout << "����ƽ����δ����!"<<endl;
			break;
		}    
		cout << "�и��������ƽ���������" << endl;
		cout<<"********************"<<endl;
		cout<<" ���� "<<"ƽ������ "<<"������ "<<"������"<<endl;
		head->InOrder(root);
		cout<<"********************"<<endl;
		cout << "ƽ����������£�" << endl;
		head->PrintBSTree(root,1);
		break;
	case 6 :
		if (root == NULL)
		{
			cout << "����ƽ����δ����!"<<endl;
			break;
		}    
		cout << "����������ƽ���������" << endl;
		cout<<"********************"<<endl;
		cout<<" ���� "<<"ƽ������ "<<"������ "<<"������"<<endl;
		head->postOrder(root);
		cout<<"********************"<<endl;
		cout << "ƽ����������£�" << endl;
		head->PrintBSTree(root,1);
		break;
	default :
		cout << "�����˳�������" << endl;
		system("pause");
		exit(0);
		break;
	}
}
//��������ʼ
void main(void)
{
	menu mymenunow;
	system("color f0");
	SetConsoleTitle("ƽ�����������չʾ"); //���ñ���	
	while(1)
	{
		mymenunow.selectmenu(mymenunow.PrintMenu());
		system("pause");
		system("cls");
	}
}
//�������