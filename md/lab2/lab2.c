#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **allocMatrix();
void createMatrix(int **matrice, int varf);
void input(int **matrice, int varf);
void Ford(int **matrice, int varf);
int cmpArr(int *A, int *B);
int main()
{
    int **MA; //matricea ponderata de adiacenta
    int choice;
    printf("Numarul de varfuri\n");
    int varf;
    scanf("%d", &varf);
    createMatrix(MA, varf);
    printf("Meniu:\n1. Algoritmul Ford\n2.Algoritmul Bellman-Kalaba\nAlegerea: ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: 
        {
            Ford(MA, varf);
            break;
        }
        case 2:
        {
            /*printf("1. Drumul minim\n2.Drumul maxim\nAlegerea: ");
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
            }*/
            break;
        }
    }
    return 0;
}
void createMatrix(int **matrice, int varf)
{
    matrice = allocMatrix(varf);
    input(matrice, varf);
}
int **allocMatrix(int varf)
{
    int **matrice = malloc(varf*sizeof(int*));
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
        for(int j = 0; j < varf; j++)
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
int cmpArr(int *A, int *B)
{
    int Asize = sizeof(A) / sizeof(A[0]);
    int Bsize = sizeof(B) / sizeof(B[0]);
    if(Asize == Bsize)
    {
        for(int i = 0; i < Asize; i++)
        {
            for(int j = 0; j < Bsize; j++)
            {
                if(A[i] != B[j]) return 1;
            }
        }
    } else return 1;
    return 0;
}
void Ford(int **matrice, int varf)
{
    printf("1. Drumul minim\n2.Drumul maxim\nAlegerea: ");
        int choice;
        scanf("%d", &choice);
        switch(choice)
        {
            case 1: 
            {
                int *H = malloc(varf * sizeof(int));
                int *H2 = malloc(varf * sizeof(int));
                for(int i = 0; i < varf; i++) H2[i] = 100;
                H2[0] = 0;
                do{
                for(int i = 0; i < varf; i++)
                {
                    H[i] = H2[i];
                    for(int j = 0; j < varf; j++)
                    {
                        if(matrice[i][j] != 0 && matrice[i][j] != 100)
                        {
                            if(H2[j] - H[i] > matrice[i][j])
                            {
                                H2[j] = H[i] + matrice[i][j];
                                printf("H %d, H2 %d\n", H[i], H2[i]);
                            }
                        }
                    } 
                }
                }while(cmpArr(H, H2)!= 0);
                break;
            }
            case 2:
            {
                break;
            }
        }
}
