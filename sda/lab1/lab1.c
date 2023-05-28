#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	char numar[10];
	struct Adresa adresa;
};
	FILE *ghid_telefon;
	struct ghidTel ghid;
void test()
{
	int c;
while ((c = getchar()) != '\n' && c != EOF);
	char alegere[10];
	printf("Dati nr de telefon dupa care sa se efectueze cautarea\n");
	scanf("%s", alegere);
	if((ghid_telefon = fopen("ghid.txt", "r")) == NULL)
	{
		printf("Fisierul nu poate fi deschis");
		exit(1);
	}
int found = 0;  // Flag to indicate if a match is found
while (fscanf(ghid_telefon, "NPP %s %s %s numar %s Adresa %s %s %s\n", ghid.nume, ghid.prenume, ghid.patronimic, ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament) == 7)
{
    if (strcmp(alegere, ghid.numar) == 0)
    {
        printf("NPP %s %s %s Adresa %s %s %s\n", ghid.nume, ghid.prenume, ghid.patronimic, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);
        found = 1;  // Set the flag to indicate a match is found
        break;      // Exit the loop after finding the match
}
}

if (!found)
{
    printf("No entry found for the given phone number.\n");
}

// ...
}
int main()
{

	if((ghid_telefon = fopen("ghid.txt", "w")) == NULL)
	{
		printf("Fisierul nu poate fi deschis\n");
		exit(1);
	}
	printf("Dati NPP, numarul de telefon si adresa(strada, nr casei, ap)");
	scanf("%s%s%s%s%s%s%s", ghid.nume, ghid.prenume, ghid.patronimic, ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);
	while(!feof(stdin))
	{
		fprintf(ghid_telefon, "NPP %s %s %s numar %s Adresa %s %s %s\n", ghid.nume, ghid.prenume, ghid.patronimic, ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);
		scanf("%s%s%s%s%s%s%s", ghid.nume, ghid.prenume, ghid.patronimic, ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);

	}
	fclose(ghid_telefon);

test();
	printf("\nultima");
	return 0;
}
