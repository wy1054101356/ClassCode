#include< stdio.h>
#include< string.h>
#include< math.h>
#include< conio.h>
#include< stdlib.h>

float f(float x)
{
	return(4 / (1 + x * x));
}
float Romberg(float a, float b)
{
	int k = 1;
	float S, x, T1, T2, S1, S2, C1, C2, Rl, R2, h = b - a, precision;
	T1 = h * (f(a) + f(b)) / 2;
	while (1){
		S = 0;
		x = a + h / 2;
		do{
			S += f(x);
			x += h;
		} while (x < b);

		T2 = (T1 + h * S) / 2.0;

		if (fabs(T2 - T1) < precision)
			return(T2);
		S2 = T2 + (T2 - T1) / 3.0;

		if (k == 1) {
			T1 = T2;
			S1 = S2;
			h /= 2;
			k += 1;
			continue;
		}
		C2 = S2 + (S2 - S1) / 15.0;

		if (k == 2) {
			C1 = C2;
			T1 = T2;
			S1 = S2; 
			h /= 2;
			k += 1;
			continue;
		}
		R2 = C2 + (C2 - C1) / 63.0;

		if (k == 3) {
			Rl = R2;
			C1 = C2;
			T1 = T2;
			S1 = S2;
			h /= 2;
			k += 1;
			continue;
		}
		if (fabs(S2 - S1) < (precision))
			return(S2);

		Rl = R2;
		C1 = C2;
		T1 = T2;
		S1 = S2;
		h /= 2;
		k += 1;
		return(Rl);
	}
}
void main()
{
	int i;
	float a, b, precision, S;
	printf("\n Input integrate f(x) the begin : ");
	scanf("%f", &a);
	printf("\n Input integrate f(x) the end : ");
	scanf("%f", &b);
	printf("\n input precision : ");
	scanf("%f", &precision);

	S = Romberg(a, b);
	printf("Theresultis %f", S);
	system("pause");
	return;
}

