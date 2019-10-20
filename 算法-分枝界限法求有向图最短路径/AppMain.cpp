//#include"stdlib.h"
//#include <iostream>
//using namespace std;
//
//#define N 7 //邻接矩阵
//#define M 2	//长度
////各个城市之间的路径长度
////int CityVal[N][N] = {
////
////{ 00,30,06,04 },
////{ 30,00,05,10 },
////{ 06,05,00,20 },
////{ 04,10,20,00 }
////
////};
//
//int CityVal[N][N] = {
//
//{00, 02,  8, 05, 99, 99, 99},
//{99, 00, 03, 99, 03, 99, 99},
//{99, 99, 00, 99, 99, 04, 99},
//{99, 99, 99, 00, 99, 06, 01},
//{99, 99, 99, 99, 00, 05, 07},
//{99, 99, 99, 99, 99, 00, 02},
//{99, 99, 99, 99, 99, 99, 00}
//
//};
//
//
//struct CityNum
//{
//	int MinVal[2];      //最短路径长度
//	int PastCity[2][N]; //走过的路径
//}city[4];
//
//int find(int j, int k, int boolnum)
//{
//	int i;
//	for (i = 0; i < 4; i++)
//		if (j == city[k].PastCity[boolnum][i])
//			return 1;
//	return 0;
//}
//void copy(int k, int boolnum1, int j, int boolnum2)
//{
//	int i = 0;
//	while (city[k].PastCity[boolnum1][i] != 0 && city[k].PastCity[boolnum1][i] != 99) {
//		city[j].PastCity[boolnum2][i] = city[k].PastCity[boolnum1][i];
//		i++;
//	}
//	city[j].PastCity[boolnum2][i] = k;
//}
//
//
//
//int main()
//{
//	int i, j, k;
//	int boolnum = 0;
//	int TempMinVal;
//	int TempCity;
//	int TempVal;
//	for (i = 0; i < M; i++)
//		for (j = 0; j < N; j++)
//			for (k = 0; k < N; k++)
//				city[k].PastCity[i][j] = 0;
//	for (i = 1; i < 4; i++)
//		city[i].MinVal[boolnum] = CityVal[i][0];
//	for (i = 0; i < 2; i++)
//	{
//		for (j = 1; j < 4; j++)
//		{
//			TempMinVal = 99;
//			for (k = 1; k < 4; k++)
//			{
//				if (j != k && !find(j, k, boolnum))
//				{
//					TempVal = CityVal[j][k] + city[k].MinVal[boolnum];
//					if (TempMinVal > TempVal)
//					{
//						TempMinVal = TempVal;
//						TempCity = k;
//					}
//				}
//			}
//			city[j].MinVal[(boolnum + 1) % 2] = TempMinVal;
//			copy(TempCity, boolnum, j, (boolnum + 1) % 2);
//		}
//		boolnum = (boolnum + 1) % 2;
//	}
//
//	for (i = 1; i < 4; i++)
//	{
//		TempVal = CityVal[0][i] + city[i].MinVal[boolnum];
//		if (TempMinVal > TempVal)
//		{
//			TempMinVal = TempVal;
//			TempCity = i;
//		}
//	}
//	cout << "最短路径长度:" << TempMinVal << endl;
//	cout << "从出发点到终点的路径：:";
//	cout << 1 << ' ';
//	cout << TempCity + 1 << ' ';
//	for (i = 1; i >= 0; i--)
//		cout << city[TempCity].PastCity[boolnum][i] + 1 << ' ';
//	cout << 1 << endl;
//}