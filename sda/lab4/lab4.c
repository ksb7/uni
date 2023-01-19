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
	if(curent== NULL)
	{
		printf("Alocare esuata\n");
		exit(1);
	}
	
	curent->val = valoare;
	curent->head = NULL;
	
	if (initial == NULL) 
	{
	    initial = curent; //pentru primul nod
	}
	
	while(temp->head != NULL)
	{
	    temp = temp->head; //trece prin toate nodurile pana ajunge la ultimul
	}
	temp->head = curent; //adauga noul nod la capat
}
/*void find(struct node *original, int n)
{
    struct node *temp = original;
    for(int i = 0; i < n; i++)
    {
        while (node->head != NULL)
        {
            if(node)
        }
    }
}
*/
int main()
{
	printf("Introduceti numarul de noduri\n");
	int n;
	scanf("%d", &n);
	struct node *N = NULL;
	float element;
	printf("introduceti elementele: \n");
	for(int i = 0; i < n; i++)
	{
		scanf("%f", &element);
		node_insert(N, element);
	}
	while(N != NULL)
    {
        printf("Data = %f\n", N->val); // Print data of current node
        N = N->head;                 // Move to next node
    }
	return 0;
}





