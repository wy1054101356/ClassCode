#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
#define pi 3.141592

float f(float x, float y) {
	return  (-y) + 2 * cos(x);
}

float Runge_Kutta(float x, float y, float h) {
	float k1, k2, k3, k4;
	k1 = f(x, y);
	k2 = f(x + h / 2, y + h * k1 / 2);
	k3 = f(x + h / 2, y + h + k2 / 2);
	k4 = f(x + h, y + h - k3);
	return(y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6);
}

void main() {
	int count = 0;//次数
	float x = 0;//x左端点
	float xn = pi / 2;//右端点
	float y = 1;//初始y(0) = 1 
	float h = 0.1;//步长
	cout << " x " << setw(2) << count << "=" << setw(4) << x
		 << " y " << setw(2) << count << "=" << setw(8) << y << endl;
	do {
		y = Runge_Kutta(x, y, h);
		x += h;
		count++;
		cout << " x " << setw(2) << count << "=" << setw(4) << x
			 << " y " << setw(2) << count << "=" << setw(8) << y << endl;
	} while (x < xn);

	return;
}