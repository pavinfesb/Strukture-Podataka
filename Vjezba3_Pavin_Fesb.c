// Vjezba 3 - PavinFesb

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_NAME 100
#define MAX_SIZE 1000

//definiranje strukture osoba s imenom, prezimenom i godinom rodjenja

struct osoba;
typedef struct osoba student;
typedef struct osoba* Pozicija;


struct osoba {
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int god;
	Pozicija Next;
};

int Uvod();
int Unos_Pocetak(Pozicija);
int Umetni_Zadnjeg(Pozicija);
Pozicija Trazi_Prezime(Pozicija);
Pozicija Trazi_Prethodnog(Pozicija);
int Brisanje(Pozicija);
int Ispis_Liste(Pozicija);
int Umetni_Iza(Pozicija);
int Umetni_Ispred(Pozicija);
int Sortiranje(Pozicija);
int Upis_u_Datoteku(Pozicija);
int Citanje_iz_Datoteke(Pozicija);

int main()
{
	char c = NULL;
	student Head;
	Head.Next = NULL;
	Pozicija odab_stud = NULL;

	while (c != 'x')
	{
		Uvod();
		scanf(" %c", &c);
		c = tolower(c);
		switch (c)
		{
		case 'a':
		{
			Unos_Pocetak(&Head);
			break;
		}
		case 'b':
		{
			Umetni_Zadnjeg(&Head);
			break;
		}
		case 'c':
		{
			odab_stud = Trazi_Prezime(Head.Next);
			printf("\nOdabrani student je %s %s %d\n", odab_stud->ime, odab_stud->prezime, odab_stud->god);
			break;
		}
		case 'd':
		{
			Brisanje(&Head);
			break;
		}
		case 'e':
		{
			Ispis_Liste(Head.Next);
			break;
		}
		case 'f':
		{
			Umetni_Iza(&Head);
			break;
		}
		case 'g':
		{
			Umetni_Ispred(&Head);
			break;
		}
		case 'h':
		{
			Sortiranje(&Head);
			break;
		}
		case 'i':
		{
			Upis_u_Datoteku(&Head);
			break;
		}
		case 'j':
		{
			Citanje_iz_Datoteke(&Head);
			break;
		}
		case 'x':
		{
			printf("Izlazak iz programa");
			break;
		}
		default:
		{
			printf("\nUpisali ste nedozvoljeni znak\n");
			break;
		}
		}
	}


	return 0;
}

//uvod u program

int Uvod()
{
	printf("\nUnesite odgovarajuce slovo za trazenu operaciju:");
	printf("\n\t a - Dinamicko dodavanje novog elementa na pocetak liste");
	printf("\n\t b - Dinamicko dodavanje novog elementa na kraj liste");
	printf("\n\t c - Pronalazenje elementa u listi po prezimenu");
	printf("\n\t d - Brisanje elementa iz liste");
	printf("\n\t e - Ispis liste");
	printf("\n\t f - Dinamicko dodavanje novog elementa iza odredjenog elementa");
	printf("\n\t g - Dinamicko dodavanje novog elementa ispred odredjenog elementa");
	printf("\n\t h - Sortiranje liste po prezimenima");
	printf("\n\t i - Upis liste u datoteku");
	printf("\n\t j - Citanje liste iz datoteke\n");
	return 0;
}

//dinamicko dodavanje novog elementa na pocetak liste

int Unos_Pocetak(Pozicija P)
{
	Pozicija q = NULL;

	q = (Pozicija)malloc(sizeof(student));
	if (q == NULL)
		return -1;

	q->Next = NULL;

	printf("\nUnesite ime studenta: ");
	scanf(" %s", q->ime);
	printf("\nUnesite prezime studenta: ");
	scanf(" %s", q->prezime);
	printf("\nUnesite godinu rodjenja studenta: ");
	scanf("%d", &q->god);

	q->Next = P->Next;
	P->Next = q;

	return 0;
}

//dinamicko dodavanje novog elementa na kraj liste

int Umetni_Zadnjeg(Pozicija P)
{
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(student));

	printf("\nUnesite ime studenta: ");
	scanf(" %s", q->ime);
	printf("\nUnesite prezime studenta: ");
	scanf(" %s", q->prezime);
	printf("\nUnesite godinu rodjenja studenta: ");
	scanf("%d", &q->god);

	while (P->Next != NULL)
		P = P->Next;

	q->Next = P->Next;
	P->Next = q;
}

//pronalazenje elementa u listi po prezimenu

