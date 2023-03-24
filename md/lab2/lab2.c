#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **allocMatrix(int varf);
int **createMatrix(int varf);
void input(int **matrice, int varf);
void Ford(int matrice[7][7], int varf);
int cmpArr(int *A, int *B, int varf);
void cpyArr(int *A, int *B, int varf);
int main()
{
    //int **MA; //matricea ponderata de adiacenta
    int choice;
    printf("Numarul de varfuri\n");
    int varf;
    scanf("%d", &varf);
    int MA[7][7] = {{0, 5, 3, 5, 6, 8, 100},
                {100, 0, 100, 1, 4, 100, 100},
                {100, 100, 0, 100, 2, 100, 100},
                {100, 100, 100, 0, 3, 5, 100},
                {100, 100, 100, 100, 0, 4, 6},
                {100, 100, 100, 100, 100, 0, 5},
                {100, 100, 100, 100, 100, 100, 0}};
    //createMatrix(varf);
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
int **createMatrix(int varf)
{
    int **matrice = allocMatrix(varf);
    input(matrice, varf);
    return matrice;
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
    /*matrice = {{0, 5, 3, 6, 8 100},
                {100, 0, 100, 1, 4, 100, 100},
                {100, 100, 0, 100, 2, 100, 100},
                {100, 100, 100, 0, 3, 5, 100},
                {100, 100, 100, 100, 0, 4, 6},
                {100, 100, 100, 100, 100, 0, 5},
                {100, 100, 100, 100, 100, 100, 0}};
    /*printf("Dati matricea ponderata de adiacenta (infinit == 100)\n");
    for(int i = 0; i < varf; i++)
    {
        for(int j = 0; j < varf; j++)
        {
            scanf("%d", &matrice[i][j]);
            TODO:
            for(int k = 0; k < i-1; k++)
            {
                if((i == j && matrice[i][j]) && isdigit(matrice[i][j])); 
                {
                    printf("Element invalid\n");
                    input(matrice, varf);
                }
           }
        }
    }*/
} 
int cmpArr(int *A, int *B, int varf)
{
    for(int i = 0; i < varf; i++)
        if(A[i] != B[i]) return 1;
    return 0;
}
void cpyArr(int *A, int *B, int varf)
{
    /*int Asize = sizeof(A) / sizeof(A[0]);
    int Bsize = sizeof(B) / sizeof(B[0]);
    if(Asize == Bsize)
    {*/
        for(int i = 0; i < varf; i++)
        {
            A[i] = B[i];
        }
    /*} else 
    {
        printf("Eroare la matricea de varfuri\n");
        exit(1);
    }*/
}
void Ford(int matrice[7][7], int varf)
{
    printf("1. Drumul minim\n2.Drumul maxim\nAlegerea: ");
        int choice;
        scanf("%d", &choice);
        switch(choice)
        {
            case 1: 
            {
                int *H = calloc(varf, sizeof(int));
                int *H2 = calloc(varf, sizeof(int));
                for(int i = 0; i < varf; i++) H2[i] = 100;
                H2[0] = 0;
                int count =0;
                do{
                    
                for(int i = 0; i < varf; i++)
                {  
                    cpyArr(H, H2, varf);
                    cpyArr(H2, H, varf);
                    //printf("count %d", count);
                    for(int j = 0; j < varf; j++)
                    {
                        printf("-------------------H[%d] %d, H2[%d] %d ---\n", i, H[i], j, H2[j]);
                       if(i != j && matrice[i][j] != 100)
                       {
                            if(H2[j] - H[i] > matrice[i][j])
                            { 
                                printf("1. H[%d] %d, H2[%d] %d matrice %d\n", i, H[i], j, H2[j], matrice[i][j]);
                                H2[j] = H[i] + matrice[i][j];
                                printf("2. H[%d] %d, H2[%d] %d matrice %d\n \n", i, H[i],  j, H2[j], matrice[i][j]);
                            }
                            printf("H[%d] %d, H2[%d] %d ---\n", i, H[i], j, H2[j]);
                       }
                    } 
                    
                }count++;
                }while(cmpArr(H, H2, varf)!= 0);

                for(int i = varf-1; i >= 0; i--)
                    {
                    for(int j = varf-1; j >= 0; j--)
		    {	//printf("%d ", matrice[varf-i-1][varf-j-1]); 
				  // printf(" H2 %d H %d", H2[i], H[j]);
	                 if(j<i)
		            {
                        if(H2[i] - H[j] == matrice[varf-i-1][varf-i-1]) 
                        {
                           printf("drumul minim %d diferenta %d-%d = %d\n", H[i], H2[j], H[i], matrice[j][i]);
			    printf("h2 %d h1 %d\n", H2[j], H[i]);
           }
                    }
                }printf("\n");
		    }
                break;
	} 
            case 2:
            {
                break;
            }
        }
}
