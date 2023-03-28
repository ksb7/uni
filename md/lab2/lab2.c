#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int prev[7], curent[7], varf;
int  matrice[7][7] = {{0, 5, 3, 5, 6, 8, 100},
                {100, 0, 100, 1, 4, 100, 100},
                {100, 100, 0, 100, 2, 100, 100},
                {100, 100, 100, 0, 3, 5, 100},
                {100, 100, 100, 100, 0, 4, 6},
                {100, 100, 100, 100, 100, 0, 5},
                {100, 100, 100, 100, 100, 100, 0}};
int **allocMatrix();
int **createMatrix();
void input();
void Ford();
void BellmanKalaba();
void Path(int H2[7],int vcurent, int k, int prec);
int cmpArr(int *A, int *B, int varf);
void cpyArr(int *A, int *B, int varf);
#define min(a, b) (a<b) ? a : b;
#define max(a, b) (a>b) ? a : b;
int main()
{
    //int **MA; //matricea ponderata de adiacenta
    int choice;
    printf("Numarul de varfuri\n");
    scanf("%d", &varf);
    //createMatrix(varf);
    printf("Meniu:\n1. Algoritmul Ford\n2.Algoritmul Bellman-Kalaba\nAlegerea: ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: 
        {
            Ford();
            break;
        }
        case 2:
        {
            BellmanKalaba();
            break;
        }
    }
    return 0;
}
/*int **createMatrix(int varf)
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
}*/
int cmpArr(int *A, int *B, int varf)
{
    for(int i = 0; i < varf; i++)
        if(A[i] != B[i]) return 1;
    return 0;
}
void cpyArr(int *A, int *B, int varf)
{
    for(int i = 0; i < varf; i++)
    {
        A[i] = B[i];
    }
}

void Ford()
{
    printf("1. Drumul minim\n2.Drumul maxim\nAlegerea: ");
        int choice;
        scanf("%d", &choice);
        int *H = calloc(varf, sizeof(int));
    int *H2 = calloc(varf, sizeof(int));
    switch(choice)
    {
        case 1:
        {
            for(int i = 0; i < varf; i++) 
            {
                H2[i] = 100;
            }
            break;
        }
        case 2:
        {
            for(int i = 0; i < varf; i++) 
            {
                H2[i] = -100;
            }
            break;
        }
    }
    H2[0] = 0;
    do{
    for(int i = 0; i < varf; i++)
    {  
        cpyArr(H, H2, varf);
        cpyArr(H2, H, varf);
        for(int j = 0; j < varf; j++)
        {
           if(i != j && matrice[i][j] != 100)
           {
                switch(choice)
                {
                    case 1:
                    { 
                        if(H2[j] - H[i] > matrice[i][j])
                        { 
                            H2[j] = H[i] + matrice[i][j];
                        }
                        break;
                    }
                    case 2:
                    {
                        if(H2[j] - H[i] < matrice[i][j])
                        {
                            H2[j] = H[i] + matrice[i][j];
                        }
                         
                        break;
                    }
                }
            }
        }
    }
    }while(cmpArr(H, H2, varf)!= 0);
}
void BellmanKalaba()
{
    printf("1. Drumul minim\n2.Drumul maxim\nAlegerea: ");
    int H2[varf], H[varf];
    int choice;
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
        {
            int minim;
            for(int i = 0; i < varf; i++)
            {
                H[i] = matrice[i][varf-1]; //initializam vectorul 0
            }
            do{
                cpyArr(H, H2, varf);
		        cpyArr(H2, H, varf);
                for(int i = 0; i < varf; i++)
                {
                    minim = matrice[i][i+1] + H[i+1];
                    for(int j = 0; j < varf-1; j++)
                    {
			            int k = j+1;
                        if(i != j)
                        {
				            if(i == k) k = j+2;
                            minim = min(minim, matrice[i][k] + H[k]);
                            H2[i] = minim;
                        }
                    }
		    H2[varf-1] = 0;
                }
            }while(cmpArr(H2, H, varf) != 0);
            break;
        }
        case 2:
        {
            for(int i = 0; i < varf; i++)
            {
                for(int j = 0; j < varf; j++)
                {
                    if(matrice[i][j] == 100) matrice[i][j] = -100;
                }
                H2[i] = matrice[i][varf-1];
            }
            int maxim;
            do{
                cpyArr(H, H2, varf);
                cpyArr(H2, H, varf);
                for(int i = 0; i < varf; i++)
                { 
                    maxim = matrice[i][i+1] + H[i+1];
                    for(int j = 0; j < varf-1; j++)
                    { 
			            int k = j+1;
                        if(i != j)
                        {
			                if(i == k) k = j+2; 
                            maxim = max(maxim, matrice[i][k] + H[k]); 
                            H2[i] = maxim;
                        }
                    }
                    H2[varf-1] = 0;
                }
            }while(cmpArr(H2, H, varf) != 0);
            break;
        }
    }
    
}

