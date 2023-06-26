#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define TS 101 // tableSize is a prime number

typedef struct aluno
{
    int mat;
    float cr;
    struct aluno *prox;
} A; // linked list of students

typedef A *TH[TS]; // TH is a table of pointers to A, and size TS

int hash(int mat)
{
    return mat % TS; // division method (simplest) - hash function
}

void inicializa(TH th)
{
    for (int i = 0; i < TS; ++i)
        th[i] = NULL;
}

A *busca(TH th, int mat)
{
    int h = hash(mat);
    A *p = th[h];
    while ((p) && (p->mat != mat))
        p = p->prox;
    return p;
}

A *aloca(int mat, float cr)
{
    A *novo = (A *)malloc(sizeof(A));
    novo->mat = mat;
    novo->cr = cr;
    novo->prox = NULL;
    return novo;
}

void insere(TH th, int mat, float cr)
{
    int h = hash(mat);
    A *p = th[h], *ant = NULL;
    while ((p) && (p->mat < mat))
    {
        ant = p;     // guarda endereço do anterior
        p = p->prox; // busca posição de inserção na lista
    }
    if ((p) && (p->mat == mat))
    {
        p->cr = cr; // atualiza CR , se matricula já existir
        return;
    }
    A *novo = aloca(mat, cr);
    novo->prox = p; // insere no início ou no meio da lista
    if (!ant)
    {
        th[h] = novo; // insere no início da lista
    }
    else
    {
        ant->prox = novo; // insere no meio da lista
    }
}

float retirar(TH th, int mat)
{
    int h = hash(mat);
    if (!th[h])
        return FLT_MIN; // matricula não existe
    A *p = th[h], *ant = NULL;
    float cr = FLT_MIN;
    while ((p) && p->mat < mat)
    {
        ant = p;     // guarda endereço do anterior
        p = p->prox; // busca posição de inserção na lista
    }
    if ((!p) || (p->mat != mat)) // matricula não existe
    {
        return cr;
    }

    // p aponta para o nó a ser retirado da lista
    if (!ant)
    {
        th[h] = p->prox; // o p será retirado, pois não tem anterior, e é inicio da lista
    }
    else
    {
        ant->prox = p->prox; // retira do meio da lista ou do fim da lista
    }
    cr = p->cr;
    free(p); // libera memória do nó retirado da lista
    return cr;
}

void liberar(TH th)
{
    for (int i = 0; i < TS; ++i)
    {
        if (th[i])
        {
            A *p = th[i], *q;
            while (p)
            {
                q = p;
                p = p->prox;
                free(q);
            }
        }
    }
}

void imprimir(TH th)
{
    int i;
    for (int i = 0; i < TS; ++i)
    {
        printf("%d: ", i);
        if (th[i])
        {
            A *p = th[i];
            while (p)
            {
                printf("%d %.2f\n", p->mat, p->cr);
                p = p->prox;
            }
        }
        else
        {
            printf("NULL\n");
        }
    }
}