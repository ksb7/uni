#include <stdio.h>
#include <string.h>
void swapStr(char *a, char *b)
{
	char temp[100];
	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
}
int main()
{
	char cuvinte[10][100];
	printf("Dati 10 cuvinte:\n");
	for(int i = 0; i < 10; i++)
	{
		scanf("%s", cuvinte[i]);
	}
	for(int i = 0; i < 10; i++)
	{
		int k = i;
		for(int j = k; j < 10; j++)
		{
			if(strcmp(cuvinte[j], cuvinte[k]) < 0) k = j;
		}
		swapStr(cuvinte[i], cuvinte[k]);
	}
	printf("Cuvintele in ordine alfabetica sunt: \n");
	for(int i = 0; i < 10; i++)
	{
		printf("%s\n", cuvinte[i]);
	}
	return 0;
}
