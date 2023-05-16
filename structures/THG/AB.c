#include <stdio.h>
#include <stdlib.h>

typedef struct arvbin
{
    int val;
    struct arvbin *esq, *dir;
} AB;

// inicializar
AB *inicializa(void)
{
    return NULL;
}

// criar
AB *criar(int val, AB *esq, AB *dir)
{
    AB *a = (AB *)malloc(sizeof(AB));
    a->val = val;
    a->esq = esq;
    a->dir = dir;
    return a;
}

// buscar
AB *buscar(AB *a, int val)
{
    if ((!a) || (a->val == val))
    {
        return a;
    };
    AB *resp = buscar(a->esq, val);
    if (resp) // torna mais eficiente -> evita percorrer a->dir, se achar em a->esq
    {
        return resp;
    };
    return buscar(a->dir, val);
}

// percorrer - Pré-Ordem -> RED - imprimir o Pai e depois os filhos, de esquerdo para direito, de cima para baixo
void *imp_pre(AB *a)
{
    if (a)
    {
        printf("%d ", a->val);
        imp_pre(a->esq);
        imp_pre(a->dir);
    }
}

// percorrer - Simétrico -> ERD - imprimir o esquerdo, depois o Pai, e depois o direito, de baixo para cima
void *imp_sim(AB *a)
{
    if (a)
    {
        imp_sim(a->esq);
        printf("%d ", a->val);
        imp_sim(a->dir);
    }
}

// percorrer - Pós-Ordem -> EDR - imprimir o esquerdo, depois o direito e depois o Pai, de baixo para cima
void *imp_pos(AB *a)
{
    if (a)
    {
        imp_pos(a->esq);
        imp_pos(a->dir);
        printf("%d ", a->val);
    }
}

// liberar - liberar todos os descendentes primeiro e o Pai no final
void liberar(AB *a)
{
    if (a)
    {
        liberar(a->esq);
        liberar(a->dir);
        free(a);
    }
}

// add elements
// remove elements

int main()
{
    AB *a = inicializa();
    a = criar(10, criar(20, NULL, criar(30, NULL, NULL)), NULL);
    AB *no = buscar(a, 20);
    printf("%d\n", no->val);
    imp_pre(a);
    liberar(a);
    return 0;
}