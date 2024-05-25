#include <stdio.h>

int main()
{
	int n;
	float A[255];
	printf("dati # de elemente:\n");
	scanf("%d", &n);
	printf("dati elementele tabloului:\n");
	for(int i = 0; i < n; i++)
		scanf("%f", &A[i]);
	float minimal = A[0], produs = 1;
        int indice;
	for(int i = 0; i < n; i++)
	{
		if(A[i] < minimal) minimal = A[i];
		if(A[i] > 0) produs *= A[i];
	}
	printf("pozitiile cu cea mai mica valoare a tabloului sunt:");
	for(int i = 0; i < n; i++)
		if(A[i] == minimal) printf(" %d", i+1);
	printf("\nprodusul elementelor pozitive din tablou este: %f\n", produs);
	return 0;
}

