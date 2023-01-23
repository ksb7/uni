#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val;
    struct node* head;
};
int **alloc(int m, int n);
void insert_matrix(int **a, int m, int n);
void MI(); //matricea de incidenta
void MA(); //matricea de adiacenta
void LA(); //lista de adiacenta

int main()
{
    int choice;
    int m, n;
    printf("Dati numarul de arce: "); scanf("%d", &n);
    printf("Dati numarul de varfuri: "); scanf("%d", &m);
    printf("Meniu:\n1.Matricea de incidenta\n2.Matricea de adiacenta\n3.Lista de adiacenta(incidenta)\nAlegerea: ");
    scanf("%d", &choice);
    switch(choice)
    {
    case 1: MI(m, n);
        break;
    case 2: MA(m, n);
        break;
    case 3: LA(m, n);
        break;
    default: printf("Alegere invalida\n");
        break;
    }
    return 0;
}
int **alloc(int m, int n)
{
    int **a = malloc(sizeof(int*) * n);

    for(int i = 0; i < n; i++)
    {
        a[i] = malloc(sizeof(int) * m);
    }
    if(a == NULL)
    {
	    printf("Tabloul nu a fost alocat\n");
	    exit(1);
    }
    printf("Memoria s-a alocat cu succes\n");
    return a;
}
void insert_matrix(int **a, int m, int n)
{
    a = alloc(m, n);
    printf("Dati elementele\n");
    for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
    {
        scanf("%d", &a[i][j]);
    }
}
void MI(int m, int n) //matricea de incidenta
{
    int **matrice = NULL;
    insert_matrix(matrice, m, n);
}
void MA(int m, int n) //matricea de adiacenta
{
    int **matrice = NULL;
    insert_matrix(matrice, m, n);

}
void LA(int m, int n ) //lista de adiacenta
{
	int **arrayOflist = NULL;
	*arrayOflist = malloc(sizeof(int)*m);

	printf("1. Transformarea in matricea de incidenta\n2. Transformarea in matricea de adiacenta\nAlegerea");
	int choice;
	scanf("%d", &choice);
	switch(choice)
	{
		case 1: //functia
			break;
		case 2: //functia
			break;
		default: printf("Optiune invalida\n");
			 break;
	}
}
void LAtoMI(int *lista, int m, int n) //lista de adiacenta la matricea de incidenta
{
	int **matrice = alloc(m, n);

}
