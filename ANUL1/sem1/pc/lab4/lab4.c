#include <stdio.h>
//varianta 2 
int main()
{
	int A[255][255];
	int n, m;
	int suma = 0;
	float media;
	printf("dati # de randuri si coloane:\n");
	scanf("%d%d", &n, &m);
	printf("dati elementele tabloului:\n");
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) scanf("%d", &A[i][j]);
	int minimal;
	int maximal = minimal = A[0][0];
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
		{
			if(A[i][j] < 0) suma += A[i][j];
			if(A[i][j] < minimal) minimal = A[i][j]; else
				if(A[i][j] > maximal) maximal = A[i][j];
		}
	media = (maximal + minimal) / 2;
	printf("suma elementelor negative ale tabloului este: %d\n", suma);
	printf("media elementului maximal si cel minimal este: %.2f\n", media);
	return 0;
}

