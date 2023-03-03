#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int **allocMatrix();
void createMatrix(int **matrice);
void input(int **matrice, int varf);
void Ford(int **matrice, int varf);
int main()
{
    int **MA; //matricea ponderata de adiacenta
    createMatrix(MA);
    int choice;
    printf("Meniu:\n1. Algoritmul Ford\n2.Algoritmul Bellman-Kalaba\nAlegerea: ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: 
        {
            printf("1. Drumul minim\n2.Drumul maxim\nAlegerea: ");
            int choice;
            scanf("%d", &choice);
            switch(choice)
            {
                case 1: 
                {
                    break;
                }
                case 2:
                {
                    break;
                }
            }
            break;
        }
        case 2:
        {
            printf("1. Drumul minim\n2.Drumul maxim\nAlegerea: ");
            int choice;
            scanf("%d", &choice);
            switch(choice)
            {
                case 1: 
                {
                    break;
                }
                case 2:
                {
                    break;
                }
            }
            break;
        }
    }
    return 0;
}
void createMatrix(int **matrice)
{
    printf("Numarul de varfuri\n");
    int varf;
    scanf("%d", &varf);
    matrice = allocMatrix(varf);
    input(matrice, varf);
}
int **allocMatrix(int varf)
{
    int **matrice = malloc(varf*sizeof(int *));
    if(!matrice)
    {
        printf("Alocare esuata");
        exit(1);
    }
    for(int i = 0; i < varf; i++)
    {
        matrice[i] = malloc(varf*sizeof(int));
        if(!matrice[i])
        {
            printf("Alocare esuata");
            exit(1);
        }
    }
    return matrice;
}
void input(int **matrice, int varf)
{
    printf("Dati matricea ponderata de adiacenta (infinit == 100)\n");
    for(int i = 0; i < varf; i++)
    {
        for(int j = 0, k = 0; j < varf, k < i-1; j++, k++)
        {
            scanf("%d", &matrice[i][j]);
            /*TODO:
            for(int k = 0; k < i-1; k++)
            {
                if((i == j && matrice[i][j]) && isdigit(matrice[i][j])); 
                {
                    printf("Element invalid\n");
                    input(matrice, varf);
                }
           }*/
        }
    }
} 
void Ford(int **matrice, int varf)
{
    
}
