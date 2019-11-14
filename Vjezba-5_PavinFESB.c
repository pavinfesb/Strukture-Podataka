#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME (100)
#define MAX_SIZE (1000)

struct element;
typedef struct element clan;
typedef struct element* Pozicija;

struct element
{
	int broj;
	Pozicija Next;
};

int Stvori(Pozicija *);
int Ucitaj_iz_Datoteke(Pozicija, char*);
int Presijecanje(Pozicija, Pozicija, Pozicija);
int Uniranje(Pozicija, Pozicija, Pozicija);
int Ispis(Pozicija);


int main ()
{
	clan L1, L2, presijek, unija;
	char* ime1, ime2;

	ime1 = (char*)malloc(sizeof(char) * MAX_SIZE);
	ime2 = (char*)malloc(sizeof(char) * MAX_SIZE);

	L1.Next = NULL;
	L2.Next = NULL;
	presijek.Next = NULL;
	unija.Next = NULL;

	printf("\nUnesite ime datoteke u kojoj se nalazi prva lista: ");
	scanf(" %s", ime1);
	Ucitaj_iz_Datoteke(&L1, ime1);
	printf("\nPrva lista: ");
	Ispis(L1.Next);

	printf("\nUnesite ime datoteke u kojoj se nalazi druga lista: ");
	scanf(" %s", ime2);
	Ucitaj_iz_Datoteke(&L2, ime2);
	printf("\nDruga lista: ");
	Ispis(L2.Next);

	Presijecanje(L1.Next, L2.Next, &presijek);
	printf("\n\nPresijek dviju listi je : ");
	Ispis(presijek.Next);

	Uniranje(L1.Next, L2.Next, &unija);
	printf("\nUnija dviju listi je : ");
	Ispis(unija.Next);
	
	return 0;
}

int Stvori(Pozicija *P)
{
	Pozicija q = NULL;
	*P = (Pozicija)malloc(sizeof(clan));
	if (*P == NULL)
	{
		printf("Nije alocirana memorija za clana liste.");
		return -1;
	}
	q = *P;
	q->Next = NULL;
	return 0;
}

int Ucitaj_iz_Datoteke(Pozicija P, char* dat)
{
	Pozicija q = NULL;
	Pozicija temp = NULL;
	FILE* f = NULL;

	memset(dat, '\0', MAX_SIZE);

	f = fopen(dat, "r");

	if (f == NULL)
	{
		printf("\nGreska. Datoteke nije otvorena.");
		return -1;
	}

	while (!feof(f))
	{
		Stvori(&q);
		fscanf(f, " %d", &q->broj);
		temp = P;

		while (temp->Next != NULL && temp->Next->broj >= q->broj)
			temp = temp->Next;

		q->Next = temp->Next;
		temp->Next = q;
	}

	fclose(f);
	return 0;
}

int Presijecanje(Pozicija L1, Pozicija L2, Pozicija L3)
{
	Pozicija q = NULL;
	while (L1 && L2)
	{
		if (L1->broj > L2->broj)
			L1 = L1->Next;
		else if (L1->broj < L2->broj)
			L2 = L2->Next;
		else
		{
			Stvori(&q);
			q->broj = L1->broj;
			q->Next = L3->Next;
			L3->Next = q;
			L3 = q;
			L1 = L1->Next;
			L2 = L2->Next;
		}
	}
	return 0;
}

int Uniranje(Pozicija L1, Pozicija L2, Pozicija L3)
{
	Pozicija q = NULL;
	Pozicija temp;
	while (L1 && L2)
	{
		Stvori(&q);
		if (L1->broj > L2->broj)
		{
			q->broj = L1->broj;
			L1 = L1->Next;
		}
		else if (L1->broj < L2->broj)
		{
			q->broj = L2->broj;
			L2 = L2->Next;
		}
		else
		{
			q->broj = L1->broj;
			L1 = L1->Next;
			L2 = L2->Next;
		}

		if (L3->broj == q->broj)
			free(q);
		else
		{
			q->Next = L3->Next;
			L3->Next = q;
			L3 = q;
		}
	}

		if (L1)
			temp = L1;
		else
			temp = L2;

		while (temp)
		{
			Stvori(&q);
			q->broj = temp->broj;
			if (L3->broj == q->broj)
				free(q);
			else
			{
				q->Next = L3->Next;
				L3->Next = q;
				L3 = q;
			}
			temp = temp->Next;
		}
	
	return 0;
}


int Ispis(Pozicija P)
{
	while (P != NULL)
	{
		printf(" %d", P->broj);
		P = P->Next;
	}
	return 0;
}
