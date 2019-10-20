#include <iostream>  
#include <string>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <fstream>
using namespace std;

struct Node
{
	double weight;
	char ch;
	string code;
	int lchild, rchild, parent;
};

class HuffMan {
private:
	Node * huffTree; // ��
	int n;  // �ַ���
	int* w; // Ȩֵ
public:
	HuffMan(int n) {
		huffTree = new Node[2 * n + 1];
		w = new int[n];
		this->n = n;
	}
	~HuffMan() {
		delete[] huffTree;
		delete[] w;
	}
	void select(int *a, int *b, int n)//��Ȩֵ��С������a��b  
	{
		int i;
		double weight = 0; //����С����
		for (i = 0; i < n; i++)
		{
			if (huffTree[i].parent != -1)     //�жϽڵ��Ƿ��Ѿ�ѡ��
				continue;
			else
			{
				if (weight == 0)
				{
					weight = huffTree[i].weight;
					*a = i;
				}
				else
				{
					if (huffTree[i].weight < weight)
					{
						weight = huffTree[i].weight;
						*a = i;
					}
				}
			}
		}
		weight = 0; //�ҵڶ�С����
		for (i = 0; i < n; i++)
		{
			if (huffTree[i].parent != -1 || (i == *a))//�ų���ѡ������
				continue;
			else
			{
				if (weight == 0)
				{
					weight = huffTree[i].weight;
					*b = i;
				}
				else
				{
					if (huffTree[i].weight < weight)
					{
						weight = huffTree[i].weight;
						*b = i;
					}
				}
			}
		}
		int temp;
		if (huffTree[*a].lchild < huffTree[*b].lchild)  //С���������
		{
			temp = *a;
			*a = *b;
			*b = temp;
		}
	}
	void Huff_Tree(vector<char>& str, vector<int>& w)
	{
		int i;
		for (i = 0; i < 2 * n - 1; i++) {//��ʼ����
			huffTree[i].parent = -1;
			huffTree[i].lchild = -1;
			huffTree[i].rchild = -1;
			huffTree[i].code = "";
		}
		for (i = 0; i < n; i++) {
			huffTree[i].weight = w[i];
			huffTree[i].ch = str[i];
		}
		for (int k = n; k < 2 * n - 1; k++) {
			int i1 = 0;
			int i2 = 0;
			select(&i1, &i2, k); //��i1��i2�ڵ�ϳɽڵ�k
			huffTree[i1].parent = k;
			huffTree[i2].parent = k;
			huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
			huffTree[k].lchild = i1;
			huffTree[k].rchild = i2;
		}
	}
	void Huff_Code()
	{
		int i, j, k;
		string s = "";
		for (i = 0; i < n; i++) {
			s = "";
			j = i;
			while (huffTree[j].parent != -1) { //��Ҷ�������ҵ����ڵ�
				k = huffTree[j].parent;
				if (j == huffTree[k].lchild) //����Ǹ������ӣ����Ϊ0
					s = s + "0";
				else
					s = s + "1";
				j = huffTree[j].parent;
			}
			cout << "�ַ� " << huffTree[i].ch << " �ı��룺";
			for (int l = s.size() - 1; l >= 0; l--) {
				cout << s[l];
				huffTree[i].code += s[l]; //�������
			}
			cout << endl;
		}
	}
	string Huff_Decode(string s) {
		char temp;
		string str = "";//����������ַ���
		for (unsigned i = 0; i < s.size(); i++) {
			temp = s[i];
			for (int j = 0; j < n; j++) {
				if (temp == huffTree[j].ch) {
					str = str + huffTree[j].code;
					break;
				}
			}
		}
		return str;
	}
	string Huff_Encode(string s) {
		string temp = "", str = "";//����������ַ���
		for (unsigned i = 0; i < s.size(); i++) {
			temp = temp + s[i];
			for (int j = 0; j < n; j++) {
				if (temp == huffTree[j].code) {
					str = str + huffTree[j].ch;
					temp = "";
					break;
				}
				else if (i == s.size() - 1 && j == n - 1 && temp != "") {//ȫ��������û��
					str = "�������";
				}
			}
		}
		return str;
	}
};


void start()
{
	// �ض������ı��ļ�,�����޸Ķ�ȡ�ļ�
	freopen("������������������ļ�.txt", "r", stdin);
	//�������
	int n,i;
	cin >> n;
	vector<char> s;
	vector<int> w;
	for (i = 0; i < n; i++) {
		char c;
		int weight;
		cin >> c >> weight;
		s.push_back(c);
		w.push_back(weight);
	}
	cout << "��Ĭ���ļ��ж����Ļ����������£�" << endl;
	for ( i = 0; i < n; i++)
		cout << s[i] << " ";
	cout << endl;
	for ( i = 0; i < n; i++)
		cout << w[i] << " ";
	cout << endl << endl;

	// ��ʼ����
	HuffMan hf(n);
	hf.Huff_Tree(s, w);
	cout << "�����ַ�����Ϊ��" << endl;
	hf.Huff_Code();
	cout << endl;

	// ��ʼ�ļ�������Ҫ������ַ���
	ifstream in("������������Ҫ���������.txt");
	string str;
	getline(in, str);
	cout << "���ı��ļ��ж�����ַ���Ϊ��" << str << endl;
	in.close();

	// ��ʼ�����ַ�����Ȼ������ļ�
	ofstream out("�������������������.txt");
	str = hf.Huff_Decode(str);
	cout << "������б��롣������Ϊ��" << str << endl;
	out << str;
	cout << "������Ѿ������ļ�������" << endl << endl;
	out.close();

	// ��ʼ���ļ��ж�������Ʊ�����н���
	in.open("�������������������.txt");
	getline(in, str);
	cout << "������ļ��ж�������Ʊ�����н��롣" << endl;
	cout << "����Ϊ:" << str << endl;
	str = hf.Huff_Encode(str);
	cout << "�����Ϊ��" << str << endl;
	cout << "������ϣ���ԭ������ȫһ�£�����" << endl << endl;

}

int main()
{
	system("color f0");
	SetConsoleTitle("���������빦��չʾ"); //���ñ���
	start();
	system("pause");
	exit(1);
	return 0;
}
//����