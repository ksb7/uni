#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
int prec[7], curent[7], varf, choice;
/*int  matrice[7][7] = {{0, 5, 3, 5, 6, 8, 100},
                {100, 0, 100, 1, 4, 100, 100},
                {100, 100, 0, 100, 2, 100, 100},
                {100, 100, 100, 0, 3, 5, 100},
                {100, 100, 100, 100, 0, 4, 6},
                {100, 100, 100, 100, 100, 0, 5},
                {100, 100, 100, 100, 100, 100, 0}};*/
int **matrice; //matricea ponderata de adiacenta
#define min(a, b) (a<b) ? a : b;
#define max(a, b) (a>b) ? a : b;
int **allocMatrix();
void createMatrix();
void input();
void Ford();
void BellmanKalaba();
 void PathFord(int H2[7],int vcurent, int indice);
 void PathBellman(int H2[7],int vcurent, int indice);
int cmpArr(int *A, int *B, int varf);
void cpyArr(int *A, int *B, int varf);
void freeArr();

int main()
{
   
    printf("Numarul de varfuri\n");
    scanf("%d", &varf);
    createMatrix(varf);
    printf("Meniu:\n1. Algoritmul Ford\n2.Algoritmul Bellman-Kalaba\nAlegerea: ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: 
        {
            Ford(matrice);
            break;
        }
        case 2:
        {
            BellmanKalaba(matrice);
            break;
        }
    }
    freeArr();
    return 0;
}
void Ford()
{
    printf("1. Drumul minim\n2. Drumul maxim\nAlegerea: ");
        int c;
        scanf("%d", &c);
        int *H = calloc(varf, sizeof(int));
    int *H2 = calloc(varf, sizeof(int));
    //initializeaza varfurile cu etichete
    switch(c)
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
    H2[0] = 0; //varful initial este 0
    do{
    for(int i = 0; i < varf; i++)
    {  
        cpyArr(H, H2, varf);
        cpyArr(H2, H, varf);
        for(int j = 0; j < varf; j++)
        {
            //trece peste elementele de sub diagonala principala
            //si celelalte unde nu este varf
           if(i != j && matrice[i][j] != 100) 
           {
                switch(c)
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
    }while(cmpArr(H, H2, varf)!= 0); //se va opri cand niciun varf nu isi va mai schimba eticheta
    printf("Drumul este \n");
    PathFord(H2, varf-1, 101);
}
void BellmanKalaba()
{
    printf("1. Drumul minim\n2. Drumul maxim\nAlegerea: ");
    int H2[varf], H[varf];
    int c;
    scanf("%d", &c);
    switch(c)
    {
        case 1:
        {
            int minim;
            for(int i = 0; i < varf; i++)
            {
                H2[i] = matrice[i][varf-1]; //initializam vectorul 0 cu elementele de pe ultima coloana
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
				            if(i == k) k = j+2; //daca urmatorul element al matricii este 0, il ignora
                            minim = min(minim, matrice[i][k] + H[k]); // min dintre elementul curent si urmatorul
                            H2[i] = minim;
                        }
                    }
		            H2[varf-1] = 0;
                }
            }while(cmpArr(H2, H, varf) != 0); //se va opri cand nicio eticheta nu se va mai schimba
            break;
        }
        case 2:
        {
            for(int i = 0; i < varf; i++)
            {
                for(int j = 0; j < varf; j++)
                {
                    if(matrice[i][j] == 100) matrice[i][j] = -100; //pentru drumul maxim folosim -inf
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
			            int k = j+1;;
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
    printf("Drumul este: \n");
    PathBellman(H2, 0, varf+1);
}
int vprec = 0, k = 0;
void PathFord(int H2[varf],int vcurent, int indice)
{
	//vcurent = varful curent
	//k = indicele drumului curent
	//indice = indicele drumului pana unde acesta nu se imparte in altul
	//prec[] = drumul precedent (daca drumul a fost impartit in mai multe)
	//curent[] = drumul curent
	//vprec = varful precedent unde s-a impartit drumul 
	
	if(indice < 100) //testeaza daca incepe un nou drum
	{ 
	    int i;
		for(i = 0; i < vprec; i++)
		{
			if(indice == prec[i])
			{
				break;
			}
		}
		for(int j = vprec - 1; j >= i; j--)
		curent[k++] = prec[j];//copie toate valorile de pana la varful nou
		indice = 101; //indicele nu poate fi mai mare decat nr de varfuri
	}
	curent[k++] = vcurent; //adauga varful curent la drum
	if (vcurent == 0)
	{
    		for (int i = k-1; i >= 0; i--)
        	printf("%d ", curent[i]+1);
		printf("\n");
    		vprec = k; //salveaza pozitia din drumul curent
    		for (int i = k-1; i >= 0; i--)
		{
        		prec[k-i-1] = curent[i];
    		}
    		k = 0; //reseteaza indicele pentru un drum nou
	}
	for(int i = varf-1; i >= 0; i--)
	{
		if(matrice[i][vcurent] > 0)
		{
			if(H2[vcurent] - H2[i] == matrice[i][vcurent])
			{
				PathFord(H2, i, indice);
				indice = vcurent; //cand ajunge la capatul unui drum se inntoarce aici si reia procesul din punctul dat
			}
		}
	}
}
void PathBellman(int H2[varf],int vcurent, int indice)
{
	if(indice < varf+1) 
	{ 
	    int i;
		int pozitie;
		for(i = 0; i < vprec; i++)
		{
			if(indice == prec[i])
			{
				break;
			}
		}
		for(int j = 0; j <= i; j++)
		curent[k++] = prec[j];
		indice = varf+1;
	}
	curent[k++] = vcurent; 
	if (vcurent == varf-1) 
	{
    		for (int i = 0; i < k; i++)
        	printf("%d ", curent[i]+1);
		    printf("\n");
    		vprec = k; 
    		for (int i = 0; i < k; i++) 
		{
        		prec[i] = curent[i];
    		}
    		k = 0;
	}
	for(int i = vcurent; i <= varf-1; i++)
	{
		if(matrice[vcurent][i] > 0)
		{
			if(H2[vcurent] - H2[i] == matrice[vcurent][i])
			{
				PathBellman(H2, i, indice); 
				indice = vcurent;
			}
		}
	}
}
void createMatrix()
{
    matrice = allocMatrix();
    input(matrice, varf);
}
int **allocMatrix()
{
    int **temp = malloc(varf*sizeof(int*));
    if(!temp)
    {
        printf("Alocare esuata");
        exit(1);
    }
    for(int i = 0; i < varf; i++)
    {
        temp[i] = malloc(varf*sizeof(int));
        if(!temp[i])
        {
            printf("Alocare esuata");
            exit(1);
        }
    }
    return temp;
}
void input(int **matrice, int varf)
{
    printf("Dati matricea ponderata de adiacenta (infinit == 100)\n");
    for(int i = 0; i < varf; i++)
    {
        for(int j = 0; j < varf; j++)
        {
            scanf("%d", &matrice[i][j]);
        }
    }
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
void freeArr()
{
	for(int i = 0; i < varf; i++)
	{
		free(matrice[i]);
	}
	free(matrice);
}
