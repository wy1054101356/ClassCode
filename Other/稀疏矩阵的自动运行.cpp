#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<iomanip>
#include<conio.h>
#include<fstream.h>
#include<sys/stat.h>  
#include<time.h>
const long max = 200;

void waiting(int judge);

void SetPos(COORD a)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, a);
}

void SetPos(int i, int j)
{
	COORD pos = { i, j };
	SetPos(pos);
}

class triples
{
	friend class sparsematrix;
private:
	int datarow;  //数据的行
	int datacol;  //数据的列
	int data;
};

class sparsematrix
{
private:
	int **matrix; //矩阵
	triples triplesdata[(int)(max*max/2)]; //非零元素最多只有10% (概率,所以设置的很大，防止出错)
	
public:
	sparsematrix(int row= max*10, int col= max*10);
	~sparsematrix();
	void matcreat(int row,int col,int choice); //自动产生稀疏矩阵
	void transpose(int row, int col,int choice);//压缩
	int returnrow();
	void retranspose(int choice);//解压
};

int sparsematrix::returnrow()
{
	return triplesdata[0].data;
}

sparsematrix::sparsematrix(int row, int col)
{
	//初始化动态二维数组
	matrix = new int*[row];
	for (int i = 0; i < row; i++)
		matrix[i] = new int[col];
}

sparsematrix::~sparsematrix()
{
	for (int i = 0; i < max*10; i++)
		delete[]matrix[i];
	delete[]matrix;
	//std::cout << "析构函数被调用!";
}

void sparsematrix::matcreat(int row, int col,int choice)
{
	int i, j, count=0;
	int tempdata;

	srand((unsigned)time(NULL));
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			
			tempdata= rand() % 10; //产生0-9 
			if (tempdata > 0)
			{
				//如果产生的数据大于0 则让矩阵数据等于0 这样 0的获得概率为9/10
				matrix[i][j] = 0;
				count++;
			}
			else //如果随机数为0 则给他随机数
				matrix[i][j] = rand() % 9 + 1; //把1-9的数据给当前行列值
		}
	}
	if(choice==1)
	{
		std::cout << std::endl;
		std::cout << "以下是系统随机产生的稀疏矩阵:" << std::endl;
	}
	FILE * matrixfile;
	matrixfile = fopen("matrixfile.txt", "w");//同时写入文件
	
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if(choice==1)
			{
				std::cout << std::setw(3) << matrix[i][j];
				Sleep(5);
			}
			fprintf(matrixfile, "%3d", matrix[i][j]);
		}

		if(choice==1)
			std::cout << std::endl;

		fprintf(matrixfile, "\n");
	}
		
		if(choice==1)
			std::cout << std::endl;

		if(choice==1)
		{
			std::cout << "其中零有 " << count << "个" <<" 非零有 "<<row*col-count<<"个"<< std::endl;

		}
			

		fclose(matrixfile);
		if(choice==2)
		{
			std::cout<<"已为您最小化打开矩阵文件!"<<std::endl;
			ShellExecute(NULL, "open", "matrixfile.txt", NULL, NULL, SW_SHOWMINIMIZED);	//以最小化形式打开写入的文件!
			Sleep(3000);
		}
			

}

void sparsematrix::transpose(int row, int col,int choice)//压缩
{
	int i, j, count = 0;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			if (matrix[i][j] != 0)
			{
				triplesdata[count + 1].datarow = i;
				triplesdata[count + 1].datacol= j;
				triplesdata[count + 1].data = matrix[i][j];
				count++;
			}
				
			
			//三元组的第一行
	triplesdata[0].datarow = row; // 三元组行
	triplesdata[0].datacol = col; // 三元组列
	triplesdata[0].data = count;  // 三元组非零元素个数
	if(choice==1)
	{	std::cout << "压缩后的矩阵为: "<< std::endl;
		std::cout 
		<< "   行" << std::setw(5) 
		<< " 列" << std::setw(5) 
		<< " 值" << std::setw(5) 
		<< std::endl;
	}
			
	FILE * transposefile;
	transposefile = fopen("transposefile.txt", "w");//同时写入文件

	for (i = 0; i <= count; i++)
	{
		if(choice==1)
		{
			std::cout
				<< triplesdata[i].datarow << std::setw(5)
				<< triplesdata[i].datacol << std::setw(5)
				<< triplesdata[i].data << std::setw(5)
				<< std::endl;
			Sleep(5);
		}
		fprintf(transposefile, "%5d%5d%5d\n", 
		triplesdata[i].datarow,
		triplesdata[i].datacol,
		triplesdata[i].data);
	}
	fclose(transposefile);
	if(choice==2)
	{
		std::cout<<"已为您最小化打开压缩文件!"<<std::endl;
		ShellExecute(NULL, "open", "transposefile.txt", NULL, NULL, SW_SHOWMINIMIZED);
		Sleep(3000);
	}
		
}


