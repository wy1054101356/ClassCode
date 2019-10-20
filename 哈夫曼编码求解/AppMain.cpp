#include <iostream>  
#include <string>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <fstream>
using namespace std;

struct node
{
	double weight;//权值
	char ch;//字符
	string code;//字符编码
	int lchild, rchild, parent;//左右子节点 父亲节点
};
class HuffMan 
{
private:
	node * hufftree;//树
	int number;//字符数
	int* weight;//权值
public:
	HuffMan(int number);//构造函数
	~HuffMan();//析构函数
	void select(int *a, int *b, int number);//找权值最小的两个a和b  
	void huffTree(vector<char>& str, vector<int>& weight);//初始化哈夫曼树
	void huffcode();//编码开始
	string huffdecode(string s);//哈夫曼译码
	string huffencode(string s);//解码
};
HuffMan::HuffMan(int number)//构造函数
{
	hufftree = new node[2 * number + 1];
	weight = new int[number];
	this->number = number;
}
HuffMan::~HuffMan()//析构函数
{
	delete[] hufftree;//清除动态申请的资源
	delete[] weight;
}
void HuffMan::select(int *a, int *b, int number)//找权值最小的两个a和b  
{
	double weight = 0; //找最小的数
	for (int i = 0; i < number; i++)
	{
		if (hufftree[i].parent != -1)//判断节点是否已经选过
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
	weight = 0; //找第二小的数
	for (int i = 0; i < number; i++)
	{
		if (hufftree[i].parent != -1 || (i == *a))//排除已选过的数
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
	if (hufftree[*a].lchild < hufftree[*b].lchild)  //小的数放左边
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}
void HuffMan::huffTree(vector<char>& str, vector<int>& weight)//初始化哈夫曼树
{
	for (int i = 0; i < 2 * number - 1; i++)//初始过程
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
		select(&temp1, &temp2, k); //将temp1，temp2节点合成节点k
		hufftree[temp1].parent = k;
		hufftree[temp2].parent = k;
		hufftree[k].weight = hufftree[temp1].weight + hufftree[temp2].weight;
		hufftree[k].lchild = temp1;
		hufftree[k].rchild = temp2;
	}
}
void HuffMan::huffcode()//编码开始
{
	int j, k;
	string s = "";
	for (int i = 0; i < number; i++) 
	{
		s = "";
		j = i;
		while (hufftree[j].parent != -1)//从叶子往上找到根节点
		{ 
			k = hufftree[j].parent;
			if (j == hufftree[k].lchild) //如果是根的左孩子，则记为0
				s = s + "0";
			else
				s = s + "1";
			j = hufftree[j].parent;
		}
		cout << "字符 " << hufftree[i].ch << " 的编码：";
		for (int l = s.size() - 1; l >= 0; l--) 
		{
			cout << s[l];
			hufftree[i].code += s[l]; //保存编码
		}
		cout << endl;
	}
}
string HuffMan::huffdecode(string s)//哈夫曼译码
{
	char temp;
	string str = "";//保存解码后的字符串
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
string HuffMan::huffencode(string s)//解码
{
	string temp = "", str = "";//保存解码后的字符串
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
			if (i == s.size() - 1 && j == number - 1 && temp != "") //全部遍历后没有
				str = "解码错误！";
		}
	}
	return str;
}
void start()//文件处理和功能调用函数
{
	//定义需要使用的文件
	char haffbasedatafile[MAX_PATH] = "哈夫曼代码基础数据文件.txt";
	char haffcodefilein[MAX_PATH] = "哈夫曼代码需要编码的数据.txt";
	char haffcodefileout[MAX_PATH] = "哈夫曼代码产生的数据.txt";

	if (freopen(haffbasedatafile, "r", stdin) == NULL)
	{
		cout << "打开文件失败，根目录中未找到" << haffbasedatafile << endl;
		system("pause");
		exit(0);
	}
	//编码过程
	int number, i;
	cin >> number;//由于重定向文件流的存在，读入的文件直接写入需要输入的数据中
	vector<char> ch;//定义字符容器
	vector<int> weightvector;//定义权值容器
	for (i = 0; i < number; i++) 
	{
		char c;
		int weight;
		cin >> c >> weight;//在文件中直接获取
		ch.push_back(c);//字符写入容器
		weightvector.push_back(weight);//权值写入容器
	}
	cout << "从默认文件中读出的基础数据如下：" << endl;
	for (i = 0; i < number; i++)//显示字符
		cout << ch[i] << " ";
	cout << endl;
	for (i = 0; i < number; i++)//显示权值
		cout << weightvector[i] << " ";
	cout << endl << endl;
	// 开始编码
	HuffMan hf(number);//创建哈夫曼树对象
	hf.huffTree(ch, weightvector);//建立
	cout << "各个字符编码为：" << endl;
	hf.huffcode();
	cout << endl;

	// 开始文件读入需要编码的字符串
	ifstream haffcodein(haffcodefilein);
	string str, sourcestr, decodedstr;//处理字符串 译码解码前，后的字符串
	if (!getline(haffcodein, str))
	{
		cout << "打开文件失败，根目录中未找到"<< haffcodefilein << endl;
		system("pause");
		exit(0);
	}
	cout << "从文本文件中读入的字符串为：" << str << endl;
	sourcestr = str;//读入的字符串存入待保存的原字符串中,以便后续对比
	haffcodein.close();

	// 开始编码字符串，然后存入文件
	ofstream haffcodeout(haffcodefileout);
	str = hf.huffdecode(str);
	cout << "下面进行编码。编码结果为：" << str << endl;
	haffcodeout << str;
	cout << "本结果已经存入文件！！！" << endl << endl;
	haffcodeout.close();

	// 开始从文件中读入二进制编码进行解码
	haffcodein.open("哈夫曼代码产生的数据.txt");
	getline(haffcodein, str);
	cout << "下面从文件中读入二进制编码进行解码。" << endl;
	cout << "数据为:" << str << endl;
	decodedstr = hf.huffencode(str);
	cout << "解码后为：" << decodedstr << endl;
	if (decodedstr == sourcestr)//如果前后字符串一致
		cout << "解码完毕，和原数据完全一致！！！" << endl << endl;
	else
		cout << "解码完毕，和原数据不一致！！！" << endl << endl;

}
void main()//程序入口
{
	system("color f0");//设备背景颜色
	system("title 哈夫曼编码功能展示"); //设置标题
	start();
	system("pause");
	return;
}//结束
