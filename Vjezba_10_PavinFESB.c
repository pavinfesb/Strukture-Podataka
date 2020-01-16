#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef MAX_SIZE
#define MAX_SIZE (1024)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct Cvor;
typedef struct Cvor* Pozicija_cvor;

struct Cvor
{
	char* element;
	Pozicija_cvor Lijevi;
	Pozicija_cvor Desni;
};

struct Stog;
typedef struct Stog* Pozicija_stog;

struct Stog
{
	Pozicija_cvor element_cvor;
	Pozicija_stog Next;
};

int Ispis(int, Pozicija_cvor);
int Brisanje_stoga(Pozicija_stog);
int Brisanje_stabla(Pozicija_cvor);
int Stvori_cvor_stabla(Pozicija_cvor*);
int Pop(Pozicija_stog S, Pozicija_cvor *element);
int Push (Pozicija_stog, Pozicija_cvor);
int Stvori_cvor_na_stogu (Pozicija_stog*);
int Stvori_stablo(char*, Pozicija_stog, Pozicija_cvor*);

int main()
{
	char* dat = NULL;
	Pozicija_stog stack = NULL;
	Pozicija_cvor root = NULL;

	Stvori_cvor_na_stogu(&stack);

	dat = (char*)malloc(sizeof(char)*MAX_SIZE);

	if (dat == NULL)
	{
		printf("\nGreska prilikom otvaranja datoteke.");
		return -1;
	}

	memset(dat, '\0', MAX_SIZE);

	printf("\nUnesite ime datoteke za citanje: ");
	scanf(" %s", dat);

	if (strrchr(dat, '.') == NULL)
		strcat(dat, ".txt");

	Stvori_stablo(dat, stack, &root);

	printf("\n\nPreorder ispis stabla proracuna:\t");
	Ispis(1, root);

	printf("\n\nInorder ispis stabla proracuna:\t");
	Ispis(2, root);

	printf("\n\nPostorder ispis stabla proracuna:\t");
	Ispis(3, root);

	Brisanje_stoga(stack);
	Brisanje_stabla(root);

	return 0;
}

int Stvori_cvor_na_stogu(Pozicija_stog *S)
{
	Pozicija_stog q = NULL;
	q = (Pozicija_stog)malloc(sizeof(struct Stog));

	if (q == NULL)
	{
		printf("Greska prilikom stvaranja cvora na stogu.");
		return -1;
	}

	q->element_cvor = NULL;
	q->Next = NULL;
	*S = q;

	return 0;
}

int Push(Pozicija_stog S, Pozicija_cvor P)
{
	Pozicija_stog q = NULL;
	q->element_cvor = P;
	q->Next = S->Next;
	S->Next = q;
	return 0;
}

int Pop(Pozicija_stog S, Pozicija_cvor *element)
{
	Pozicija_stog temp = NULL;
	Pozicija_cvor q = NULL;
	if (S == NULL)
	{
		printf("\nGreska sa stogom.");
		return -1;
	}

	temp = S->Next;
	if (temp == NULL)
	{
		printf("\nGreska s elementima stoga.");
		return -1;
	}

	S->Next = temp->Next;
	q = temp->element_cvor;

	free(temp);

	*element = q;

	return 0;
}

int Stvori_cvor_stabla(Pozicija_cvor *P)
{
	Pozicija_cvor q = NULL;
	q = (Pozicija_cvor)malloc(sizeof(struct Cvor));

	if (q == NULL)
	{
		printf("\nGreska prilikom alokacije memorije za cvor.");
		return -1;
	}

	q->element = NULL;
	q->Lijevi = NULL;
	q->Desni = NULL;

	*P = q;

	return 0;
}

int Brisanje_stabla(Pozicija_cvor P)
{
	if (P == NULL)
		return 0;

	Brisanje_stabla(P->Lijevi);
	Brisanje_stabla(P->Desni);

	free(P);

	return 0;
}

int Brisanje_stoga(Pozicija_stog S)
{
	if (S == NULL)
		return 0;

	Brisanje_stoga(S->Next);
	Brisanje_stabla(S->element_cvor);

	free(S);
	return 0;
}

int Ispis(int c, Pozicija_cvor P)
{
	switch (c)
	{
	case(1):
	{
		if (P != NULL)
		{
			if (P->Lijevi != NULL)
				printf(" ( ");
			Ispis(c, P->Lijevi);
			printf(" %s", P->element);
			Ispis(c, P->Desni);
			if (P->Desni != NULL)
				printf(" ) ");
		}
	}
	break;

	case(2):
	{
		if (P != NULL)
		{
			printf(" %s", P->element);
			Ispis(c, P->Lijevi);
			Ispis(c, P->Desni);
		}
	}
	break;

	case(3):
	{
		if (P != NULL)
		{
			Ispis(c, P->Lijevi);
			Ispis(c, P->Desni);
			printf(" %s"), P->element;
		}
	}
	break;
	}

	return 0;
}

int Stvori_stablo(char* dat, Pozicija_stog stack, Pozicija_cvor *root)
{
	int brojac_cvorova = 0;
	int broj = 0;

	char* buffer = NULL;
	Pozicija_cvor q = NULL;
	FILE *f = NULL;

	buffer = (char*)malloc(sizeof(char) * MAX_SIZE);

	if (buffer == NULL)
	{
		printf("\nGreska prilikom alociranja memorije za medjuspremnik.");
		return -1;
	}

	memset(buffer, '\0', MAX_SIZE);

	f = fopen(dat, "r");

	if (f == NULL)
	{
		printf("\nGreska prilikom otvaranja datoteke.");
		return -1;
	}

	while (!feof(f))
	{
		memset(buffer, '\0', MAX_SIZE);

		Stvori_cvor_stabla(&q);

		fscanf(f, " %s", buffer);

		brojac_cvorova = strlen(buffer);

		brojac_cvorova++;

		q->element = (char*)malloc(sizeof(char)*brojac_cvorova);

		if (q->element == NULL)
		{
			printf("\nGreska sa cvorom");
			free(q);
			break;
		}

		memset(q->element, '\0', brojac_cvorova);
		brojac_cvorova--;

		strncpy(q->element, buffer, brojac_cvorova);

		q->Lijevi = NULL;
		q->Desni = NULL;

		brojac_cvorova = sscanf(buffer, " %d", &broj);

		if (brojac_cvorova == EOF || brojac_cvorova <= 0)
		{
			Pop(stack, &q->Desni);
			Pop(stack, &q->Lijevi);
		}

		Push(stack, q);
	}

	fclose(f);
	free(buffer);

	Pop(stack, &q);
	*root = q;

	return 0;
}
