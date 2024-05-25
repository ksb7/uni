#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define delimLinie "()-:, ;" //delimitatoare de propozitie
int pozitiaPropozitie; 
int pozitiaCuvinte; 

char **token(char* input)
{
	char** tokens = malloc(pozitiaPropozitie * sizeof(char*)); //pentru vectorul de cuvinte
	char* token; //pentru fiecare cuvant in parte
    pozitiaCuvinte = 0;
	if(!tokens)
	{
		printf("Alocare esuata\n");
		exit(1);
	}
	token = strtok(input, delimLinie); //cauta primul cuvant din propozitie
	
	/* in cazul cand intalneste vreun caracter din delimLinie
	il inlocuieste cu NULL 
	iar urmatorul apel al functiei strtok va continua de la pozitia caracterului NULL
	pana cand va intalni sfarsitul liniei*/
	
    while (token != NULL)
	{
		tokens[pozitiaCuvinte] = token; //stocheaza fiecare cuvant in vectorul de pointeri
		pozitiaCuvinte++;
		token = strtok(NULL, delimLinie); //stocheaza urmatorul cuvant
	}
	tokens[pozitiaCuvinte] = NULL; //caracterul endline finiseaza crearea vectorului de cuvinte
	//for(int i = 0; i < pozitiaCuvinte; i++)
	//printf("tokens %s\n", tokens[i]);
	return tokens;
}
char* input(void)
{
	char *input = malloc(1* sizeof(char));
	int i = 0; //pentru pozitie
	pozitiaPropozitie = 1; //pentru spatiul total alocat
	/*scanf returneaza numarul de caractere citite de la tastatura
	deci, cand va fi scanat cate un caracter al propozitiei
	functia va returna 1*/
	printf("Propozitia este: \n");
	do
	/*ciclul do while controleaza daca citirea de la tastatura a avut loc
	si daca noul caracter citit este new line*/
	{
		input = realloc(input, pozitiaPropozitie * sizeof(char)); //realocheaza memoria +1 spatiu
		i++;
		pozitiaPropozitie++;
	}while (scanf("%c", &input[i-1]) == 1 && input[i-1] != '.');
	input[i] = '\0'; 
	
	//deoarece sirurile de caracter se termina cu \0
	//a fost alocat spatiu, apoi initializat dupa citirea tuturor caracterelor
	
	/*astfel se va citi cate un caracter si, simultan, se va aloca memorie pentru urmatorul 
	atata timp cat acesta nu este newline*/
	if(input == NULL)
	{
	    printf("Alocare esuata\n");
	    exit(1);
	} else return input;
}

int main()
{
    char *propozitia = input();
    char **cuvinte = token(propozitia);
    char *maximal;
    maximal = cuvinte[0];
    for(int i = 0; i < pozitiaCuvinte; i++)
    {
        if(strcmp(maximal, cuvinte[i]) < 0) maximal = cuvinte[i];
    }
    printf("Cel mai mare cuvant este %s\n", maximal);
    return 0;
}
