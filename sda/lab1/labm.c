#include <stdio.h>
#include <stdlib.h>

struct Adresa {
	char strada[21];
	char nr_casei[5];
	char apartament[4];
};

struct ghidTel {
	char nume[11];
	char prenume[11];
	char patronimic[11];
	int numar;
	struct Adresa adresa;
};
	FILE *ghid_telefon;
int test()
{
	int choice; 
	printf("dati alegerea dupa care se face cautarea\n");
	scanf("%d", choice);
	return choice;
}
int main() {
	struct ghidTel ghid;

	if ((ghid_telefon = fopen("ghid.txt", "w")) == NULL) {
		printf("Fisierul nu poate fi deschis\n");
		exit(1);
	}

	printf("Dati NPP, numarul de telefon si adresa(strada, nr casei, ap)");
	scanf("%s%s%s%d%s%s%s", ghid.nume, ghid.prenume, ghid.patronimic, &ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);

	while (!feof(stdin)) {
		fprintf(ghid_telefon, "NPP %s %s %s numar %d Adresa %s %s %s\n", ghid.nume, ghid.prenume, ghid.patronimic, ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);
		scanf("%s%s%s%d%s%s%s", ghid.nume, ghid.prenume, ghid.patronimic, &ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);

		char c;
		while ((c = getchar()) != '\n' && c != EOF);
	}

	fclose(ghid_telefon);

	int c;
	while ((c = getchar()) != '\n' && c != EOF);

	int alegere = test();
while ((c = getchar()) != '\n' && c != EOF);
	printf("Aleere %d\n", alegere);

	if ((ghid_telefon = fopen("ghid.txt", "r")) == NULL) {
		printf("Fisierul nu poate fi deschis");
		exit(1);
	}

	int found = 0;  // Flag to indicate if a match is found

	while (fscanf(ghid_telefon, "NPP %s %s %s numar %d Adresa %s %s %s\n", ghid.nume, ghid.prenume, ghid.patronimic, &ghid.numar, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament) == 7) {
		if (alegere == ghid.numar) {
			printf("NPP %s %s %s Adresa %s %s %s\n", ghid.nume, ghid.prenume, ghid.patronimic, ghid.adresa.strada, ghid.adresa.nr_casei, ghid.adresa.apartament);
			found = 1;  // Set the flag to indicate a match is found
			break;      // Exit the loop after finding the match
		}
	}

	if (!found) {
		printf("No entry found for the given phone number.\n");
	}

	fclose(ghid_telefon);

	printf("\nultima");
	return 0;
}

