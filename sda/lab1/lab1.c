#include <stdio.h>
#include <stdlib.h>
/*Să se creeze fişierul ghidul telefonic. Conform numărului telefonului să se găsească NPP şi adresa proprietarului.*/
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
	int numar;
	struct Adresa adresa;
};
int main()
{
	struct ghidTel ghid;
	FILE *ghid_telefon;

	if((ghid_telefon = fopen("ghid.txt", "w")) == NULL)
	{
		printf("Fisierul nu poate fi deschis\n");
		exit(1);
	}
	printf("Dati NPP, numarul de telefon si adresa(strada, nr casei, ap)");
	scanf("%s%s%s%d%s%s%s", ghid.nume, ghid.prenume, ghid.patronimic, &ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);
	while(!feof(stdin))
	{
		fprintf(ghid_telefon, "NPP %s %s %s numar %d Adresa %s %s %s\n", ghid.nume, ghid.prenume, ghid.patronimic, ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);
		scanf("%s%s%s%d%s%s%s", ghid.nume, ghid.prenume, ghid.patronimic, &ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);

	}
	fclose(ghid_telefon);
	fflush(stdin);
	int alegere;
	printf("Dati numarul de telefon dupa care sa se inceapa cautarea\n");
	scanf("%d", &alegere);
	printf("Aleere");
	if((ghid_telefon = fopen("ghid.txt", "r")) == NULL)
	{
		printf("Fisierul nu poate fi deschis");
		exit(1);
	}
	if(!feof(ghid_telefon))
	{
		if(alegere == ghid.numar)
		{
			printf("NPP %s %s %s Adresa %s %s %s\n", ghid.nume, ghid.prenume, ghid.patronimic, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);
		}
	}
	printf("\nultima");
	return 0;
}
