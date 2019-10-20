#include <iostream>
#include <math.h>
#include <iomanip>
#define pi 3.141592
using namespace std;

float f(float x, float y) {
	return ((-y) + 2 * cos(x));
}
void Ola(float x0, float xn, float y0, float h)
{
	int count = 1;
	float yc, yp;
	float x = x0, y = y0;
	int n = (int)fabs(xn - x0) / h;
	cout << " X" << setw(2) << count - 1 << " = " << setw(4) << x
		<< "   Y" << setw(2) << count - 1 << " = " << setw(8) << y << endl;
	do
	{
		yp = y + h * f(x, y);
		x = x + h;
		yc = y + h * f(x, yp);
		y = (yp + yc) / 2.0;
		cout << " X" << setw(2) << count << " = " << setw(4) << x
			<< "   Y" << setw(2) << count << " = " << setw(8) << y << endl;
		count++;
	} while (x < xn);
}

void main()
{
	Ola(0, pi / 2, 1, 0.1);
	return;
}

