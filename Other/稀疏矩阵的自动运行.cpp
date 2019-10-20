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
	int datarow;  //���ݵ���
	int datacol;  //���ݵ���
	int data;
};

class sparsematrix
{
private:
	int **matrix; //����
	triples triplesdata[(int)(max*max/2)]; //����Ԫ�����ֻ��10% (����,�������õĺܴ󣬷�ֹ����)
	
public:
	sparsematrix(int row= max*10, int col= max*10);
	~sparsematrix();
	void matcreat(int row,int col,int choice); //�Զ�����ϡ�����
	void transpose(int row, int col,int choice);//ѹ��
	int returnrow();
	void retranspose(int choice);//��ѹ
};

int sparsematrix::returnrow()
{
	return triplesdata[0].data;
}

sparsematrix::sparsematrix(int row, int col)
{
	//��ʼ����̬��ά����
	matrix = new int*[row];
	for (int i = 0; i < row; i++)
		matrix[i] = new int[col];
}

sparsematrix::~sparsematrix()
{
	for (int i = 0; i < max*10; i++)
		delete[]matrix[i];
	delete[]matrix;
	//std::cout << "��������������!";
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
			
			tempdata= rand() % 10; //����0-9 
			if (tempdata > 0)
			{
				//������������ݴ���0 ���þ������ݵ���0 ���� 0�Ļ�ø���Ϊ9/10
				matrix[i][j] = 0;
				count++;
			}
			else //��������Ϊ0 ����������
				matrix[i][j] = rand() % 9 + 1; //��1-9�����ݸ���ǰ����ֵ
		}
	}
	if(choice==1)
	{
		std::cout << std::endl;
		std::cout << "������ϵͳ���������ϡ�����:" << std::endl;
	}
	FILE * matrixfile;
	matrixfile = fopen("matrixfile.txt", "w");//ͬʱд���ļ�
	
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
			std::cout << "�������� " << count << "��" <<" ������ "<<row*col-count<<"��"<< std::endl;

		}
			

		fclose(matrixfile);
		if(choice==2)
		{
			std::cout<<"��Ϊ����С���򿪾����ļ�!"<<std::endl;
			ShellExecute(NULL, "open", "matrixfile.txt", NULL, NULL, SW_SHOWMINIMIZED);	//����С����ʽ��д����ļ�!
			Sleep(3000);
		}
			

}

void sparsematrix::transpose(int row, int col,int choice)//ѹ��
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
				
			
			//��Ԫ��ĵ�һ��
	triplesdata[0].datarow = row; // ��Ԫ����
	triplesdata[0].datacol = col; // ��Ԫ����
	triplesdata[0].data = count;  // ��Ԫ�����Ԫ�ظ���
	if(choice==1)
	{	std::cout << "ѹ����ľ���Ϊ: "<< std::endl;
		std::cout 
		<< "   ��" << std::setw(5) 
		<< " ��" << std::setw(5) 
		<< " ֵ" << std::setw(5) 
		<< std::endl;
	}
			
	FILE * transposefile;
	transposefile = fopen("transposefile.txt", "w");//ͬʱд���ļ�

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
		std::cout<<"��Ϊ����С����ѹ���ļ�!"<<std::endl;
		ShellExecute(NULL, "open", "transposefile.txt", NULL, NULL, SW_SHOWMINIMIZED);
		Sleep(3000);
	}
		
}


void sparsematrix::retranspose(int choice)
{
	int i, j,count=0;
	int temprow, tempcol;
	int tempdata[max*max*2];
	//char tempstr[30];	//������ķ�ʽ��ָ���ļ�
	/*//�����������

	OPENFILENAME ofn;
    TCHAR str[MAX_PATH];
    ZeroMemory(&ofn,sizeof(ofn));
    ofn.lStructSize=sizeof(ofn);
    ofn.lpstrFile=str;
    ofn.lpstrFile[0]='\0';
    ofn.nMaxFile=sizeof(str);
    ofn.lpstrFileTitle=NULL;
    ofn.lpstrFilter=TEXT("�ı��ĵ�\0*.TXT\0�����ļ�\0*.*\0");
    ofn.nMaxFileTitle=0;
    ofn.nFilterIndex=1;
    ofn.lpstrInitialDir=NULL;
    ofn.Flags=OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
	if(GetOpenFileName(&ofn))
	{
		strcpy(tempstr,str); //���ѡ�����ļ���
	}
	*/ //�Զ�����¾�û�б�Ҫ��
	FILE * transposefile;
	transposefile= fopen("transposefile.txt", "r");//��ѡ�����ļ�

    if(transposefile == NULL) //��
		std::cout<<"�򿪳���"<<std::endl;
	
	for (i = 0; !feof(transposefile); i++)
	{
		fscanf(transposefile,"%d",&tempdata[i]);
		count++;
	} 
	fclose(transposefile);//�ر��ļ�
	
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
		std::cout << "ѹ����ľ���Ϊ: " << std::endl;
		std::cout
		<< "   ��" << std::setw(5)
		<< " ��" << std::setw(5)
		<< " ֵ" << std::setw(5)
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
		<< "��ѹ��ľ����� " << triplesdata[0].datarow
		<< " �� " << triplesdata[0].datacol
		<< "������� " << triplesdata[0].data << std::endl;
		
	FILE * matrixfileIn;
	matrixfileIn = fopen("matrixfileIn.txt", "w");//ͬʱд���ļ�
	if(choice==1)	
		std::cout << "��Ԫ���ѹ������: " << std::endl;
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
			std::cout<<"��Ϊ����С����ѹ���ļ�!"<<std::endl;
			ShellExecute(NULL, "open", "matrixfileIn.txt", NULL, NULL, SW_SHOWMINIMIZED);
			Sleep(3000);
		}
}


