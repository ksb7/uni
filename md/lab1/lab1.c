#include <stdio.h>
#include <stdlib.h>

/*TODO
free every alloc-ed memory
*/

struct node
{
    int val;
    struct node* head;
}*list;
 //int m, n, u;
 void MI(); //matricea de incidenta
void LA(); //lista de adiacenta

void MA(); //matricea de adiacenta
int **allocMatrix(int n, int m); //aloca memorie pentru matrici
void insertMatrix(int ***a, int n, int m); //introduce valori in matrici
void insert_node(struct node *initial, int valoare); //introduce valori in lista
void LAtoMI(int *lista, int n, int m); //din lista in matrice de incidenta
void printList(struct node* list);
void printMatrix(int **a, int n, int m);
void insertArrayOfList(struct node ***arrayOflist, int m);
struct node** allocArrayOfList(int m);
void MAtoMI(int **MA, int **MI, int n, int m);
/*TODO
void MItoLI();
void LItoMA();
*/

int main()
{
    int choice;
    int n, m;
    printf("Dati numarul de arce: "); scanf("%d", &m);
    printf("Dati numarul de varfuri: "); scanf("%d", &n);
    printf("Meniu:\n1.Matricea de incidenta\n2.Matricea de adiacenta\n3.Lista de adiacenta\nAlegerea: ");
    scanf("%d", &choice);
    switch(choice)
    {
    case 1: MI(n, m);
        break;
    case 2: MA(n, m);
        break;
    case 3: LA(n, m);
        break;
    default: printf("Alegere invalida\n");
        break;
    }
    return 0;
}
void freeMatrix(int **a, int n)
{
    for(int i = 0; i < n; i++) free(a[i]);
    free(a);
}
void freeList(struct node* list)
{
   struct node* tmp;
   while (list)
    {
       tmp = list;
       list = list->head;
       free(tmp);
    }
}
int **allocMatrix(int n, int m)
{
    int **a = calloc(m, sizeof(int*));
    if(!a)
    {
	    printf("Matricea nu a fost alocata\n");
	    exit(1);
    }
    for(int i = 0; i < m; i++)
    {
        a[i] = calloc(n, sizeof(int));
        if(!a[i])
        {
            printf("Matricea nu a fost alocata\n");
            exit(1);
        }
    }
    
    printf("Memoria pentru matrice a fost alocata\n");
    return a;
}
void insertMatrix(int ***a, int n, int m)
{
    *a = allocMatrix(m, n);
    printf("Dati elementele\n");
    for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
    {
        scanf("%d", &(*a)[i][j]);
    }
}
/*struct node** allocArrayOfList(int m)
{
    struct node **arrayOflist = malloc(m*sizeof(struct node*));
    if(!arrayOflist)
    {
        printf("Alocare esuata\n");
        exit(1);
    }
	for(int i = 0; i < m; i++) 
	{
	    arrayOflist[i] = malloc(sizeof(struct node*));
	    if(!arrayOflist[i])
	    {
	        printf("Alocare esuata\n");
	        exit(1);
	    }
	}
	return arrayOflist;
}
void insertArrayOfList(struct node ***arrayOflist, int m)
{
    
    for(int i = 0; i < m; i++)
	{
	    printf("Dati numarul coloanei:");
	    scanf("%d", &(arrayOflist[i]->val));
	    int node;
	    *(arrayOflist[i])->head=NULL;
	    printf("Dati arcele:");
	    do
	    {
	        scanf("%d", &node);
	        insert_node(&arrayOflist[i], node);
	    }while(node);
	}
}*/
void MI(int n, int m) //matricea de incidenta
{
    int **matrice;
    insertMatrix(&matrice, n, m);
    printMatrix(matrice, n, m);
    printf("\nMeniu:\n1.Transformarea in matricea de adiacenta\n2.Transformarea in lista de adiacenta\nAlegerea :");
    int choice;
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: 
        {
            int **MA = allocMatrix(n, n);
            //functia
            printMatrix(MA, n, n);
            break;
        }
        case 2:
        {
            
        }
        //functia
        break;
        default:
        printf("Alegere invalida\n");
        break;
    }
}
void MA(int n, int m) //matricea de adiacenta
{
    int **matrice;
    insertMatrix(&matrice, n, n);
    printMatrix(matrice, n, n);
    printf("\nMeniu:\n1.Transformarea in matricea de incidenta\n2.Transformarea in lista de adiacenta\nAlegerea: ");
    int choice;
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: 
        {
            int **MI = allocMatrix(n, m);
            MAtoMI(matrice, MI, n, m);
            printMatrix(MI, n, m);
            break;
        }
        
        case 2:
        //functia
        break;
        default:
        printf("Alegere invalida\n");
        break;
    }
}
void insert_node(struct node *initial, int valoare)
{
	struct node *temp = NULL;
	struct node *curent = (struct node*) malloc(sizeof(struct node));
	if(!curent)
	{
		printf("Alocare esuata\n");
		exit(1);
	}
	curent->val = valoare;
	curent->head = NULL;
	//temp si initial vor avea aceeasi adresa in memorie
	temp = initial; 
	while(temp->head != NULL)
	{
	    temp = temp->head; //trece prin toate nodurile pana ajunge la ultimul
	}
	temp->head = curent; //adauga noul nod la capat
}
struct node** allocArrayOfList(int m)
{
    struct node **arrayOflist = malloc(m*sizeof(struct node*));
    if(!arrayOflist)
    {
        printf("Alocare esuata\n");
        exit(1);
    }
	for(int i = 0; i < m; i++) 
	{
	    arrayOflist[i] = malloc(sizeof(struct node*));
	    if(!arrayOflist[i])
	    {
	        printf("Alocare esuata\n");
	        exit(1);
	    }
	}
	return arrayOflist;
}
void insertArrayOfList(struct node ***arrayOflist, int m)
{
    
    for(int i = 0; i < m; i++)
	{
	    printf("Dati numarul coloanei:");
	    scanf("%d", &((*arrayOflist)[i]->val));
	    int node;
	    (*arrayOflist)[i]->head=NULL;
	    printf("Dati arcele:");
	    do
	    {
	        scanf("%d", &node);
	        insert_node((*arrayOflist)[i], node);
	    }while(node);
	}
}
void LA(int n, int m) //lista de adiacenta
{
    /*ALOCARE MEMORIE*/
	struct node **arrayOflist = allocArrayOfList(m);
	
	insertArrayOfList(&arrayOflist, m);
	/*VERIFICARE ERORI
	if(!arrayOflist)
	{
	    printf("Alocare esuata\n");
	    exit(1);
	}
	for(int i = 0; i < n; i++) 
	{
	    if(!arrayOflist[i])
	    {
	        printf("Alocare esuata\n");
	        exit(1);
	    }
	}*/
	
	/*INTRODUCERE VALORI*/
	/*for(int i = 0; i < n; i++)
	{
	    printf("Dati numarul coloanei:");
	    scanf("%d", &(arrayOflist[i]->val));
	    int node;
	    arrayOflist[i]->head=NULL;
	    printf("Dati arcele:");
	    do
	    {
	        scanf("%d", &node);
	        insert_node(arrayOflist[i], node);
	    }while(node);
	}*/
	
	/*AFISARE LISTA*/
	printf("Lista de adiacenta:\n");
	for(int i = 0; i < n; i++)
	    {
	        printList(arrayOflist[i]);
	    }
	
	/*TRANSFORMARI*/
	printf("Meniu: \n1. Transformarea in matricea de incidenta\n2. Transformarea in matricea de adiacenta\nAlegerea: ");
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
	
	/*ELIBERARE MEMORIE*/
	for(int i = 0; i < m; i++)
	{
	    freeList(arrayOflist[i]);
	}
	free(arrayOflist);
	
}
void LAtoMI(int *lista, int n, int m) //lista de adiacenta la matricea de incidenta
{
	int **matrice = allocMatrix(m, n);

}
void printList(struct node* list)
{
    printf("%d | ", list->val);
    list = list->head;
    while(list)
    {
        printf("%d ", list->val);
        list=list->head;
    }
    printf("\n");
}

void printMatrix(int **a, int n, int m)
{
    printf("Matricea este \n  ");
    for(int j = 1; j <= n; j++) 
    {
        printf(" x%d", j);
    }
    for(int i = 0; i < m; i++)
    {
        printf("\nx%d ", i+1);
        for(int j = 0; j < n; j++) 
        {
            printf("%d  ", a[i][j]);
        }
    }
}

void MAtoMI(int **MA, int **MI, int n, int m)
{
    
    for(int i = 0; i < n; i++)
    {
        int k = 0;
        for(int j = 0; j < n; j++)
        {
            if(MA[i][j]==1) 
            {
                MI[k][i] = -1;
                MI[k][j] = 1;
            }
            k++;
        }
    }
}
/*void MItoLA(int **MI, struct node **LI, int n, int m)
{
    
}

*/

