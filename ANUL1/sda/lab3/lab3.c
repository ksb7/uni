#include <stdio.h>
#include <math.h>
/* Să se calculeze pentru limitele indicate de integrare [a,b]: */

float integral(float A, float B, int n)
{
	if(n > 1) return ((B*pow(log(B), n) - n*integral(A, B, n-1)) - (A*pow(log(A), n) - n*integral(A, B, n-1)));
	else if(n = 1)
	return ((B*log(B) - B) - (A*log(A) - A)); 	
}
int main()
{
	float A, B; //limitele
	int n; //puterea
	printf("Dati limitele integrarii:\n");
	scanf("%f%f", &A, &B);
	printf("Dati puterea\n");
	scanf("%d", &n);
	printf("Rezultatul integrarii este: %f\n", integral(A, B, n));
	return 0;
}
