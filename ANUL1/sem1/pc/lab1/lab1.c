#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//varianta 8
 
int main()
{
	float W, Y;
	int a, b, x, y;
	printf("dati variabilele a, b, x, y\n");
	scanf("%d%d%d%d", &a, &b, &x, &y);

	W = ((a+b) / sqrt((pow(a, 2)+13) / (13+pow(b, 2)))) - x - y;
	Y = (pow(x, 2-cos(y) * sqrt(pow(a, 2) + pow(y, 2)))) / (sin(pow(x, 2) - pow(cos(y), 2)));

	printf("W = %f Y = %f\n", W, Y);
	return 0;
}
