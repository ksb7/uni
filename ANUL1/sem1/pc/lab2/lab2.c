#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 //varianta 7
 
int main()
{
	int choice;
	float d, g, V;
	printf("MENIU:\n1. Instructiunea if\n2. Instructiunea if-else\n3. Instructiunea if-else-if\n");
	printf("Alegeti optiunea:\n");
	scanf("%d", &choice);
	printf("Introduceti necunoscutele d si g: ");
	scanf("%f%f", &d, &g);
	switch(choice)
	{
		case 1:
			{
				if(d*2 >= 1 && d*2 <= 9) V = 3.14*pow(d, 3) - sqrt(abs(d - g));
				if(d*2 < 1) V = d*g - exp(-d);
				if(d*2 > 9) V = sin(d*g) + 1;
				break;
			}
		case 2:
			{
				if(d*2 >=1) 
				{
					if(d*2 <=9 ) V = 3.14*pow(d, 3) - sqrt(abs(d - g)); 
					else V = sin(d*g) + 1;
				}
				else V = d*g - exp(-d);
				break;
			}
		case 3:
			{
				if(d*2 >= 1 && d*2 <= 9) V = 3.14*pow(d, 3) - sqrt(abs(d - g)); else
                                if(d*2 < 1) V = d*g - exp(-d); else
                                if(d*2 > 9) V = sin(d*g) + 1;
				break;
			}
		default: printf("Alegere invalida\n"); break;
	}
	printf("V = %f\n", V);
	return 0;
}


