#include <iostream>  
#include <string>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <fstream>
using namespace std;

struct node
{
	double weight;//Ȩֵ
	char ch;//�ַ�
	string code;//�ַ�����
	int lchild, rchild, parent;//�����ӽڵ� ���׽ڵ�
};
class HuffMan 
{
private:
	node * hufftree;//��
	int number;//�ַ���
	int* weight;//Ȩֵ
public:
	HuffMan(int number);//���캯��
	~HuffMan();//��������
	void select(int *a, int *b, int number);//��Ȩֵ��С������a��b  
	void huffTree(vector<char>& str, vector<int>& weight);//��ʼ����������
	void huffcode();//���뿪ʼ
	string huffdecode(string s);//����������
	string huffencode(string s);//����
};
HuffMan::HuffMan(int number)//���캯��
{
	hufftree = new node[2 * number + 1];
	weight = new int[number];
	this->number = number;
}
HuffMan::~HuffMan()//��������
{
	delete[] hufftree;//�����̬�������Դ
	delete[] weight;
}
void HuffMan::select(int *a, int *b, int number)//��Ȩֵ��С������a��b  
{
	double weight = 0; //����С����
	for (int i = 0; i < number; i++)
	{
		if (hufftree[i].parent != -1)//�жϽڵ��Ƿ��Ѿ�ѡ��
			continue;
		else
		{
			if (weight == 0)
			{
				weight = hufftree[i].weight;
				*a = i;
			}
			else
			{
				if (hufftree[i].weight < weight)
				{
					weight = hufftree[i].weight;
					*a = i;
				}
			}
		}
	}
	weight = 0; //�ҵڶ�С����
	for (int i = 0; i < number; i++)
	{
		if (hufftree[i].parent != -1 || (i == *a))//�ų���ѡ������
			continue;
		else
		{
			if (weight == 0)
			{
				weight = hufftree[i].weight;
				*b = i;
			}
			else
			{
				if (hufftree[i].weight < weight)
				{
					weight = hufftree[i].weight;
					*b = i;
				}
			}
		}
	}
	int temp;
	if (hufftree[*a].lchild < hufftree[*b].lchild)  //С���������
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}
void HuffMan::huffTree(vector<char>& str, vector<int>& weight)//��ʼ����������
{
	for (int i = 0; i < 2 * number - 1; i++)//��ʼ����
	{
		hufftree[i].parent = -1;
		hufftree[i].lchild = -1;
		hufftree[i].rchild = -1;
		hufftree[i].code = "";
	}
	for (int i = 0; i < number; i++)
	{
		hufftree[i].weight = weight[i];
		hufftree[i].ch = str[i];
	}
	for (int k = number; k < 2 * number - 1; k++)
	{
		int temp1 = 0;
		int temp2 = 0;
		select(&temp1, &temp2, k); //��temp1��temp2�ڵ�ϳɽڵ�k
		hufftree[temp1].parent = k;
		hufftree[temp2].parent = k;
		hufftree[k].weight = hufftree[temp1].weight + hufftree[temp2].weight;
		hufftree[k].lchild = temp1;
		hufftree[k].rchild = temp2;
	}
}
void HuffMan::huffcode()//���뿪ʼ
{
	int j, k;
	string s = "";
	for (int i = 0; i < number; i++) 
	{
		s = "";
		j = i;
		while (hufftree[j].parent != -1)//��Ҷ�������ҵ����ڵ�
		{ 
			k = hufftree[j].parent;
			if (j == hufftree[k].lchild) //����Ǹ������ӣ����Ϊ0
				s = s + "0";
			else
				s = s + "1";
			j = hufftree[j].parent;
		}
		cout << "�ַ� " << hufftree[i].ch << " �ı��룺";
		for (int l = s.size() - 1; l >= 0; l--) 
		{
			cout << s[l];
			hufftree[i].code += s[l]; //�������
		}
		cout << endl;
	}
}
string HuffMan::huffdecode(string s)//����������
{
	char temp;
	string str = "";//����������ַ���
	for (unsigned i = 0; i < s.size(); i++)
	{
		temp = s[i];
		for (int j = 0; j < number; j++)
		{
			if (temp == hufftree[j].ch) 
			{
				str = str + hufftree[j].code;
				break;
			}
		}
	}
	return str;
}
string HuffMan::huffencode(string s)//����
{
	string temp = "", str = "";//����������ַ���
	for (unsigned i = 0; i < s.size(); i++) 
	{
		temp = temp + s[i];
		for (int j = 0; j < number; j++) 
		{
			if (temp == hufftree[j].code)
			{
				str = str + hufftree[j].ch;
				temp = "";
				break;
			}
			if (i == s.size() - 1 && j == number - 1 && temp != "") //ȫ��������û��
				str = "�������";
		}
	}
	return str;
}
void start()//�ļ�����͹��ܵ��ú���
{
	//������Ҫʹ�õ��ļ�
	char haffbasedatafile[MAX_PATH] = "������������������ļ�.txt";
	char haffcodefilein[MAX_PATH] = "������������Ҫ���������.txt";
	char haffcodefileout[MAX_PATH] = "�������������������.txt";

	if (freopen(haffbasedatafile, "r", stdin) == NULL)
	{
		cout << "���ļ�ʧ�ܣ���Ŀ¼��δ�ҵ�" << haffbasedatafile << endl;
		system("pause");
		exit(0);
	}
	//�������
	int number, i;
	cin >> number;//�����ض����ļ����Ĵ��ڣ�������ļ�ֱ��д����Ҫ�����������
	vector<char> ch;//�����ַ�����
	vector<int> weightvector;//����Ȩֵ����
	for (i = 0; i < number; i++) 
	{
		char c;
		int weight;
		cin >> c >> weight;//���ļ���ֱ�ӻ�ȡ
		ch.push_back(c);//�ַ�д������
		weightvector.push_back(weight);//Ȩֵд������
	}
	cout << "��Ĭ���ļ��ж����Ļ����������£�" << endl;
	for (i = 0; i < number; i++)//��ʾ�ַ�
		cout << ch[i] << " ";
	cout << endl;
	for (i = 0; i < number; i++)//��ʾȨֵ
		cout << weightvector[i] << " ";
	cout << endl << endl;
	// ��ʼ����
	HuffMan hf(number);//����������������
	hf.huffTree(ch, weightvector);//����
	cout << "�����ַ�����Ϊ��" << endl;
	hf.huffcode();
	cout << endl;

	// ��ʼ�ļ�������Ҫ������ַ���
	ifstream haffcodein(haffcodefilein);
	string str, sourcestr, decodedstr;//�����ַ��� �������ǰ������ַ���
	if (!getline(haffcodein, str))
	{
		cout << "���ļ�ʧ�ܣ���Ŀ¼��δ�ҵ�"<< haffcodefilein << endl;
		system("pause");
		exit(0);
	}
	cout << "���ı��ļ��ж�����ַ���Ϊ��" << str << endl;
	sourcestr = str;//������ַ�������������ԭ�ַ�����,�Ա�����Ա�
	haffcodein.close();

	// ��ʼ�����ַ�����Ȼ������ļ�
	ofstream haffcodeout(haffcodefileout);
	str = hf.huffdecode(str);
	cout << "������б��롣������Ϊ��" << str << endl;
	haffcodeout << str;
	cout << "������Ѿ������ļ�������" << endl << endl;
	haffcodeout.close();

	// ��ʼ���ļ��ж�������Ʊ�����н���
	haffcodein.open("�������������������.txt");
	getline(haffcodein, str);
	cout << "������ļ��ж�������Ʊ�����н��롣" << endl;
	cout << "����Ϊ:" << str << endl;
	decodedstr = hf.huffencode(str);
	cout << "�����Ϊ��" << decodedstr << endl;
	if (decodedstr == sourcestr)//���ǰ���ַ���һ��
		cout << "������ϣ���ԭ������ȫһ�£�����" << endl << endl;
	else
		cout << "������ϣ���ԭ���ݲ�һ�£�����" << endl << endl;

}
void main()//�������
{
	system("color f0");//�豸������ɫ
	system("title ���������빦��չʾ"); //���ñ���
	start();
	system("pause");
	return;
}//����
