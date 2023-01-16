#include <stdio.h>
#include <stdlib.h>
struct node
{
	float val;
	struct node *head;
};
void node_insert(struct node **initial, int valoare)
{
	struct node *new = (struct node*) malloc(sizeof(struct node));
	if(new == NULL)
	{
		printf("Alocare esuata\n");
		exit(1);
	} else
	{
		new->val = valoare;
		new->head = (*initial);
		(*initial) = new;
	}
}
int main()
{
	printf("Introduceti numarul de noduri\n");
	int n;
	scanf("%d", &n);
	struct node *N = (struct node*)malloc(sizeof(struct node));
	float element;
	for(int i = 0; i < n; i++)
	{
		printf("introduceti elementul: \n");
		scanf("%f", &element);
		node_insert(&N, element);
	}

	return 0;
}
