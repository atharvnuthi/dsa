#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *prox;
} Node;

Node *inicializa();
Node *insere_inicio(Node *, int);
Node *insere_final(Node *, int);
void imprime(Node *);
void libera(Node *);
Node *delhead(Node *);
Node *deltail(Node *);
Node *retira(Node *, int);

int main()
{
    Node *l = inicializa();
    l = insere_inicio(l,10);
    l = insere_final(l,20);
    l = insere_inicio(l,20);
    l = delhead(l);
    l = deltail(l);
    l = retira(l,10);
    l = insere_inicio(l,30);
    imprime(l);
    return 0;
}

// Initialization
Node *inicializa()
{
    return NULL;
};

// Insertion_head
Node *insere_inicio(Node *l, int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->prox = l;
    return node; // new node becomes l
};

// Insertion_tail
Node *insere_final(Node *l, int val)
{
    Node *p = l; // to not change the value of l
    while (p->prox != NULL)
    { // find last element
        p = p->prox;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->prox = NULL;
    p->prox = node; // last element prox is the new node
    return l; 
};

// Print
void imprime(Node *l)
{
    while (l != NULL)
    { // l->prox != NULL (won't print last element)
        printf("%d\n", l->val);
        l = l->prox;
    }
};

// Clear
void libera(Node *l)
{
    Node *p = l, *q;
    while (p)
    {
        q = p;
        p = p->prox;
        free(q);
    }
};

// Deletion_head
Node *delhead(Node *l)
{
    Node *p = l;
    l = l->prox;
    free(p);
    return l;
};

// Deletion_tail
Node *deltail(Node *l)
{
    Node *p = l;
    Node *q = l;
    while (p->prox != NULL)
    {
        q = p;
        p = p->prox;
    }
    q->prox = NULL;
    free(p);
    return l;
};

// Deletion_specific
Node *retira(Node *l, int val)
{
    Node *p = l, *q = NULL;
    while ((p) && (p->val != val))
    {
        q = p;
        p = p->prox;
    }
    if (!p)
    {
        return l;
    } // elemento não encontrado
    else if (!q)
    {
        l = l->prox;
    } // elemento é primeiro
    else
    {
        q->prox = p->prox;
    } // elemento em qualquer outra posição
    free(p);
    return l;
}