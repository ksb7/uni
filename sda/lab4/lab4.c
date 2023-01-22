#include <stdio.h>
#include <stdlib.h>

/*  Fie dată o listă de numere reale. Pentru fiecare element al listei
să se tipărească numărul elementelor negative, ce-l succed. */

struct node
{
	float val;
	struct node *head;
};

void node_insert(struct node *initial, int valoare)
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

void find(struct node *original, int n)
{
    struct node *temp, *control;
    temp = original;
    for(int i = 0; i < n; i++)
    {   
        control = temp->head;
        int k = 0;
        //pentru fiecare nod va trece prin intreaga lista 
        //incepand de la urmatorul 
        for(int j = i+1; j < n; ++j) 
        {
            if(control->val < 0) k++;
            control = control->head;
        }
        printf("Elementul %f are %d elemente negative succesive\n", temp->val, k);
        temp = temp->head;
    }
        
}

int main()
{
	printf("Introduceti numarul de noduri\n");
	int n;
	scanf("%d", &n);
	struct node *N = (struct node*) malloc(sizeof(struct node));
	if(!N)
	{
		printf("Alocare esuata\n");
		exit(1);
	}
	
	float element;
	printf("Introduceti elementele: \n");
	//-------------------------
	//pentru primul nod
	scanf("%f", &element);
	N->val = element;
	N->head = NULL; 
	//-------------------------
	for(int i = 1; i < n; i++)
	{
		scanf("%f", &element);
		node_insert(N, element);
	}
	find(N, n);
	return 0;
}
