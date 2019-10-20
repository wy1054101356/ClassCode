#include <iostream>
#include <math.h>
#include <iomanip>
#define pi 3.1415926
using namespace std;

float f(float x, float y) {
	return ( (-y) + 2 * cos(x) );
}
void Ola(float x0, float xn, float y0, float h)
{
	int count = 1;
	float x = x0, y = y0;
	int n = (int)fabs(xn - x0) / h;
	cout << " X" << setw(2) << count - 1 << " = " << setw(4) << x
		 << "   Y" << setw(2) << count - 1 << " = " << setw(8) << y << endl;
	do
	{
		y = y + h * f(x, y);
		cout << " X" << setw(2) << count << " = " << setw(4) << x
			 << "   Y" << setw(2) << count << " = " << setw(8) << y << endl;
		x = x + h;
		count++;
	} while (x < xn);
}

void main(){
	Ola(0, pi / 2, 1, 0.1); //直接将基本数据带入
	return;
}