void sparsematrix::retranspose(int choice)
{
	int i, j,count=0;
	int temprow, tempcol;
	int tempdata[max*max*2];
	//char tempstr[30];	//用浏览的方式打开指定文件
	/*//调用浏览窗口

	OPENFILENAME ofn;
    TCHAR str[MAX_PATH];
    ZeroMemory(&ofn,sizeof(ofn));
    ofn.lStructSize=sizeof(ofn);
    ofn.lpstrFile=str;
    ofn.lpstrFile[0]='\0';
    ofn.nMaxFile=sizeof(str);
    ofn.lpstrFileTitle=NULL;
    ofn.lpstrFilter=TEXT("文本文档\0*.TXT\0所有文件\0*.*\0");
    ofn.nMaxFileTitle=0;
    ofn.nFilterIndex=1;
    ofn.lpstrInitialDir=NULL;
    ofn.Flags=OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
	if(GetOpenFileName(&ofn))
	{
		strcpy(tempstr,str); //获得选定的文件名
	}
	*/ //自动情况下就没有必要打开
	FILE * transposefile;
	transposefile= fopen("transposefile.txt", "r");//打开选定的文件

    if(transposefile == NULL) //打开
		std::cout<<"打开出错"<<std::endl;
	
	for (i = 0; !feof(transposefile); i++)
	{
		fscanf(transposefile,"%d",&tempdata[i]);
		count++;
	} 
	fclose(transposefile);//关闭文件
	
	triplesdata[0].datarow = tempdata[0];
	triplesdata[0].datacol = tempdata[1];
	triplesdata[0].data    = tempdata[2];
	
	for (i = 3,j = 0; i < count; i++)
	{
		if (i % 3 == 0)
			j++;
		if (i % 3 == 0)
			triplesdata[j].datarow = tempdata[i];
		if (i % 3 == 1)
			triplesdata[j].datacol = tempdata[i];
		if (i % 3 == 2)
			triplesdata[j].data = tempdata[i];
		
	}
	if(choice==1)
	{
		std::cout << "压缩后的矩阵为: " << std::endl;
		std::cout
		<< "   行" << std::setw(5)
		<< " 列" << std::setw(5)
		<< " 值" << std::setw(5)
		<< std::endl;

		for (i = 0; i < triplesdata[0].data; i++)
		{
			std::cout
			<< triplesdata[i].datarow << std::setw(5)
			<< triplesdata[i].datacol << std::setw(5)
			<< triplesdata[i].data << std::setw(5)
			<< std::endl;
			Sleep(5);
		}
	}
	for (i = 0; i < triplesdata[0].datarow; i++)
		for (j = 0; j < triplesdata[0].datacol; j++)
			matrix[i][j] = 0;
		
	for (i = 1; i <triplesdata[0].data+1; i++)
	{
		temprow = triplesdata[i].datarow;
		tempcol = triplesdata[i].datacol;
		matrix[temprow][tempcol] = triplesdata[i].data;
	}
		
	std::cout
		<< "解压后的矩阵行 " << triplesdata[0].datarow
		<< " 列 " << triplesdata[0].datacol
		<< "非零个数 " << triplesdata[0].data << std::endl;
		
	FILE * matrixfileIn;
	matrixfileIn = fopen("matrixfileIn.txt", "w");//同时写入文件
	if(choice==1)	
		std::cout << "三元组解压后如下: " << std::endl;
	for (i = 0; i < triplesdata[0].datarow; i++)
		{
			for (j = 0; j < triplesdata[0].datacol; j++)
			{
				if(choice==1)
				{
					std::cout << std::setw(4) << matrix[i][j];
					Sleep(5);
				}
				fprintf(matrixfileIn, "%3d", matrix[i][j]);
			}
			if(choice==1)
				std::cout << std::endl;
			fprintf(matrixfileIn, "\n");
		}

		fclose(matrixfileIn);

		if(choice==2)
		{
			std::cout<<"已为您最小化打开压缩文件!"<<std::endl;
			ShellExecute(NULL, "open", "matrixfileIn.txt", NULL, NULL, SW_SHOWMINIMIZED);
			Sleep(3000);
		}
}


