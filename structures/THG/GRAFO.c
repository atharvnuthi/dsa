#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct viz
{
    int id;
    struct viz *prox;
} VIZ;

typedef struct grafo
{
    int id;
    VIZ *pv;
    struct grafo *prox;
} GRAFO;

GRAFO *inicializa()
{
    return NULL;
}

void imprime(GRAFO *g)
{
    while (g)
    {
        printf("Vizinhos do %d:\n", g->id);
        VIZ *v = g->pv;
        while (v)
        {
            printf("%d ", v->id);
            v = v->prox;
        }
        printf("\n");
        g = g->prox;
    }
}

void imprime_rec(GRAFO *g)
{
    if (g)
    {
        printf("Vizinhos do %d:\n", g->id);
        VIZ *v = g->pv;
        while (v)
        {
            printf("%d ", v->id);
            v = v->prox;
        }
        printf("\n");
        imprime_rec(g->prox);
    }
}

void libera_viz(VIZ *v)
{
    while (v)
    {
        VIZ *temp = v;
        v = v->prox;
        free(temp);
    }
}

void libera_grafo(GRAFO *g)
{
    while (g)
    {
        libera_viz(g->pv);
        GRAFO *temp = g;
        g = g->prox;
        free(temp);
    }
}

GRAFO *busca_no(GRAFO *g, int x)
{
    if ((!g) || (g->id == x))
        return g;
    return busca_no(g->prox, x);
}

VIZ *busca_aresta(GRAFO *g, int x1, int x2)
{
    GRAFO *g1 = busca_no(g, x1);
    GRAFO *g2 = busca_no(g, x2);
    if ((!g1) || (!g2))
        return NULL;
    VIZ *resp = g1->pv;
    while ((resp) && (resp->id != x2))
        resp = resp->prox;
    return resp;
}

// ELEMENTOS ÚNICOS

GRAFO *insere_no(GRAFO *g, int x)
{
    GRAFO *t = busca_no(g, x);
    if (!t)
    {
        t = (GRAFO *)malloc(sizeof(GRAFO));
        t->id = x;
        t->prox = g;
        t->pv = NULL;
        g = t;
    }
    return g;
}

void insere_um_sentido(GRAFO *g, int x1, int x2)
{
    GRAFO *no = busca_no(g, x1);
    VIZ *viz = (VIZ *)malloc(sizeof(VIZ));
    viz->id = x2;
    viz->prox = no->pv; // viz tem o primeiro vetor do nó como prox
    no->pv = viz;       // viz torna primeiro vetor do nó

    // insere VIZ com valor x2 no NÓ x1, no início
}

void insere_aresta(GRAFO *g, int x1, int x2)
{
    VIZ *v = busca_aresta(g, x1, x2);
    if (v)
        return;
    insere_um_sentido(g, x1, x2);
    insere_um_sentido(g, x2, x1);
}

int main()
{
    return 0;
}