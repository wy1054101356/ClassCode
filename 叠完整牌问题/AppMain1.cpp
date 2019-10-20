
#include<iostream>
#include<iomanip>
#include<conio.h>
#include<vector>
using namespace std;

vector<int> pokers;							//这里尝试使用容器

void showPokers()							//显示扑克牌每摞情况
{
	cout << "====================================" << endl;
	cout << "摞数:";
	for (int i = 0; i < pokers.size(); i++)
		cout << setw(3) << i + 1;
	cout << endl;

	cout << "张数:";
	for (int i = 0; i < pokers.size(); i++)
		cout << setw(3) << pokers[i];
	cout << endl;
	cout << "====================================" << endl;
	return;
}

void main()
{
	int total;								//扑克牌总张数
	int temp;								//扑克牌每摞张数
	int pokersAverage;						//计算平均数
	int times;								//交换次数
	int max;								//排序
	do {									//循环输入扑克牌数据，直到正确数据为止
		total = 0;							//初始化所有资源
		pokers.clear();

		cout << "请输入每摞扑克牌张数，以回车结束：" << endl;
		while (1) {
			cin >> temp;
			pokers.push_back(temp);			//向容器写入当前输入的数据
			total += temp;					//计算总和
			if (getchar() == '\n')			//遇到回车跳出循环
				break;
		}
		if (total % pokers.size() != 0)		//判断
			cout << "输入扑克牌张数有误!" << endl;
	} while (total % pokers.size() != 0);
	showPokers();							//显示数据

	pokersAverage = total / pokers.size();	//计算平均数
	times = 0;		
	
	for (int j = 0; j < pokers.size(); j++){//从大到小排列
		for (int i = 0; i < pokers.size() - 1 - j; i++){
			if (pokers[i] < pokers[i + 1]){
				max = pokers[i];
				pokers[i] = pokers[i + 1];
				pokers[i + 1] = max;
			}
		}
	}
	cout << "排序后的扑克牌如下:" << endl;
	showPokers();		//更新数据

	for (int i = 0; i < pokers.size(); i++) {
		if (pokers[i] != pokersAverage) {
			if (pokers[i] > pokersAverage) {
				pokers[i + 1] += pokers[i] - pokersAverage;//移动扑克牌
				cout << "第" << times + 1 << "次:第 " << i + 1 << " 摞牌向 " << i + 2 << " 摞"
					<< "移动了 " << pokers[i] - pokersAverage << " 张牌" << endl;//显示步骤
				pokers[i] = pokersAverage;
			}
			times++;		//次数计数
			showPokers();	//更新数据
		}
	}
	cout << "最优移动次数:" << times << endl;
	return;
}
