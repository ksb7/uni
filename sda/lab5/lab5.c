#include <stdio.h>
#include <stdlib.h>
int a[100], b[100];
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void shakerSort(int *comp, int *perm, int n)
{
	for(int i = 0; i < n; i++)
		for(int j=i+1; i < n-1; j++)
		{
			if(a[j] < a[j-1])
			{
				swap(&a[j], &a[j-1]);
				(*perm)++;
				(*comp)++;
			}	
			n--;
			for(int k = n-1; k > i; k--)
				if(a[k] < a[k-1]) 
			{
				swap(&a[k], &a[k-1]);
				(*perm)++;
				(*comp)++;
			}
		}
}
int selectionSort(int *perm, int *comp, int n)
{
	int i = 0, j;
	while (i < n)
	{
		int k = i;
		for(j = k; j < n; j++)
			if(b[j] < b[k]) 
			{
				k = j;
				(*comp)++;
			}
		swap(&b[i], &b[k]);
		(*perm)++;
		i++;
	}
}
int main()
{
	int permS = 0, compS = 0; //permutari si comparatii pentru shaker sort
	int n;
	printf("Dati numarul de elemente:\n");
	scanf("%d", &n);
	printf("Dati elementele tabloului:\n");
	for(int i = 0; i < n; i++) 
	{
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	shakerSort(&compS, &permS, n);
	printf("Elementele dupa Shaker Sort\n");
	for(int i = 0; i < n; i++)
		printf("%d ", a[i]);
	int permSS = 0, compSS = 0;
	selectionSort(&permSS, &compSS, n);	
	printf("\nElementele dupa Selection Sort\n");
	for(int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
	if(permS < permSS) printf("Algoritmul Shaker Sort este mai eficient in termeni de permutari\n"); else 
		if(permS > permSS) printf("Algoritmul Selection Sort este mai eficient in termeni de permutari\n"); else
			if(permS == permSS) printf("Algoritmele sunt egal eficiente in termeni de permutari\n");
	if(compS < permSS) printf("Algoritmul Shaker Sort este mai eficient in termeni de comparatii\n"); else
		if(compS > permSS) printf("Algoritmul Selection Sort este mai eficient in termeni de comparatii\n"); else
			if(compS == compSS) printf("Algoritmele sunt egal eficiente in termeni de comparatii\n");
	return 0;
}



