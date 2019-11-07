#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE (1000)

struct clan;
typedef struct clan faktor;
typedef struct clan* Pozicija;

struct clan
{
    int koef;
    int exp;
    Pozicija Next;
};

int Kreiraj(Pozicija *);
int Ucitaj_iz_Datoteke(Pozicija);
int Ispis(Pozicija);
int Zbrajanje(Pozicija, Pozicija, Pozicija);
int Mnozenje(Pozicija, Pozicija, Pozicija);

int main()
{
    struct clan A, B, zbroj, produkt;

    A.Next = NULL;
    B.Next = NULL;
    zbroj.Next = NULL;
    produkt.Next = NULL;

    Ucitaj_iz_Datoteke(&A);
    Ucitaj_iz_Datoteke(&B);
    
    printf("\nIz datoteke su ucitani polinomi:\nA = ");
    Ispis(A.Next);
    printf("\nB = ");
    Ispis(B.Next);
    printf("\n");
    

    printf("\nZbroj polinoma je ");
    Zbrajanje(A.Next, B.Next, &zbroj);
    Ispis(zbroj.Next);

    printf("\nUmnozak polinoma je ");
    Mnozenje(A.Next, B.Next, &produkt);
    Ispis(produkt.Next);

    return 0;
}

// stvaranje polinomskog clana i postavljanje pokazivaca

int Kreiraj(Pozicija *head)
{
    Pozicija q = NULL;

    *head = (Pozicija)malloc(sizeof(faktor));
    if (*head == NULL) 
        return -1;

    q = *head;
    q->Next = NULL;

    return 0;
}

// ucitavanje polinoma iz datoteke i upisivanje u privremene varijable radi zbrajanja i mnozenja

int Ucitaj_iz_Datoteke(Pozicija P)
{
    Pozicija q = NULL;
    Pozicija temp = NULL;
    char *dat = NULL;
    FILE *f = NULL;

    dat = (char*)malloc(sizeof(char) * MAX_SIZE);
    if (dat == NULL) 
        return -1;

    printf("\nUnesite ime datoteke za citanje : ");
    scanf(" %s", dat);

    f = fopen(dat, "r");
    if (f == NULL)
    {
        printf("\nNije moguce raspolagati datotekom.");
        return -1;
    }

    while (!feof(f))
    {
        Kreiraj (&q);

        fscanf(f, " %d %d", &q->koef, &q->exp);

        temp = P;
        while (temp->Next != NULL && temp->Next->exp > q->exp)
            temp = temp->Next;

        if (temp->Next != NULL && temp->Next->exp == q->exp)
        {
            temp->Next->koef += q->koef;
            free(q);
            if (temp->Next->koef == 0)
            {
                q = temp->Next;
                temp->Next = q->Next;

                free(q);
            }
        }
        else
        {
            q->Next = temp->Next;
            temp->Next = q;
        }

    }
    fclose(f);

    return 0;
}

//ispisivanje rezultata operacija s polinomima na ekranu

int Ispis(Pozicija P)
{
    int first = 1;
    while (P != NULL)
    {
        if (first)
        {
            printf("%dx^%d", P->koef, P->exp);
            first = 0;
        }
        else
        {
            if (P->koef > 0)
                printf(" +%dx^%d", P->koef, P->exp);
            else
                printf(" %dx^%d", P->koef, P->exp);
        }

        P = P->Next;
    }

    return 0;
}

// zbrajanje dvaju ucitanih polinoma

int Zbrajanje(Pozicija A, Pozicija B, Pozicija zbroj)
{
    Pozicija q = NULL;
    Pozicija temp = NULL;

    while (A != NULL && B != NULL)
    {
        Kreiraj(&q);

        if (A->exp > B->exp)
        {
            q->exp = A->exp;
            q->koef = A->koef;
            A = A->Next;
        }
        else if (A->exp < B->exp)
        {
            q->exp = B->exp;
            q->koef = B->koef;
            B = B->Next;
        }
        else
        {
            q->exp = A->exp;
            q->koef = A->koef + B->koef;
            A = A->Next;
            B = B->Next;
        }

        q->Next = zbroj->Next;
        zbroj->Next = q;

        zbroj = q;
    }

    if (A == NULL)
        temp = B;
    else
        temp = A;

    while (temp != NULL)
    {
        Kreiraj(&q);

        q->exp = temp->exp;
        q->koef = temp->koef;

        q->Next = zbroj->Next;
        zbroj->Next = q;

        zbroj = q;

        temp = temp->Next;
    }

    return 0;
}

// mnozenje dvaju ucitanih polinoma

int Mnozenje(Pozicija A, Pozicija B, Pozicija produkt)
{
    Pozicija q = NULL;
    Pozicija  temp = NULL;
    Pozicija i = NULL;
    Pozicija j = NULL;

    i = A;

    while (i != NULL)
    {
        j = B;
        while (j != NULL)
        {
            Kreiraj(&q);

            q->exp = i->exp + j->exp;
            q->koef = i->koef * j->koef;

            temp = produkt;

            while (temp->Next != NULL && temp->Next->exp > q->exp)
                temp = temp->Next;

            if (temp->Next != NULL && temp->Next->exp == q->exp)
            {
                temp->Next->koef += q->koef;
                free(q);

                if (temp->Next->koef == 0)
                {
                    q = temp->Next;
                    temp->Next = q->Next;

                    free(q);
                }
            }
            else
            {
                q->Next = temp->Next;
                temp->Next = q;
            }

            j = j->Next;
        }
        i = i->Next;
    }

    return 0;
}
