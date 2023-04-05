#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val;
    struct node* head;
}*list;
/*MA = {{0, 1, 0, 0, 0},
 	{0, 0, 0, 1, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{1, 1, 1, 0, 0}}*/
/*MI = {{0, 1, 0, 0, -1},
 	{1, 0, 0, 0, -1},
	{-1, 1, 0, 0, 0},
	{0, 0, 1, 0, -1},
	{0, 0, -1, 1, 0},
	{0, 1, -1, 0, 0},
	{0, -1, 0, 1, 0}}*/
/*LA = {{1 | 2, 0},
 	{2 | 4, 0},
	{3 | 2, 4, 0},
	{4 | 0},
	{5 | 1, 2, 3, 0}}*/
void MI(); //matricea de incidenta
void LA(); //lista de adiacenta
void MA(); //matricea de adiacenta
void MAtoMI(int **MA, int **MI, int varf, int arc); //din matricea de adiacenta in matricea de incidenta
void MItoLA(int **MI, struct node **LI, int varf, int arc); //din matricea de incidenta in lista de adiacenta
void LAtoMA(struct node **LA, int **MA, int varf, int arc); //din lista de adiacenta in matricea de adiacenta
int **allocMatrix(int varf, int arc); 
void insertMatrix(int ***a, int varf, int arc); 
struct node** allocArrayOfList(int arc);
void insertArrayOfList(struct node ***arrayOflist, int arc);
void insert_node(struct node *initial, int valoare);
void printList(struct node* list);
void printMatrix(int **a, int varf, int arc);
void freeMatrix(int **a, int arc);
void freeList(struct node* list);

int main()
{
    int choice;
    int varf, arc;
    printf("Dati numarul de arce: "); scanf("%d", &arc);
    printf("Dati numarul de varfuri: "); scanf("%d", &varf);
    printf("Meniu:\n1.Matricea de incidenta\n2.Matricea de adiacenta\n3.Lista de adiacenta\nAlegerea: ");
    scanf("%d", &choice);
    switch(choice)
    {
    case 1: MI(varf, arc);
        break;
    case 2: MA(varf, arc);
        break;
    case 3: LA(varf, arc);
        break;
    default: printf("Alegere invalida\n");
        break;
    }
    return 0;
}
void MI(int varf, int arc) 
{
    /*INTRODUCERE DATE*/
    int **matrice;
    insertMatrix(&matrice, varf, arc);
    
    /*TRANSFORMARI*/
    printf("\nMeniu:\n1.Transformarea in matricea de adiacenta\n2.Transformarea in lista de adiacenta\nAlegerea :");
    int choice;
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
        {
            int **MA = allocMatrix(varf, varf);
            struct node** LA = allocArrayOfList(varf);
            MItoLA(matrice, LA, varf, arc);
            LAtoMA(LA, MA, varf, arc);
            printMatrix(MA, varf, varf);
            freeMatrix(MA, arc);
            for(int i = 0; i < varf; i++)
            {
                freeList(LA[i]);
            }
            free(LA);
            freeMatrix(MA, varf);
            break;
        }
        case 2:
        {
            struct node** LA = allocArrayOfList(varf);
            MItoLA(matrice, LA, varf, arc);
            printf("Lista este \n");
            for(int i = 0; i < varf; i++)
            {
                printList(LA[i]);
            }
            for(int i = 0; i < varf; i++)
            {
                freeList(LA[i]);
            }
            free(LA);
            break;
        }
        default:
        printf("Alegere invalida\n");
        break;
    }
    
    /*ELIBERARE MEMORIE*/
    freeMatrix(matrice, arc);
}
void MA(int varf, int arc) 
{
    /*INTRODUCERE DATE*/
    int **matrice;
    insertMatrix(&matrice, varf, varf);
    
    /*TRANSFORMARI*/
    printf("\nMeniu:\n1.Transformarea in matricea de incidenta\n2.Transformarea in lista de adiacenta\nAlegerea: ");
    int choice;
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
        {
            int **MI = allocMatrix(varf, arc);
            MAtoMI(matrice, MI, varf, arc);
            printMatrix(MI, varf, arc);
            freeMatrix(MI, arc);
            break;
        }

        case 2:
        {
            struct node **LA = allocArrayOfList(varf);
            int **MI = allocMatrix(varf, arc);
            MAtoMI(matrice, MI, varf, arc);
            MItoLA(MI, LA, varf, arc);
            for(int i = 0; i < varf; i++)
            {
                printList(LA[i]);
            }
            for(int i = 0; i < varf; i++)
            {
                freeList(LA[i]);
            }
            free(LA);
            freeMatrix(MI, arc);
            break;
        }
        default:
        printf("Alegere invalida\n");
        break;
    }
     
    /*ELIBERARE MEMORIE*/
    freeMatrix(matrice, varf);
}
void LA(int varf, int arc) 
{
    /*INTRODUCERE DATE*/
    struct node **arrayOflist = allocArrayOfList(varf);
    
    insertArrayOfList(&arrayOflist, varf);

    /*AFISARE LISTA*/
    printf("Lista de adiacenta:\n");
    for(int i = 0; i < varf; i++)
        {
            printList(arrayOflist[i]);
        }

    /*TRANSFORMARI*/
    printf("Meniu: \n1. Transformarea in matricea de incidenta\n2. Transformarea in matricea de adiacenta\nAlegerea: ");
    int choice;
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
        {
            int **MI = allocMatrix(varf, arc);
            int **MA = allocMatrix(varf, varf);
            LAtoMA(arrayOflist, MA, varf, arc);
            MAtoMI(MA, MI, varf, arc);
            printMatrix(MI, varf, arc+1); 
            freeMatrix(MI, arc);
            freeMatrix(MA, varf);
            break;
        }
        case 2: 
        {
            int **MA = allocMatrix(varf, varf);
            LAtoMA(arrayOflist, MA, varf, arc);
            printMatrix(MA, varf, varf); 
            freeMatrix(MA, varf);
            break;
        }
            default: printf("Optiune invalida\n");
            break;
        }

    /*ELIBERARE MEMORIE*/
    for(int i = 0; i < varf; i++)
    {
        freeList(arrayOflist[i]);
    }
    free(arrayOflist);

}
void MAtoMI(int **MA, int **MI, int varf, int arc)
{
    int k = 0;
    for(int i = 0; i < varf; i++)
    {
        for(int j = 0; j < varf; j++)
        {
		//daca pe randul i este elementul 1
		//atunci in matricea de incidenta coloana i va avea -1
		//iar coloana j va avea 1
            if(MA[i][j])
            {
                MI[k][i] = -1;
                MI[k][j] = 1;
                k++;
            }
        }
    }
}
void MItoLA(int **MI, struct node **LI, int varf, int arc)
{
    for(int i = 0; i < arc; i++)
    {
       if(i < varf)
       {
            LI[i]->val = i+1; //adauga indicii pentru fiecare rand
            LI[i]->head = NULL;
       }
        for(int j = 0; j < varf; j++)
        {
            if(MI[i][j] == -1) //daca din varful i iese arc
            {
                for(int k = 0; k < varf; k++)
                {
                    
                    if(MI[i][k] == 1) insert_node(LI[j], k+1); //va cauta varful in care intra arcul si va adauga la lista pe pozitia i
                }
                break;
            }
        }
    }
    for(int i = 0 ; i < varf; i++) insert_node(LI[i], 0); //va adauga elementul 0 la sfarsitul fiecarul rand
}

