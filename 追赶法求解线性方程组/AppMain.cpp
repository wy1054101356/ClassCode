#include <iostream>
#include <vector>
using namespace std;

int main() {
	freopen("1.txt", "r", stdin);
	int row, col;
	cin >> row >> col;
	vector< vector<double> > mtx(row + 1, vector<double>(col + 1, 0));
	vector<double> b(col + 1, 0);
	vector<double> y(col + 1, 0);
	vector<double> x(col + 1, 0);
	// 读取数据
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col + 1; j++) {
			double num;
			cin >> num;
			if (j == col + 1)
				b[i] = num;
			else
				mtx[i][j] = num;
			if (i == 1 && (1 < j && j <= col)) {
				mtx[i][j] /= mtx[1][1];
			}
		}
	}
	// 分解
	for (int i = 2; i <= col; i++) {
		// 算列
		for (int j = i; j <= row; j++) {
			double count = 0;
			for (int m = i - 1; m >= 1; m--) {
				count += (mtx[j][m] * mtx[m][i]);
			}
			double value = mtx[j][i];
			mtx[j][i] -= count;
		}

		// 算行
		for (int j = i + 1; j <= row; j++) {
			double count = 0;
			for (int m = i - 1; m >= 1; m--) {
				count += (mtx[i][m] * mtx[m][j]);
			}
			mtx[i][j] -= count;
			mtx[i][j] /= mtx[i][i];
		}
	}

	//L
	cout << "L矩阵" << endl;;
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= i; j++) {
			if (mtx[i][j] == 0.0f)
				cout << "          ";
			else
				printf("%10.6lf", mtx[i][j]);
		}
		cout << endl;
	}
	cout << endl << endl;

	//U
	cout << "U矩阵" << endl;
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			if (j > i) {
				if (mtx[i][j] == 0.0f)
					cout << "          ";
				else
					printf("%10.6lf", mtx[i][j]);
			}
			else if (j == i)
				printf("%10.6lf", 1.0);
			else
				cout << "          ";
		}
		cout << endl;
	}
	cout << endl << endl;

	// Ly = f, 计算y
	y[1] = b[1] / mtx[1][1];
	for (int i = 2; i <= row; i++) {
		y[i] = (b[i] - mtx[i][i - 1] * y[i - 1]) / mtx[i][i];
	}
	cout << "通过Ly=b求解y:" << endl << "[ " << y[1];
	for (int i = 2; i < y.size(); i++)
		printf(", %10.6lf", y[i]);
	cout << "]" << endl << endl;


	// Ux = y, 计算x
	x[row] = y[row];
	for (int i = row - 1; i >= 1; i--) {
		x[i] = y[i] - mtx[i][i + 1] * x[i + 1];
	}
	cout << "通过Ux=y求解x:" << endl << "[ " << x[1];
	for (int i = 2; i < x.size(); i++)
		printf(", %10.6lf", x[i]);
	cout << "]" << endl << endl;

	//输出结果
	cout << "Result:" << endl;
	for (int i = 1; i <= row; i++)
		cout << "X" << i << " = " << x[i] << endl;
	return 0;
}
