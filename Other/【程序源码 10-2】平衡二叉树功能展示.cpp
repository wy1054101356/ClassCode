//平衡二叉树功能展示
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>	
#include <iomanip.h>
#include<windows.h>	
#define TRUE 1
#define FALSE 0
const int Lbalance=1;//左高
const int Ebalance=0;//等高
const int Rbalance=-1;//右高
int taller=0;//taller反映T长高与否
int shorter=0;//shorter反映T变矮与否
//二叉排序树中结点的对象设计
class BSTNode{
public:
	int data;//结点值
	int balancefactor;//结点的平衡因子
	BSTNode *lchild, *rchild;
};
//二叉排序树的对象设计
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
			cout<<setw(8)<<"无";
		if (T->rchild )
			cout<<setw(8)<<T->rchild->data;
		else 
			cout<<setw(8)<<"无";
		cout<<endl;
	}
	if(T->lchild) //递归调用先根遍历
		PreOrder(T->lchild);   	
	if(T->rchild)//递归调用先根遍历
		PreOrder(T->rchild); 
}
void balancetree::InOrder(BSTNode* T)
{
	if(T->lchild) InOrder(T->lchild);//递归调用中根遍历   
	if(T->data) //输出根的值
	{
		cout<<setw(4)<<T->data<<setw(6)<<T->balancefactor;
		if (T->lchild ) 
			cout<<setw(8)<<T->lchild->data; 
		else 
			cout<<setw(8)<<"无";
		if (T->rchild ) 
			cout<<setw(8)<<T->rchild->data; 
		else 
			cout<<setw(8)<<"无";
		cout<<endl;
	}	
	if(T->rchild) InOrder(T->rchild);//递归调用中根遍历 
}
void balancetree::postOrder(BSTNode* T)
{
	if(T->lchild) //递归调用后根遍历
		postOrder(T->lchild);  
	if(T->rchild) //递归调用后根遍历
		postOrder(T->rchild); 
	if(T->data) //输出根的值
	{
		cout<<setw(4)<<T->data<<setw(6)<<T->balancefactor;
		if (T->lchild ) 
			cout<<setw(8)<<T->lchild->data; 
		else 
			cout<<setw(8)<<"无";
		if (T->rchild ) 
			cout<<setw(8)<<T->rchild->data; 
		else 
			cout<<setw(8)<<"无";
		cout<<endl;
	}	
}
BSTNode* balancetree::R_Rotate(BSTNode* p)
{
	BSTNode *lc;//声明BSTNode* 临时变量
	lc=p->lchild;//lc指向的*p的左子树根结点
	p->lchild=lc->rchild;	//lc的右子树挂接为*p的左子树
	lc->rchild=p;			
	p=lc;//p指向新的根结点
	return p;//返回新的根结点
}
BSTNode* balancetree::L_Rotate(BSTNode* p)
{
	BSTNode *rc;//声明BSTNode* 临时变量
	rc=p->rchild;//rc指向的*p的右子树根结点
	p->rchild=rc->lchild;	//rc的左子树挂接为*p的右子树
	rc->lchild=p;
	p=rc;//p指向新的根结点
	return p;//返回新的根结点
}
BSTNode* balancetree::LeftBalance(BSTNode* T)
{
	BSTNode *lc,*rd;
	lc=T->lchild;//lc指向*T的左子树根结点
	switch(lc->balancefactor)//检查*T的左子树平衡度
		//并做相应的平衡处理
	{
	case Lbalance:
		//新结点插入在*T的左孩子的左子树上，要做单右旋处理
		T->balancefactor=lc->balancefactor=Ebalance;
		T=R_Rotate(T);
		break;
	case Rbalance:
		//新结点插入在*T的左孩子的右子树上，要做双旋处理
		rd=lc->rchild;//rd指向*T的左孩子的右子树根
		switch(rd->balancefactor)
			//修改*T及其左孩子的平衡因子
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
		//对*T的左孩子做左旋平衡处理
		T=R_Rotate(T);
		//对*T做右旋处理
	}
	return T;
}
BSTNode* balancetree::RightBalance(BSTNode* T)
{
	BSTNode *rc,*ld;
	rc=T->rchild;//rc指向*T的右子树根结点
	switch(rc->balancefactor)//检查*T的右子树平衡度
		//并做相应的平衡处理
	{
	case Rbalance://新结点插入在*T的右孩子的右子树上
		//要做单右旋处理
		T->balancefactor=rc->balancefactor=Ebalance;
		T=L_Rotate(T);
		break;
	case Lbalance://新结点插入在*T的右孩子的左子树上
		//要做双旋处理
		ld=rc->lchild;//ld指向*T的右孩子的左子树根
		switch(ld->balancefactor)
			//修改*T及其右孩子的平衡因子
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
		//对*T的右孩子做右旋平衡处理
		T=L_Rotate(T);
		//对*T做左旋处理
	}
	return T;
}
BSTNode* balancetree::InsertAVL(BSTNode* T, int e)
{
	BSTNode *p;
	//插入新结点，树长高置taller为TRUE
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
		//树中存在和e有相同关键字的结点则不再插入
		if(e==T->data)
		{
			taller=FALSE;
			return NULL;
		}
		//值小于则继续在树的左子树中搜索
		if(e < T->data)
		{			
			p=InsertAVL(T->lchild,e); 
			//插入到左子树且左子树长高
			if(p)
			{
				T->lchild=p;
				if(taller)
				{
					switch(T->balancefactor)//检查*T的平衡度
					{
					case Lbalance://原本左子树比右子树高，需要做左平衡处理
						T=LeftBalance(T);
						taller=FALSE;
						break;
					case Ebalance://原本左、右子树同高，现因左子树争高而使树增高
						T->balancefactor=Lbalance;
						taller=TRUE;
						break;
					case Rbalance://原本右子树比左子树高，现在左右子树等高
						T->balancefactor=Ebalance;
						taller=FALSE;
						break;
					}
				}
			}
		}
		//继续在*T的右子树中搜索
		else
		{
			//插入到右子树且使右子树长高
			p=InsertAVL(T->rchild,e);
			if (p)
			{
				T->rchild=p;
				if(taller)
				{
					switch(T->balancefactor)//检查*T的平衡度
					{
					case Lbalance://原本左子树比右子树高，现在左右子树等高
						T->balancefactor=Ebalance;
						taller=FALSE;
						break;
					case Ebalance://原本左、右子树同高，现因右子树增高而使树增高
						T->balancefactor=Rbalance;
						taller=TRUE;
						break;
					case Rbalance://原本右子树比左子树高，需要做右平衡处理
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
	BSTNode  *tempp1,*tempp2;//定义两个临时指针
	//左子树比右子树高
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
	BSTNode  *tempp1,*tempp2;//定义两个临时指针
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
		//根结点的右子树为空则将左子树提高并标记树变矮了
	{
		q->data=r->data;
		q=r;
		r=r->lchild;
		free(q);
		shorter=1;
	}
	else//继续递归搜索并删除
	{
		r->rchild=Delete(q,r->rchild);
	} 
	return r;
}
BSTNode* balancetree::DeleteAVL(BSTNode* p, int e)
{
	BSTNode *q;
	//抛弃空删除
	if(p==NULL) return NULL;
	else 
		if(e < p->data)
			//欲删除值小于当前结点值则继续在左子树中搜索
		{
			p->lchild = DeleteAVL(p->lchild,e);
			if(shorter==1) 
				p=LeftBalance1(p);
			return p;
		}
		else 
			if(e > p->data)//欲删除值大于当前结点值则继续在右子树中搜索
			{
				p->rchild=DeleteAVL(p->rchild,e);
				if(shorter==1) 
					p=RightBalance1(p);
				return p;
			}
			else//找到了
			{
				q=p;//将p存储到临时变量q里面
				if(p->rchild==NULL)//如果p的右子树为空则将其左子树提高一层
				{
					p=p->lchild;
					free(q);
					shorter=1;			//并标记树变矮了
				}
				else
					//如果p的左子树为空则将其右子树提高一层
					if(p->lchild==NULL)
					{
						p=p->rchild;
						free(q);
						shorter=1;
					}
					else
					{
						//将删除后的子树后的得到的新的子树的根结点赋值给q左子树
						q->lchild=Delete(q,q->lchild);
						//如果树高到变矮了则要执行删除后的左平衡处理
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
	//如果传入根结点不为空，则树已构建过，退出函数 
    if (r != NULL)
    {
        cout << "二叉平衡树已经创建!" << endl;
		cout << "是否新建二叉平衡树（y/n）";
		cin>>select;
		if (select == 'y'){
			r = NULL;
		}
		if (select == 'n'){
			return r;
		}
    }    
    //根结点为空则开始构建
	cout << "开始创建，请依次输入多个值，用空格分隔，用0作为结束符！" << endl;
    int nodeValue;
    cin >> nodeValue;
    while  (nodeValue)	
    {
        BSTNode *node = CreatNode(nodeValue);		
        //如果根为空，则将此结点设置为根结点，否则将此结点作为非根结点插入
        if (r == NULL) 
			r = node; 
		else  
			r=InsertAVL(r,nodeValue);
        cin >> nodeValue;//获取用户输入的新值
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
			   cout<<"→";
		   }   
	   }
	   cout<<p->data<<endl;
	   if(p->lchild)
	   {
		   PrintBSTree(p->lchild,i+1);
	   }
	}
} 
//菜单对象设计
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
	cout << "  平衡二叉树功能展示   " << endl;                    
	cout << "***********************" << endl;
	cout << "  1. 创建一棵平衡二叉树" << endl;                    
	cout << "  2. 向平衡树插入新数据" << endl;                  
	cout << "  3. 在树中删除一个数据" << endl;                   
	cout << "  4. 先根遍历输出平衡树" << endl;                    
	cout << "  5. 中根遍历输出平衡树" << endl;                  
	cout << "  6. 后根遍历输出平衡树" << endl;                   
	cout << " 注：按其他键将退出程序" << endl;               
	cout << "***********************" << endl;
	cout << "请选择你的操作:";
	cin >> userChose;
	return userChose;
}
void menu::selectmenu(int choice){
	int number;
	switch (choice)
	{
	case 1 : 
		root = head->BuildTree(root);
		cout << "平衡二叉树如下：" << endl;
		head->PrintBSTree(root,1);
		break;
	case 2 :
		if (root == NULL)
		{
			cout << "二叉平衡树未创建!"<<endl;
			break;
		}    
		cout << "插入新数据，请输入要插入的值：" << endl;
		cin >> number;
		root = head->InsertAVL(root,number);
		cout << "平衡二叉树如下：" << endl;
		head->PrintBSTree(root,1);
		break;
	case 3 :
		if (root == NULL)
		{
			cout << "二叉平衡树未创建!"<<endl;
			break;
		}    
		cout << "删除数据，请输入要删除的值：" << endl;
		cin >> number;
		root = head->DeleteAVL(root,number);
		cout << "平衡二叉树如下：" << endl;
		head->PrintBSTree(root,1);
		break;
	case 4 :
		if (root == NULL)
		{
			cout << "二叉平衡树未创建!"<<endl;
			break;
		}    
		cout << "先根遍历输出平衡二叉树：" << endl;
		cout<<"********************"<<endl;
		cout<<" 数据 "<<"平衡因子 "<<"左子树 "<<"右子树"<<endl;
		head->PreOrder(root);
		cout<<"********************"<<endl;
		cout << "平衡二叉树如下：" << endl;
		head->PrintBSTree(root,1);
		break;
	case 5 :
		if (root == NULL)
		{
			cout << "二叉平衡树未创建!"<<endl;
			break;
		}    
		cout << "中根遍历输出平衡二叉树：" << endl;
		cout<<"********************"<<endl;
		cout<<" 数据 "<<"平衡因子 "<<"左子树 "<<"右子树"<<endl;
		head->InOrder(root);
		cout<<"********************"<<endl;
		cout << "平衡二叉树如下：" << endl;
		head->PrintBSTree(root,1);
		break;
	case 6 :
		if (root == NULL)
		{
			cout << "二叉平衡树未创建!"<<endl;
			break;
		}    
		cout << "后根遍历输出平衡二叉树：" << endl;
		cout<<"********************"<<endl;
		cout<<" 数据 "<<"平衡因子 "<<"左子树 "<<"右子树"<<endl;
		head->postOrder(root);
		cout<<"********************"<<endl;
		cout << "平衡二叉树如下：" << endl;
		head->PrintBSTree(root,1);
		break;
	default :
		cout << "程序将退出！！！" << endl;
		system("pause");
		exit(0);
		break;
	}
}
//主函数开始
void main(void)
{
	menu mymenunow;
	system("color f0");
	SetConsoleTitle("平衡二叉树功能展示"); //设置标题	
	while(1)
	{
		mymenunow.selectmenu(mymenunow.PrintMenu());
		system("pause");
		system("cls");
	}
}
//程序结束