#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE (1000)

struct cvor;
typedef struct cvor* Pozicija;
struct cvor {
	
	int broj;
	Pozicija Next;
};

int Uvod();
int Stvori(Pozicija*);
int Generator_broja(int, int);
int Push_stack(Pozicija, int);
int Push_queue(Pozicija, int);
int Pop(Pozicija);
int Ispis(Pozicija);

int main()
{
	int x = 0;
	int a = 1;
	int min = 10;
	int max = 100;
	char slovo;
	struct cvor stog, red;

	stog.Next = NULL;
	red.Next = NULL;

	while (a)
	{
		Uvod();

		scanf(" %c", &slovo);
		tolower(slovo);

		switch (slovo) {

		case ('a'):
			x = Generator_broja(min, max);
			Push_stack(&stog, x);
			Ispis(stog.Next);
			break;
		case ('b'):
			Pop(&stog);
			Ispis(stog.Next);
			break;
		case ('c'):
			x = Generator_broja(min, max);
			Push_queue(&red, x);
			Ispis(red.Next);
			break;
		case ('d'):
			Pop(&red);
			Ispis(red.Next);
			break;
		case ('e'):
			a = 0;
			break;
		default:
			printf("\nUnijeli ste nedozvoljeni znak. Ponovite upis.\n");
			break;
		}
	}

	return 0;
}

int Uvod()
{
	printf("\nUnesite odgovarajuci broj za zeljenu radnju:");
	printf("\na)\tDodaj element na stog");
	printf("\nb)\tSkini element sa stoga");
	printf("\nc)\tDodaj element na red");
	printf("\nd)\tSkini element s reda");
	printf("\ne)\tkraj programa\n\n");
	return 0;
}

int Stvori(Pozicija* P)
{
	Pozicija q = NULL;

	*P = (Pozicija*)malloc(sizeof(struct cvor));
	if (q == NULL) 
		return -1;

	q = *P;
	q->Next = NULL;

	return 0;
}

int Generator_broja(int min, int max)
{
	return rand() % (max - min) + min;
}

int Push_stack(Pozicija P, int x)
{
	Pozicija q = NULL;
	Stvori(&q);

	q->broj = x;
	q->Next = P->Next;
	P->Next = q;

	return 0;
}

int Push_queue(Pozicija P, int x)
{
	static Pozicija zadnji;
	Pozicija q = NULL;

	if (P->Next == NULL)
		zadnji = P;

	Stvori(&q);

	q->broj = x;

	q->Next = zadnji->Next;
	zadnji->Next = q;

	zadnji = q;

	return 0;
}

int Pop(Pozicija P)
{
	Pozicija q = NULL;

	q = P->Next;

	if (q == NULL) 
		return -1;

	P->Next = q->Next;
	printf("\nSkidanje broja %d\n", q->broj);
	free(q);

	return 0;
}

int Ispis(Pozicija P)
{
	if (P == NULL)
	{
		printf("\nPrazno.");
		return 0;
	}

	printf("\nIspis liste:");
	while (P)
	{
		printf(" %d", P->broj);
		P = P->Next;
	}

	return 0;
}
