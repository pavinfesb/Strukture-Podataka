#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define MAX_NAME (128)
#define MAX_LENGTH (512)

struct Node;
typedef struct Node* Position_Node;

struct Stack;
typedef struct Stack* Position_Stack;

struct Node {
	char name[MAX_NAME];
	Position_Node Child;
	Position_Node Next;
};

struct Stack {
	Position_Node el;
	Position_Stack Next;
};

int Menu();
int Create_Node(Position_Node, char*);
int Print_Node(Position_Node, char*);
int Push_Node(Position_Stack, Position_Node);
Position_Node Pop_Node(Position_Stack);
Position_Node Enter_Node(Position_Node, char*, char*, Position_Stack);
Position_Node Exit_Node(Position_Node, Position_Stack);

int main()
{
	char *name;

	name = (char*)malloc(sizeof(char) * MAX_NAME);
	
	char c;
	int a = 1;

	char* i, * j;

	struct Node root;
	struct Stack S;

	Position_Node pointer = &root;
	S.Next = NULL;

	printf("\nUnesite ime root direktorija: ");
	scanf(" %s", root.name);
	root.Child = NULL;
	root.Next = NULL;


	system("cls");

	while (a)
	{
		Menu();
		scanf(" %c", &c);

		memset(name, '\0', MAX_NAME);

		switch (c) 
		{
		case('1'):
			printf("\nEnter the name of new directory: ");
			scanf(" %s", name);
			Create_Node(pointer, name);
			break;

		case('2'):
			printf("\nEnter the name of directory to enter: ");
			scanf(" %s", name);
			pointer = Enter_Node(pointer, name, &S);
			break;

		case('3'):
			pointer = Exit_Node(pointer, &S);
			break;

		case('4'):
			Print_Node(pointer, name);
			break;

		case('5'):
			printf("\nExit the programm");
			a = 0;
			break;
		default:
			printf("\nInvalid input. Please try again.");
			break;
		}

	}

	return 0;
}

int Menu()
{
	printf("\Unesite odgovarajuci broj za zeljenu DOS naredbu:");
	printf("\n\t1)\tmd");
	printf("\n\t2)\tcd dir");
	printf("\n\t3)\tcd..");
	printf("\n\t4)\tdir");
	printf("\n\t5)\texit\n");

	return 0;
}


int Create_Node(Position_Node P, char* str)
{
	Position_Node q;

	q = (Position_Node)malloc(sizeof(struct Node));
	q->Child = NULL;
	q->Next = NULL;

	strcpy(q->name, str);

	if (q == NULL)
	{
		printf("\nMemory allocation error.");
		return 1;
	}
	
	if (P->Child == NULL)
			P->Child = q;
	else
	{
			q->Next = P->Child;
			P->Child = q;
	}

	return 0;
}

int Print_Node(Position_Node P, char* name)
{
	printf("\nPrinting of directory: ", name);

	P = P->Child;
	while (P != NULL)
	{
		printf("\n %s", P->name);
		P = P->Next;
	}

	return 0;
}

int Push_Node(Position_Stack S, Position_Node T)
{
	Position_Stack q;

	q = (Position_Stack)malloc(sizeof(struct Stack));

	if (q == NULL) 
	{
		printf("\nMemory allocation error.");
		return 1;
	}
	
	q->el = T;
	q->Next = S->Next;

	S->Next = q;

	return 0;
}

Position_Node Pop_Node(Position_Stack S)
{
	Position_Node q;
	Position_Stack tmp;

	if (S->Next == NULL)
		return NULL;

	q = S->Next->el;
	tmp = S->Next;
	S->Next = tmp->Next;

	free(tmp);
	return q;
}

Position_Node Enter_Node(Position_Node P, char* name, Position_Stack S)
{
	Position_Node tmp = P->Child;

	while (tmp != NULL && strcmp(tmp->name, name) != 0)
		tmp = tmp->Next;
	if (NULL == tmp)
		printf("\nNo such sub-directory with that name.");
	else
	{
		Push_Node(S, P);
		return tmp;
	}

	return P;
}

Position_Node Exit_Node(Position_Node P, Position_Stack S)
{
	Position_Node q;

	q = Pop_Node(S);
	if (q == NULL)
	{
		printf("Cannot exit root directory.");
		return P;
	}
		return q;
}