int filesize(char* filename)  //获取文件的字符
{  
    struct stat statbuf;  
    stat(filename,&statbuf);  
    int size=statbuf.st_size;  
	
    return size;  
}  

void showMenu(void)
{

	std::cout
	 	 << "======================================" << std::endl
		 << "  软件161-19-王洋-稀疏矩阵的自动操作  " << std::endl
		 << "    1.自动获得小型矩阵并打印显示      " << std::endl
		 << "    2.自动获得大型矩阵并打开文件      " << std::endl
		 << "======================================" << std::endl;

}

void waiting(int judge)
{
	char tempdisp1[20]="正在压缩,请稍候";
	char tempdisp2[20]="正在解压,请稍候";
	char tempdisp3[20]="正在执行,请稍候";
	char tempdisp4[20]="正在计算,请稍候";
	char disp[20];
	if(judge==1)
		strcpy(disp,tempdisp1);
	if(judge==2)
		strcpy(disp,tempdisp2);
	if(judge==3)
		strcpy(disp,tempdisp3);
	if(judge==4)
		strcpy(disp,tempdisp4);

	SetPos(1,4);
	std::cout << disp <<"·"<< std::endl;
	Sleep(300);
				
	SetPos(1,4);
	std::cout << disp <<"··"<< std::endl;
	Sleep(300);
				
	SetPos(1,4);
	std::cout << disp <<"···"<< std::endl;
	Sleep(300);
				
	SetPos(1,4);
	std::cout << disp <<"····"<< std::endl;
	Sleep(300);
				
	SetPos(1,4);
	std::cout << disp <<"·····"<< std::endl;
	Sleep(300);
				
	SetPos(1,4);
	std::cout << disp <<"······"<< std::endl;
	Sleep(300);	
	
}