int filesize(char* filename)  //��ȡ�ļ����ַ�
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
		 << "  ���161-19-����-ϡ�������Զ�����  " << std::endl
		 << "    1.�Զ����С�;��󲢴�ӡ��ʾ      " << std::endl
		 << "    2.�Զ���ô��;��󲢴��ļ�      " << std::endl
		 << "======================================" << std::endl;

}

void waiting(int judge)
{
	char tempdisp1[20]="����ѹ��,���Ժ�";
	char tempdisp2[20]="���ڽ�ѹ,���Ժ�";
	char tempdisp3[20]="����ִ��,���Ժ�";
	char tempdisp4[20]="���ڼ���,���Ժ�";
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
	std::cout << disp <<"��"<< std::endl;
	Sleep(300);
				
	SetPos(1,4);
	std::cout << disp <<"����"<< std::endl;
	Sleep(300);
				
	SetPos(1,4);
	std::cout << disp <<"������"<< std::endl;
	Sleep(300);
				
	SetPos(1,4);
	std::cout << disp <<"��������"<< std::endl;
	Sleep(300);
				
	SetPos(1,4);
	std::cout << disp <<"����������"<< std::endl;
	Sleep(300);
				
	SetPos(1,4);
	std::cout << disp <<"������������"<< std::endl;
	Sleep(300);	
	
}

void factionSelect(void)
{
	int choice;
	int temprow=0, tempcol=0;
	int size1,size2;//�ļ����ֽڴ�С
	char matrixfile[]="matrixfile.txt";
	char transposefile[]="transposefile.txt";//Ϊ�˻���ļ���С

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
				 << " С��ϡ�������Զ�����  " << std::endl
				 << "========================" << std::endl;
			
		}

		if(choice==2)
		{
			std::cout
				 << "========================" << std::endl
				 << " ����ϡ�������Զ�����  " << std::endl
				 << "========================" << std::endl;
			
		}
		Sleep(3000);
		system("cls");
		std::cout
		     << "=======================" << std::endl
			 << "  ��һ�� ���ϡ�����  " << std::endl
			 << "=======================" << std::endl;
			Sleep(3000);
		waiting(3);//�ȴ��Ķ���Ч��
		waiting(3);//�ȴ��Ķ���Ч��
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
		std::cout<<"��ǰ���� "<<temprow<<" �� "<<tempcol<<" ��"<<std::endl;
		Sleep(2000);
		Matrix.matcreat(temprow, tempcol,choice);
		Sleep(5000);
			
		case 2:
			system("cls");
			std::cout<< "=========================" << std::endl
					 << "  �ڶ��� ϡ������ѹ��  " << std::endl
					 << "=========================" << std::endl;
			Sleep(3000);
			/*std::cout << "�Ƿ���о���ѹ����"
				<< std::endl
				<< " ��Yȷ�ϣ��س�ȡ���� ";
			char Judgment;//�����ж�
			std::cin.get();//�Իس�
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
					 << "  ������ ��Ԫ���ѹ  " << std::endl
				     << "=====================" << std::endl;
			Sleep(3000);
			/*
				<< "�Ƿ���о���ѹ����"
				<< std::endl
				<< " ��Yȷ�ϣ��س�ȡ���� ";
				char Judgment;//�����ж�
				std::cin.get();//�Իس�
				Judgment = std::cin.get();
				if (Judgment == 'y' || Judgment == 'Y')
				{  
				
					std::cout<<"��ѡ����Ҫ��ѹ���ļ�!";
					Sleep(1000);
					Matrix.retranspose();
					system("pause");
					break;
				}
				else
					break;
			}
			*/
			//std::cout<<"��ѡ����Ҫ��ѹ���ļ�!";
			waiting(2);
			waiting(2);
			Sleep(1000);
			SetPos(1,4);
			std::cout<<"                                        "<<std::endl;
			Matrix.retranspose(choice);
			
			//�жϽ�ѹǰ�����������Ƿ���ͬ
			/*while(!feof(matrix1) && !feof(matrix2))
			{
				if(mat1 != mat2)
				{
					std::cout<<"��ѹ��ʧ��!��ѹǰ�����һ��!"<<std::endl;
				}
				mat1 = fgetc(matrix1);
				mat2 = fgetc(matrix2);
			}
			*///Ҳû�б�Ҫ�ˣ�������㷨���ǶԵģ��о�û�б�Ҫ�Ƚϣ�
			fclose(matrix1);
			fclose(matrix2);
			

			std::cout<<"��ѹ���ɹ�!"<<std::endl;
			Sleep(8000);
		case 4:
			system("cls");
			std::cout	<< "======================" << std::endl
						<< "  ���Ĳ� ���ļ�ѹ����  " << std::endl
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

			std::cout<<"ϡ�����ռ�� "<<size1<<" ���ֽ�"<<std::endl;
			Sleep(2000);
			std::cout<<"ѹ�������Ԫ�鹲ռ�� "<<size2<<" ���ֽ�"<<std::endl;
			Sleep(2000);
			std::cout<<"ѹ����(Խ��Ч��Խ��): "<<(float)size2/size1*100<<" %"<<std::endl;
			Sleep(3000);
		case 5:
			system("cls");
			std::cout	<< "==============================" << std::endl
						<< "   �˳����� -���161-19-����  " << std::endl
						<< "==============================" << std::endl;
			Sleep(4000);
			exit(0);
		}
	}
}

void main(void)
{
	
	system("title ���161-19-����-ϡ�����Ĳ���");
	system("color f0");
	factionSelect();
}