void LAtoMA(struct node **LA, int **MA, int varf, int arc)
{
    struct node *temp;
    for(int i = 0; i < varf; i++)
    {
        int r = LA[i]->val; //varfurile din care ies arce
        for(temp = LA[i]->head; temp->val != 0; temp = temp->head) //varfurile in care intra arce
        {
            MA[r-1][(temp->val)-1] = 1; 
        }
    }
}


int **allocMatrix(int varf, int arc)
{
    int **a = calloc(arc, sizeof(int*));
    if(!a)
    {
        printf("Matricea nu a fost alocata\n");
        exit(1);
    }
    for(int i = 0; i < arc; i++)
    {
        a[i] = calloc(varf, sizeof(int));
        if(!a[i])
        {
            printf("Matricea nu a fost alocata\n");
            exit(1);
        }
    }

    return a;
}
void insertMatrix(int ***a, int varf, int arc)
{
    *a = allocMatrix(varf, arc);
    printf("Dati elementele\n");
    for(int i = 0; i < arc; i++)
    for(int j = 0; j < varf; j++)
    {
        scanf("%d", &(*a)[i][j]);
    }
}

struct node** allocArrayOfList(int varf)
{
    struct node **arrayOflist = malloc(varf*sizeof(struct node*));
    if(!arrayOflist)
    {
        printf("Alocare esuata\n");
        exit(1);
    }
        for(int i = 0; i < varf; i++)
        {
            arrayOflist[i] = malloc(sizeof(struct node));
            if(!arrayOflist[i])
            {
                printf("Alocare esuata\n");
                exit(1);
            }
        }
    return arrayOflist;
}
void insertArrayOfList(struct node ***arrayOflist, int varf)
{

    for(int i = 0; i < varf; i++)
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
void printMatrix(int **a, int varf, int arc)
{
    printf("Matricea este \n  ");
    for(int j = 1; j <= varf; j++)
    {
        printf(" x%d", j);
    }
    for(int i = 0; i < arc; i++)
    {
        printf("\nx%d ", i+1);
        for(int j = 0; j < varf; j++)
        {
            printf("%d  ", a[i][j]);
        }
    }
}
void freeMatrix(int **a, int arc)
{
    for(int i = 0; i < arc; i++) free(a[i]);
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