Pozicija Trazi_Prezime(Pozicija P)
{
	char* prez = NULL;

	prez = (char*)malloc(sizeof(char) * MAX_NAME);
	if (prez == NULL)
		return -1;

	printf("\nUnesite prezime za pretragu: ");
	scanf(" %s", prez);

	while (P != NULL && strcmp(P->prezime, prez) != 0)
		P = P->Next;

	free(prez);

	return P;
}

//brisanje odredjenog elementa iz liste

Pozicija Trazi_Prethodnog(Pozicija P)
{
	char* prez = NULL;

	prez = (char*)malloc(sizeof(char) * MAX_NAME);
	if (prez == NULL)
		return -1;

	printf("\nUnesite prezime za pretragu: ");
	scanf(" %s", prez);

	while (P->Next != NULL && strcmp(P->Next->prezime, prez) != 0)
		P = P->Next;

	if (P->Next == NULL)
		P = NULL;

	free(prez);

	return P;
}


int Brisanje(Pozicija P)
{
	Pozicija temp = NULL;

	P = Trazi_Prethodnog(P);
	if (P == NULL)
	{
		printf("\nNije moguce izvrsiti brisanje.");
		return -1;
	}
	else
	{
		temp = P->Next;
		P->Next = temp->Next;
		printf("\nBrisanje %s %s %d", temp->ime, temp->prezime, temp->god);
		free(temp);
	}

	return 0;
}


//ispis liste

int Ispis_Liste(Pozicija P)
{
	if (P == NULL)
		printf("\nNepostojeca lista.");
	else
	{
		printf("\nIspis liste:\n");
		while (P != NULL)
		{
			printf("\t%s %s %d\n", P->ime, P->prezime, P->god);
			P = P->Next;
		}
	}

	return 0;
}

// dinamicko dodavanje novog elementa iza odredjenog elementa

int Umetni_Iza(Pozicija P)
{
	P = Trazi_Prezime(P);	// trazenje odredjenog elementa po prezimenu
	if (P == NULL)
		return -1;
	
	Unos_Pocetak(P);	//dinamicka alokacija, unos podataka i postavljanje pokazivaca
	
	return 0;	
}

// dinamicko dodavanje novog elementa ispred odredjenog elementa

int Umetni_Ispred(Pozicija P)
{
	P = Trazi_Prethodnog(P);	//trazenje elementa ispred odredjenog
	if (P == NULL)
		return -1;
	
	Unos_Pocetak(P);	//dinamicka alokacija, unos podataka i postavljanje pokazivaca
	
	return 0;
}

// sortiranje liste po prezimenima

int Sortiranje(Pozicija P)
{
	Pozicija i = P;
	Pozicija j = NULL;
	Pozicija prev_j = NULL;
	Pozicija end = NULL;

	while (i->Next != end)
	{
		prev_j = i;
		j = prev_j->Next;

		while (j->Next != end)
		{
			if (strcmp(j->prezime, j->Next->prezime) > 0)
			{
				prev_j->Next = j->Next;
				j->Next = j->Next->Next;
				prev_j->Next->Next = j;
				j = prev_j->Next;
			}
			prev_j = j;
			j = j->Next;
		}
		end = j;
	}

	return 0;
}

// upis liste u datoteku

int Upis_u_Datoteku(Pozicija P)
{
	FILE* f = NULL;
	char* dat = NULL;

	dat = (char*)malloc(sizeof(char) * MAX_SIZE);
	if (dat == NULL)
		return -1;

	printf("\nUnesite ime datoteke za upis: ");
	scanf(" %s", dat);


	f = fopen(dat, "w+");
	if (f == NULL)
	{
		printf("\nGreska. Nije moguce raspolagati trazenom datotekom");
		return -1;
	}

	while (P != NULL)
	{
		fprintf(f, "%s %s %d", P->ime, P->prezime, P->god);
		P = P->Next;

		if (P != NULL)
			fprintf(f, "\n");
	}

	fclose(f);

	return 0;
}

// citanje liste iz datoteke

int Citanje_iz_Datoteke(Pozicija P)
{	
	FILE* f = NULL;
	Pozicija q = NULL;
	char* dat = NULL;
	
	dat = (char*)malloc(sizeof(char) * MAX_SIZE);
	if (dat == NULL)
		return -1;

	printf("\nUnesite datoteku za citanje : ");
	scanf(" %s", dat);

	f = fopen(dat, "r+");
	if (f == NULL)
	{
		printf("\nNepostojeca datoteka");
		return -1;
	}

	while (!feof(f))
	{
		Pozicija q = NULL;

		q = (Pozicija)malloc(sizeof(student));
		if (q == NULL)
			return -1;

		q->Next = NULL;

		fscanf(f, " %s %s %d", q->ime, q->prezime, &q->god);
		q->Next = P->Next;
		P->Next = q;
	}
	fclose(f);

	return 0;
}