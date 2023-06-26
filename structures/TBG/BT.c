#include <stdio.h>

typedef struct BT
{
    int nKeys, *aKeys;  // number of keys filled, array of keys
    int leaf;           // is leaf or not
    struct BT **childs; // children pointers (array of pointers)
} BT;

// h = log(t)n , n = number of keys, t = minimum degree, t >= 2

BT *inicializar();
BT *criar(int t);
BT *liberar(BT *bt);
BT *buscar(BT *bt, int k);
void imprimir(BT *bt);
BT *inserir(BT *bt, int k, int t); // not implemented
BT *retirar(BT *bt, int k, int t); // not implemented

int main()
{
    return 0;
}

BT *inicializar()
{
    return NULL;
}

BT *criar(int t)
{
    BT *bt = (BT *)malloc(sizeof(BT));
    bt->nKeys = 0;                                          // no keys filled
    bt->leaf = 1;                                           // is leaf
    bt->aKeys = (int *)malloc(sizeof(int) * ((2 * t) - 1)); // max number of keys = 2t - 1
    bt->childs = (BT **)malloc(sizeof(BT *) * (2 * t));     // max number of children = 2t
    for (int i = 0; i < (2 * t); i++)
        bt->childs[i] = NULL; // initialize children pointers to NULL
    return bt;
}

BT *liberar(BT *bt)
{
    if (bt)
    {
        if (!bt->leaf) // if not leaf, free children
        {
            for (int i = 0; i <= bt->nKeys; i++)
                liberar(bt->childs[i]); // free children recursively
        }
        free(bt->aKeys);
        free(bt->childs);
        free(bt);
        return NULL;
    }
}

BT *buscar(BT *bt, int k)
{
    if (!bt)
        return NULL;
    int i = 0;
    while (i < bt->nKeys && k > bt->aKeys[i]) // while aKeys is greater than current aKeys and not end of keys
        i++;
    if (i < bt->nKeys && k == bt->aKeys[i]) // if key is found return bt
        return bt;
    if (bt->leaf) // if leaf and key not found return NULL
        return NULL;
    return buscar(bt->childs[i], k); // else search recursively, for the childs of the key
}

void imprimir_helper(BT *bt, int h)
{
    if (bt)
    {
        int i, j;                       // i = keys, j is for indentation (h)
        for (i = 0; i < bt->nKeys; i++) // print keys and childs recursively
        {
            imprimir_helper(bt->childs[i], h + 1); // print childs recursively first (left to right)
            for (j = 0; j < h; j++)                // print indentation
                printf("\t");
            printf("%d\n", bt->aKeys[i]); // print key
        }
        imprimir_helper(bt->childs[i], h + 1); // print last child recursively (rightmost)
    }
}

void imprimir(BT *bt)
{
    imprimir_helper(bt, 0);
}