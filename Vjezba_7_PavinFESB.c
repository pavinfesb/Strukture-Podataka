#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SIZE (1024)

struct cvor;
typedef struct cvor* Pozicija;

struct cvor {
	float el;
	Pozicija Next;
};

int Stvori(Pozicija*);
int Push(Pozicija, float);
int Pop(Pozicija, float*);
int Racunanje(float, float, char*, float*);
int Ispitivanje(char*, float*);
int Izracun_postfix(char*, Pozicija);

int main()
{
	char* dat = NULL;
	struct cvor stog;
	stog.Next = NULL;
	
	dat = (char*)malloc(sizeof(char)*MAX_SIZE);
	
	if(dat==NULL)
		return 1;
		
	memset(dat, '\0', MAX_SIZE);
	
	while(strlen(dat)==0)
	{
		printf ("\nUnesite ime datoteke s postfix izrazom: ");
		scanf (" %s", &dat);
	}
	
	if(strchr(dat, ".")==NULL)
		strcat(dat, ".txt");
		
	Izracun_postfix(dat, &stog);
	
	if (&stog == NULL)
		printf("\nGreska u izracunu postfixa.");
	
		
	printf("\nRezultat izracuna postifixa : %f", stog.Next->el);

	free(dat);
	return 0;
}

int Stvori(Pozicija* P)
{
	Pozicija q = NULL;
	P = (Pozicija*)malloc(sizeof(struct cvor));

	if (*P == NULL)
		return 1;

	q = *P;
	q->Next = NULL;

	return 0;
}

int Push(Pozicija P, float x)
{
	Pozicija q = NULL;

	Stvori(&q);

	q->el = x;

	q->Next = P->Next;
	P->Next = q;

	return 0;
}

int Pop(Pozicija P, float* x)
{
	Pozicija q = NULL;
	q = P->Next;
	if (q == NULL)
		return 1;

	P->Next = q->Next;
	*x = q->el;
	free(q);

	return 0;
}

int Racunanje (float x, float y, char* op, float *z)
{
	
	if(op==NULL)
		return 1;
		
	switch(*op){
		case('+'):	*z = x+y;
					break;
		case('-'):	*z = x-y;
					break;
		case('*'):	*z = x*y;
					break;
		case('/'):	
			if(y==0)
			{
				printf("\nGreska. Nije dozvoljeno dijeliti nulom.");
				return 1;
			}
			*z = x/y;
			break;
		default:	printf("\nNije prepoznata operacija.");
					*z = 0;
					break;
	}
	
	return 0;
}

int Ispitivanje(char* mem, float* a)
{
	int x = 0;
	x = sscanf(mem, " %f", a);
	if(x!=1)
		return 1;

	return 0;
}

int Izracun_postfix(char* dat, Pozicija S)
{
	float n, x, y;
	n = x = y = 0;
	
	char *mem = NULL;	FILE *f = NULL;
	
	mem = (char*)malloc(sizeof(char)*MAX_SIZE);
	if(mem == NULL)
		return 1;
		
	memset(mem, '\0', MAX_SIZE);
	
	f = fopen(dat, "r");
	if(f==NULL)
		return -1;
		
	while(!feof(f))
	{
		fscanf(f, " %s", mem);
		if(strlen(mem)==0)
			continue;
			if(!Ispitivanje(mem, &n))
			{
				Pop(S, &y);
				Pop(S, &x);
				Racunanje(x, y, mem, &n);
			}
		Push(S,n);
	}
	fclose(f);
	
	return 0;
}
