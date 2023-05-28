#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Să se creeze fişierul ghidul telefonic. Conform numărului telefonului să se găsească NPP şi adresa proprietarului.*/
/* 
 !!! La numele strazii va accepta doar un cuvant
*/
struct Adresa
{
	char strada[21];
	char nr_casei[5];
	char apartament[4];
};
struct ghidTel
{
	char nume[11];
	char prenume[11];
	char patronimic[11];
	char numar[10];
	struct Adresa adresa;
};
	FILE *ghid_telefon;
	struct ghidTel ghid;
void search()
{
	char alegere[10];
	printf("Dati nr de telefon dupa care sa se efectueze cautarea\n");
	scanf("%s", alegere);
	if((ghid_telefon = fopen("ghid.txt", "r")) == NULL)
	{
		printf("Fisierul nu poate fi deschis");
		exit(1);
	}
	int flag = 0;  
	while (fscanf(ghid_telefon, "NPP %s %s %s Numar %s Adresa %s %s %s\n", ghid.nume, ghid.prenume, ghid.patronimic, ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament) == 7)
	{
    		if (strcmp(alegere, ghid.numar) == 0)
   		{
        	printf("NPP %s %s %s / Adresa %s %s %s\n", ghid.nume, ghid.prenume, ghid.patronimic, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);
        	flag = 1; 
		break; 
		}
	}
	if (!flag)
	{
    		printf("Numarul de telefon dat n-a fost gasit\n");
	}
	fclose(ghid_telefon);
}
int main()
{
	char ordine;
	if((ghid_telefon = fopen("ghid.txt", "w")) == NULL)
	{
		printf("Fisierul nu poate fi deschis\n");
		exit(1);
	}
	printf("Dati NPP, numarul de telefon si adresa(strada, nr casei, ap), apoi introduceti 0 pentru finalizare/numarul de ordine pentru continuare\n");
	do
	{
	scanf("%s%s%s%s%s%s%s", ghid.nume, ghid.prenume, ghid.patronimic, ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);
		fprintf(ghid_telefon, "NPP %s %s %s Numar %s Adresa %s %s %s\n", ghid.nume, ghid.prenume, ghid.patronimic, ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);
		scanf("%s", &ordine);
	}while (ordine != '0');
	fprintf(ghid_telefon, "%d", EOF);
	/*-------------------------*/
	int c;
	while ((c = getchar()) != '\n' && c != EOF); //curata buffer-ul pentru datele de intrare
	/*--------------------------*/
	fclose(ghid_telefon);
	search();
	return 0;
}
