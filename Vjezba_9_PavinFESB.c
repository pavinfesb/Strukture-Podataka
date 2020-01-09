#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

struct Stablo;
typedef struct Stablo* Cvor;

struct Stablo
{
	int element;
	Cvor Lijevi;
	Cvor Desni;
};

int Uvod();
Cvor Umetni(Cvor, int);
Cvor Trazi(Cvor, int);
int Ispis(Cvor);
Cvor Trazi_manjeg(Cvor);
Cvor Trazi_veceg(Cvor);
Cvor Brisanje(Cvor, int);


int main()
{
	Cvor root = NULL;
	Cvor temp;
	int c = 0;
	int A;
	while (c != 5)
	{
		Uvod();

		scanf(" %d", &c);

		switch (c)
		{
		case(1):
			printf("\nUnesite element: ");
			scanf(" %d", &A);
			root = Umetni(root, A);
			break;
		case(2):
			Ispis(root);
			break;
		case(3):
			printf("\nKoji element: ");
			scanf(" %d", &A);
			temp = Trazi(root, A);
			if (temp != NULL)
				printf("Element se nalazi na adresi %d", temp->element, temp);
			break;
		case(4):
			printf("\nKoji element: ");
			scanf(" %d", &A);
			root = Brisanje(root, A);
			break;
		case(5):
			printf("\nIzlazak iz programa");
			break;
		default:
			printf("\nKrivi unos. Pokusajte ponovo.");
		}

	}
	return 0;
}


int Uvod()
{
	printf("\nOdaberite broj ");
	printf("\n\t1)\tunos novog elementa");
	printf("\n\t2)\tispis stabla");
	printf("\n\t3)\ttrazenje elementa");
	printf("\n\t4)\tbrisanje elementa");
	printf("\n\t5)\tizlazak iz programa\n");

	return 0;
}

Cvor Umetni(Cvor X, int broj)
{
	if (X == NULL)
	{
		X = (Cvor)malloc(sizeof(struct Stablo));
		X->Lijevi = NULL;
		X->Desni = NULL;
		X->element = broj;
	}
	else if (broj > X->element)
		X->Desni = Umetni(X->Desni, broj);
	else if (broj < X->element)
		X->Lijevi = Umetni(X->Lijevi, broj);

	return X;
}

Cvor Trazi(Cvor X, int broj)
{
	if (X == NULL)
	{
		printf("\nCvor ne postoji.");
		return NULL;
	}

	else if (broj < X->element)
		return Trazi(X->Lijevi, broj);
	else if (broj > X->element)
		return Trazi(X->Desni, broj);

	return X;
}

int Ispis(Cvor X)
{
	static int n = 0;
	int i;

	if (n == -1)
		n = 0;

	if (X != NULL)
	{
		n++;
		Ispis(X->Desni);
		printf("\n");

		for (i = 0; i < n; i++)
			printf("\t");

		printf(" %d", X->element);
		printf("\n");
		n++;
		Ispis(X->Lijevi);
	}
	n--;

	return 0;
}

Cvor Trazi_manjeg(Cvor X)
{
	while (X->Lijevi != NULL)
		X = X->Lijevi;

	return X;
}

Cvor Trazi_veceg(Cvor X)
{
	while (X->Desni != NULL)
		X = X->Desni;

	return X;
}

Cvor Brisanje(Cvor X, int broj)
{
	Cvor temp;

	if (X == NULL)
		printf("Nema tog cvora");
	else if (broj < X->element)
		X->Lijevi = Brisanje(X->Lijevi, broj);
	else if (broj > X->element)
		X->Desni = Brisanje(X->Desni, broj);
	else
	{
		if (X->Lijevi && X->Desni)
		{
			temp = Trazi_manjeg(X->Desni);
			X->element = temp->element;
			X->Desni = Brisanje(X->Desni, X->element);
		}
		else
		{
			temp = X;
			if (X->Lijevi == NULL)
				X = X->Desni;
			else if (X->Desni == NULL)
				X = X->Lijevi;

			free(temp);
		}
	}

	return X;
}
