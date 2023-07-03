#include <stdio.h>

typedef struct BPT
{
    int nKeys, *aKeys;          // number of keys filled, array of keys
    int leaf;                   // is leaf or not
    struct BPT **childs, *prox; // children pointers (array of pointers), prox pointer for leafs only (linked list)
} BPT;

BPT *inicializar()
{
    return NULL;
}

BPT *criar(int t)
{
    BPT *bpt = (BPT *)malloc(sizeof(BPT));
    bpt->nKeys = 0;                                          // no keys filled
    bpt->leaf = 1;                                           // is leaf
    bpt->aKeys = (int *)malloc(sizeof(int) * ((2 * t) - 1)); // max number of keys = 2t - 1
    bpt->childs = (BPT **)malloc(sizeof(BPT *) * (2 * t));   // max number of children = 2t
    bpt->prox = NULL;                                        // initialize prox to NULL
    for (int i = 0; i < (t * 2); ++i)
    {
        bpt->childs[i] = NULL; // initialize children pointers to NULL
    }
    return bpt;
}

BPT *buscar(BPT *bpt, int k)
{
    if (!bpt)
        return NULL;
    int i = 0;
    while (i < bpt->nKeys && k > bpt->aKeys[i])
        i++;
    if (i < bpt->nKeys && k == bpt->aKeys[i] && bpt->leaf) // Só se pode ter certeza que uma chave foi encontrada quando se chega a uma folha!
        return bpt;
    if (bpt->leaf)
        return NULL;
    if (bpt->childs[i] == k)
        i++;
    return buscar(bpt->childs[i], k);
}

void imprimir_helper(BPT *bpt, int h)
{
    if (bpt)
    {
        int i, j;                        // i = keys, j is for indentation (h)
        for (i = 0; i < bpt->nKeys; i++) // print keys and childs recursively
        {
            imprimir_helper(bpt->childs[i], h + 1); // print childs recursively first (left to right)
            for (j = 0; j < h; j++)                 // print indentation
                printf("\t");
            printf("%d\n", bpt->aKeys[i]); // print key
        }
        imprimir_helper(bpt->childs[i], h + 1); // print last child recursively (rightmost)
    }
}

void imprimir(BPT *bpt)
{
    imprimir_helper(bpt, 0);
}

void liberar(BPT *bpt)
{
    if (bpt)
    {
        if (!bpt->leaf) // if not leaf, free children
        {
            for (int i = 0; i <= bpt->nKeys; i++)
                liberar(bpt->childs[i]); // free children recursively
        }
        free(bpt->aKeys);
        // free(bpt->childs); - don't need to free childs, because it's a pointer to a pointer
        free(bpt);
    }
}

BPT *inserir(BPT *bpt, int k, int t); // not implemented
BPT *retirar(BPT *bpt, int k, int t); // not implemented