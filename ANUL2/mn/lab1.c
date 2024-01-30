#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EROAREA 		0.1
#define EXACTITATEA 	0.00001
#define APROXIMARI 		100

double f(double);
double fl(double);
double g(double);
double f1(double);
double g1(double);
double f2(double);
double g2(double x);
void input(float *a, float *b);
void metodaAproximatiilorSuccesive(float a, float b, double (*funct)(double));
void metodaNewton(float a, float b, double (*funct)(double), double (*funct1)(double));
void metodaSecantelor(float a, float b, double (*funct)(double));

int main()
{
	int choice;
	float a, b;
	do{
		printf("Meniu: 1. Metoda aproximatiilor succesive\n2. Metoda tangentelor(Newton)\n3. Metoda secantelor\n0. Iesire din program\n");
		scanf("%d", &choice);
		switch(choice){
		case 0:
		{
			exit(0);
		}
		case 1:
		{
			input(&a, &b);
			printf("Cazul a:\n");
			metodaAproximatiilorSuccesive(a, b, &f);
			printf("Cazul b:\n");
			metodaAproximatiilorSuccesive(a, b, &g);
			break;
		}
		case 2:
		{
			input(&a, &b);
			printf("Cazul a:\n");
			metodaNewton(a, b, &f, &f1);
			printf("Cazul b:\n");
			metodaNewton(a, b, &g, &g1);
			break;
		}
		case 3:
		{
			input(&a, &b);
			printf("Cazul a:\n");
			metodaSecantelor(a, b, &f);
			printf("Cazul b:\n");
			metodaSecantelor(a, b, &g);
			break;
		}
		default:
		{
			printf("Alegere invalida. Incercati din nou\n");
			break;
		}
		}

	} while(choice != 0);
	return 0;
}

double f(double x)
{
	return pow(x+1, 3)+log(x);
}

double g(double x)
{
	return pow(x,3)+23*x+1;
}

double f1(double x)
{
	return 3*pow(x+1, 2)+1/x;
}

double g1(double x)
{
	return 3*pow(x,2)+23;
}

double f2(double x)
{
	return -1/pow(x,2)+6*x+6;
}

double g2(double x)
{
	return 6*x;
}

void input(float *a, float *b)
{
	printf("Introduceti intervalul [a, b]\n");
	scanf("%f%f", a, b);
}

void metodaAproximatiilorSuccesive(float a, float b, double (*funct)(double x))
{
	float x; 
	for(int i = 0; i < APROXIMARI; i++)
	{
		x = (a+b)/2;

		if ((*funct)(x) == 0) 
		{
			break; 
		}
		else
		{
			if ((*funct)(a) * (*funct)(x) > 0) 
			{
				a = x; 
			} 
			else 
			{
				b = x;
			}
		}
	}

	printf("Solutia ecuatiei este x = %f\n", x);
}

void metodaNewton(float a, float b, double (*funct)(double x), double (*funct1)(double))
{
	float c, x;
	int k = 0; 
	c = a - ((*funct)(a) * (b-a))/((*funct)(b) - (*funct)(a));

	if((*funct)(c) * (*funct)(a) < 0) 
	{
		x = a; 
	}
	else
	{ 
		x = b;
	}

	for(int i = 0; i < APROXIMARI; i++)
	{
		x = x - (*funct)(x) / (*funct1)(x);
		k++;
	}

	printf("Solutia ecuatiei este x = %f\n", x);
}

void metodaSecantelor(float a, float b, double (*funct)(double))
{
	float c, e, x;
	int k = 0;
	c = a - ((*funct)(a) * (b-a)) / ((*funct)(b) - (*funct)(a));

	if((*funct)(c) * (*funct)(a) < 0) 
	{
		e = a;
		x = b;
	} 
	else 
	{
		e = b;
		x = a;
	}

	for(int i = 0; i < APROXIMARI; i++)
	{
		x = x - ((*funct)(x) * (e - x)) / ((*funct)(e) - (*funct)(x));
		k++;
	}

	printf("Solutia ecuatiei este x = %f\n", x);
}