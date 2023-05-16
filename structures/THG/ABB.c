#include <stdio.h>
#include <stdlib.h>

typedef struct arvbinbusca
{
    int val;
    struct arvbinbusca *esq, *dir;
} ABB;

// inicializar
ABB *inicializar(void)
{
    return NULL;
}

// criar
ABB *criar(int val, ABB *esq, ABB *dir)
{
    ABB *novo = (ABB *)malloc(sizeof(ABB));
    novo->val = val;
    novo->esq = esq;
    novo->dir = dir;
    return novo;
}

// pré
void imp_pre(ABB *a)
{
    if (a)
    {
        printf("%d ", a->val);
        imp_pre(a->esq);
        imp_pre(a->dir);
    }
}

// pós
void imp_pos(ABB *a)
{
    if (a)
    {
        imp_pos(a->esq);
        imp_pos(a->dir);
        printf("%d ", a->val);
    }
}

// sim
void imp_sim(ABB *a)
{
    if (a)
    {
        imp_sim(a->esq);
        printf("%d ", a->val);
        imp_sim(a->dir);
    }
}

// buscar
ABB *buscar(ABB *a, int val)
{
    if ((!a) || (a->val = val))
    {
        return a;
    }
    if (val < a->val) // menor fica no lado esquerdo, e maior no lado direito -> em ABB
    {
        return buscar(a->esq, val);
    }
    // if no other conditions work, and, val > a->val
    return buscar(a->dir, val);
}

// inserir
ABB *inserir(ABB *a, int val)
{
    if (!a) // create new node with dir and esq = NULL, and val = val
    {
        return criar(val, NULL, NULL);
    }
    if (val < a->val)
    {
        a->esq = inserir(a->esq, val);
    }
    else if (val > a->val)
    {
        a->dir = inserir(a->dir, val);
    }
    return a; // return updated binary tree
}

// retirar
ABB *retirar(ABB *a, int val)
{
    if (!a)
        return a;
    if (val < a->val)
        a->esq = retirar(a->esq, val);
    else if (val > a->val)
        a->dir = retirar(a->dir, val);
    else
    { // info encontrado
        if ((!a->esq) && (!a->dir))
        { // CASO 1
            free(a);
            a = NULL;
        }
        else if ((!a->esq) || (!a->dir))
        { // CASO 2
            ABB *temp = a;
            if (!a->esq)
                a = a->dir; // nó = nó->dir
            else
                a = a->esq; // nó = nó->esq
            free(temp);     // free(nó)
        }
        else
        {                        // CASO 3
            ABB *filho = a->esq; // largest value in left subtree
            while (filho->dir)
                filho = filho->dir;               // until I find largest value
            a->val = filho->val;                  // filho -> nó
            filho->val = val;                     // nó -> filho
            a->esq = remover(a->esq, filho->val); // remover o filhó
        }
    }
    return a;
}

// liberar
void liberar(ABB *a)
{
    if (a)
    {
        liberar(a->esq);
        liberar(a->dir);
        free(a);
    }
}

int main()
{
    return 0;
}