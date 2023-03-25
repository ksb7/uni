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
    for(int i = 0; i < varf; i++)
    {
        A[i] = B[i];
    }
}
/*void calculFord(int choice)
{
    int *H = calloc(varf, sizeof(int));
    int *H2 = calloc(varf, sizeof(int));
    if(choice == 1) 
    {
        for(int i = 0; i < varf; i++) H2[i] = 100;
    } else if(choice == 2)
    {
        for(int i = 0; i < varf; i++) H2[i] = -100;
    }
    H2[0] = 0;
    do{
    for(int i = 0; i < varf; i++)
    {  
        cpyArr(H, H2, varf);
        cpyArr(H2, H, varf);
        for(int j = 0; j < varf; j++)
        {
           if(i != j && (matrice[i][j] != 100 || matrice[i][j] != -100))
           {
                switch(choice)
                {
                    case 1:
                    { 
                        if(H2[j] - H[i] > matrice[i][j])
                        { 
                            H2[j] = H[i] + matrice[i][j];
                        }
                    }
                    case 2:
                    {
                        if(H2[j] - H[i] < matrice[i][j])
                        {
                            H2[j] = H[i] + matrice[i][j];
                        }
                    }
                    
            }
        }
    }
    }while(cmpArr(H, H2, varf)!= 0);
        int *pozitii = calloc(1, sizeof(int));
        int c = 0;
        pozitii[c] = varf; //stabilim varful din top
        for(int i = varf-1; i >= 0; i--)
        {
            for(int j = varf-1; j > 0; j--)
		    {	
	            if(j<i)
		       {
                    if(H2[i] - H[j] == matrice[j][i]) 
                    { 
                        c++;
                        pozitii = realloc(pozitii, (c+1)*sizeof(int));
                        pozitii[c] = i-1; //determinam drumul dintre punctul initial si final
                    }
                }
            }
		}
    if(H2[pozitii[c++]] - H[0]) pozitii[c++] = 1; //determinam daca este drum de la punctul initial
	printf("Drumul este"); 
	for(int i = c-1; i >= 0; i--)
	{
	    printf(" %d ", pozitii[i]); 
    }
}*/
void Ford(int matrice[7][7], int varf)
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
                            printf("1. H[%d] %d, H2[%d] %d matrice %d\n", i, H[i], j, H2[j], matrice[i][j]);
                            H2[j] = H[i] + matrice[i][j];
                            printf("2. H[%d] %d, H2[%d] %d matrice %d\n \n", i, H[i],  j, H2[j], matrice[i][j]);
                        }
                         
                        break;
                    }
                }
                printf("H[%d] %d, H2[%d] %d ---\n", i, H[i], j, H2[j]);
        }
    }
    }
    }while(cmpArr(H, H2, varf)!= 0);
    for(int i = 0; i < varf; i++)
    {
        printf("H %d \n", H[i]);
    }
        int *pozitii = calloc(1, sizeof(int));
        int c = 0;
        pozitii[c] = varf; //stabilim varful din top
        for(int i = varf-1; i >= 0; i--)
        {
            for(int j = varf-1; j > 0; j--)
		    {	
	            if(j<i)
		       {
                    if(H2[i] - H[j] == matrice[j][i]) 
                    { 
                        c++;
                        pozitii = realloc(pozitii, (c+1)*sizeof(int));
                        pozitii[c] = i-1; //determinam drumul dintre punctul initial si final
                        printf("drumul minim %d diferenta %d-%d = %d\n", H[i], H2[i], H[j], matrice[j][i]);
			    printf("h2 %d h1 %d\n", H2[j], H[i]);
                    }
                }
            }
		}
    if(H2[pozitii[c++]] - H[0]) pozitii[c++] = 1; //determinam daca este drum de la punctul initial
	printf("Drumul este"); 
	for(int i = c-1; i >= 0; i--)
	{
	    printf(" %d ", pozitii[i]); 
    }
}
