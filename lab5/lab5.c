#include <stdio.h>
#include <stdlib.h>
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
    return a;
}
void insert(int** a, int m, int n)
{
    printf("dati elementele\n");
    for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
    {
        scanf("%d", &a[i][j]);
        printf("element %d \n", a[i][j]);
    }
}
void rand_insert(int** a, int m, int n)
{
    printf("elementele aleatorii sunt \n");
    for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
    {
        a[i][j] = rand();
        printf("element %d\n", a[i][j]);
    }
}
void bubbleSort(int **a, int m, int n)
{
    printf("Inainte de sortare\n");
    for(int i = 0; i < n; i++)
    {
    for(int j = 0; j < m; j++)
    printf("%d ", a[i][j]);
    printf("\n");
    }
    for(int pas = 0; pas < n - 1; pas++)
    {
        for(int j = 0; j < m; j++)
        for(int i = 0; i < n-pas-1; i++)
        {
            if (a[i][j] > a[i+1][j]) 
            {
                int temp = a[i][j];
                a[i][j] = a[i+1][j];
                a[i+1][j] = temp;
            }
        }
    }
}
void print(int **a, int m, int n)
{
    printf("Dupa sortare\n");
    for(int i = 0; i < n; i++)
    {
    for(int j = 0; j < m; j++)
    printf("%d ", a[i][j]);
    printf("\n");
    }
}
void free_mem(int **a, int m, int n)
{
    for(int i = 0; i < n; i++) free(a[i]);
    free(a);
}
int main()
{
    int m, n;
    int **A;
    printf("nr de coloane si randuri\n");
    scanf("%d%d", &n, &m);
    int choice;
    do{
        printf("Meniu:\n");
        printf(" 1. Alocarea dinamica a memoriei pentru tablourile bidimensionale\n2. Introducerea elementelor tabloului de la tastatura\n3. Completarea tabloului cu valori aleatorii\n4. Sortarea elementelor tabloului (cоnform variantelor)\n5. Afișarea elementelor tabloului la ecran\n6. Eliberarea memoriei alocate pentru tablou\n7. Ieșire din program\n");
        printf("Alegerea:\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            A = alloc(m, n);
            break;
            case 2:
            insert(A, m, n);
            break;
            case 3:
            rand_insert(A, m, n);
            break;
            case 4:
            bubbleSort(A, m, n);
            break;
            case 5:
            print(A, m, n);
            break;
            case 6:
            free_mem(A, m, n);
            break;
            case 7:
            exit(0);
            default:
            printf("Optiune invalida\n");
            break;
        }
    }while(choice<=7 && choice>=1);
    return 0;
}