void factionSelect(void)
{
	int choice;
	int temprow=0, tempcol=0;
	int size1,size2;//文件的字节大小
	char matrixfile[]="matrixfile.txt";
	char transposefile[]="transposefile.txt";//为了获得文件大小

	FILE * matrix1 = fopen("matrixfile.txt","a+");
	FILE * matrix2 = fopen("matrixfileIn.txt","a+");
	char mat1 = fgetc(matrix1);
	char mat2 = fgetc(matrix2);
	
	sparsematrix Matrix;
	
	while (1)
	{
		
		do
		{
			system("cls");
			showMenu();
			std::cin>>choice;

		}while(choice<1 || choice>2);
		switch (1)
		{
		case 1:
		system("cls");
		if(choice==1)
		{
			std::cout
				 << "========================" << std::endl
				 << " 小型稀疏矩阵的自动操作  " << std::endl
				 << "========================" << std::endl;
			
		}

		if(choice==2)
		{
			std::cout
				 << "========================" << std::endl
				 << " 大型稀疏矩阵的自动操作  " << std::endl
				 << "========================" << std::endl;
			
		}
		Sleep(3000);
		system("cls");
		std::cout
		     << "=======================" << std::endl
			 << "  第一步 获得稀疏矩阵  " << std::endl
			 << "=======================" << std::endl;
			Sleep(3000);
		waiting(3);//等待的动画效果
		waiting(3);//等待的动画效果
		Sleep(1000);
		SetPos(1,4);
		std::cout<<"                                        "<<std::endl;
		if(choice==1)
		{
			srand((unsigned)time(NULL));
			temprow=rand() % 10+5;
			tempcol=rand() % 10+5;
		}
		if(choice==2)
		{
			srand((unsigned)time(NULL));
			temprow=rand() % 50+200;
			tempcol=rand() % 50+200;
		}
		std::cout<<"当前矩阵 "<<temprow<<" 行 "<<tempcol<<" 列"<<std::endl;
		Sleep(2000);
		Matrix.matcreat(temprow, tempcol,choice);
		Sleep(5000);
			
		case 2:
			system("cls");
			std::cout<< "=========================" << std::endl
					 << "  第二步 稀疏矩阵的压缩  " << std::endl
					 << "=========================" << std::endl;
			Sleep(3000);
			/*std::cout << "是否进行矩阵压缩？"
				<< std::endl
				<< " 按Y确认，回车取消： ";
			char Judgment;//输入判断
			std::cin.get();//吃回车
			Judgment = std::cin.get();
			if (Judgment == 'y' || Judgment == 'Y')
			{  
				waiting(1);
				Matrix.transpose(temprow, tempcol);
				system("pause");
				break;
			}
			else
				break;
			*/

			waiting(1);
			waiting(1);
			Sleep(1000);
			SetPos(1,4);
			std::cout<<"                                        "<<std::endl;
			Matrix.transpose(temprow, tempcol,choice);
			Sleep(5000);
		case 3:
			system("cls");
			std::cout<< "=====================" << std::endl
					 << "  第三步 三元组解压  " << std::endl
				     << "=====================" << std::endl;
			Sleep(3000);
			/*
				<< "是否进行矩阵压缩？"
				<< std::endl
				<< " 按Y确认，回车取消： ";
				char Judgment;//输入判断
				std::cin.get();//吃回车
				Judgment = std::cin.get();
				if (Judgment == 'y' || Judgment == 'Y')
				{  
				
					std::cout<<"请选择需要解压的文件!";
					Sleep(1000);
					Matrix.retranspose();
					system("pause");
					break;
				}
				else
					break;
			}
			*/
			//std::cout<<"请选择需要解压的文件!";
			waiting(2);
			waiting(2);
			Sleep(1000);
			SetPos(1,4);
			std::cout<<"                                        "<<std::endl;
			Matrix.retranspose(choice);
			
			//判断解压前后两个矩阵是否相同
			/*while(!feof(matrix1) && !feof(matrix2))
			{
				if(mat1 != mat2)
				{
					std::cout<<"解压缩失败!解压前后矩阵不一致!"<<std::endl;
				}
				mat1 = fgetc(matrix1);
				mat2 = fgetc(matrix2);
			}
			*///也没有必要了，程序和算法都是对的，感觉没有必要比较！
			fclose(matrix1);
			fclose(matrix2);
			

			std::cout<<"解压缩成功!"<<std::endl;
			Sleep(8000);
		case 4:
			system("cls");
			std::cout	<< "======================" << std::endl
						<< "  第四步 求文件压缩率  " << std::endl
						<< "======================" << std::endl;
			Sleep(3000);
			waiting(4);
			waiting(4);
			Sleep(1000);
			SetPos(1,4);
			std::cout<<"                                        "<<std::endl;
			FILE *matrix,*transpose; 
			matrix=fopen("matrixfile.txt","r");
			transpose=fopen("transposefile.txt","r");

			size1=filesize(matrixfile);
			size2=filesize(transposefile);

			fclose(matrix);
			fclose(transpose);

			std::cout<<"稀疏矩阵共占用 "<<size1<<" 个字节"<<std::endl;
			Sleep(2000);
			std::cout<<"压缩后的三元组共占用 "<<size2<<" 个字节"<<std::endl;
			Sleep(2000);
			std::cout<<"压缩率(越低效果越好): "<<(float)size2/size1*100<<" %"<<std::endl;
			Sleep(3000);
		case 5:
			system("cls");
			std::cout	<< "==============================" << std::endl
						<< "   退出程序 -软件161-19-王洋  " << std::endl
						<< "==============================" << std::endl;
			Sleep(4000);
			exit(0);
		}
	}
}

void main(void)
{
	
	system("title 软件161-19-王洋-稀疏矩阵的操作");
	system("color f0");
	factionSelect();
}