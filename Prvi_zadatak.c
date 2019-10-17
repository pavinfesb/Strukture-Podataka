#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 100
#define MAXIM 1000

struct student {
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int bod;
};

typedef struct student stud_in;
typedef struct student* stud_out;

int brojanje_redaka(char*);
int ucitavanje_i_max_bodova(char*, stud_out);

int main()
{
	int i = 0;
	int br = 0;
	float rel = 0;
	int max_bod = 0;
	char* dat = NULL;
	stud_out Studenti = NULL;

	dat = (char*)malloc(sizeof(char) * MAXIM);
	if (dat == NULL)
	{
		printf("\nNeuspjela alokacija memorije :(");
		exit(1);
	}
		

	printf("Unesite ime datoteke: ");
	scanf(" %s", dat);

	br = brojanje_redaka(dat);

	if (br > 0)
	{
		Studenti = (stud_out)malloc(sizeof(stud_in) * br);
		if (Studenti == NULL)
		{
			printf("\nNeuspjela alokacija memorije za strukturu :(");
			exit(1);
		}

		max_bod = ucitavanje_i_max_bodova(dat, Studenti);
		printf("Broj studenata je %d", br);

		for (i = 0; i < br; i++)
		{
			rel = ((float)Studenti->bod / max_bod) * 100;
			printf("\n%s\t%s\t\t\t%d\t\t%d\t\t%f", Studenti->ime, Studenti->prezime, Studenti->bod, max_bod, rel);
			rel = 0;
			Studenti++;
		}
	}
	else
	{
		printf("\nGRESKA");
		exit(1);
	}
	getchar();
	return 0;
}

int brojanje_redaka(char* f)
{	
	int br = 0;
	FILE* file = NULL;
	char* tmp = NULL;

	tmp = (char*)malloc(sizeof(char) * MAXIM);
	if (tmp == NULL)
		exit(1);

	file = fopen(f, "r");
	if (file == NULL)
	{
		printf("\nGRESKA");
		fclose(file);
		exit(1);
	}

	while (!feof(file))
	{
		fgets(tmp, MAXIM - 1, file);
		if (sizeof(tmp) != 0 && isalnum(tmp[0]))
			br++;
	}
	fclose(file);
	return br;
}

int ucitavanje_i_max_bodova(char* f, stud_out _stud)
{	
	int max_bod = 0;
	FILE* file = NULL;
	char* temp = NULL;
	
	temp = (char*)malloc(sizeof(char) * MAXIM);
	if (temp == NULL) 
		exit(1);

	file = fopen(f, "r");
	if (file == NULL)
	{
		printf("\nGRESKA");
		fclose(file);
		exit(1);
	}

	do
	{
		fgets(temp, MAXIM - 1, file);
		sscanf(temp, " %s %s %d", _stud->ime, _stud->prezime, &_stud->bod);
		if (_stud->bod > max_bod)
			max_bod = _stud->bod;
		_stud++;
	} while (!feof(file));

	fclose(file);
	return max_bod;
}