// pointers with state management in C

#include <stdio.h>
#include <stdlib.h>

typedef struct arvbin
{
    int val;
    struct arvbin *esq, *dir;
} AB;

typedef struct node
{
    int val;
    struct ll *prox;
} Node;

Node *insere_inicio(Node *l, int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->prox = l;
    return node;
};

void imprime(Node *l)
{
    while (l != NULL)
    {
        printf("%d->", l->val);
        l = l->prox;
    }
    printf("NULL");
};

void helper(AB *a, Node **l, int *c)
{
    if (a)
    {
        if (a->val % 2 == 0)
        {
            *l = insere_inicio(*l, a->val);
            (*c)++;
        }

        // a própria função já reconhece que é um ponteiro!
        helper(a->esq, l, c);
        helper(a->dir, l, c);
    }
}

void selectionSort(Node **head)
{
    for (Node *i = *head; i != NULL; i = i->prox)
    {
        for (Node *j = i->prox; j != NULL; j = j->prox)
        {
            if (i->val > j->val)
            {
                int temp = i->val;
                i->val = j->val;
                j->val = temp;
            }
        }
    }
}

Node *solve(AB *a)
{
    Node *l = NULL;
    int c = 0;
    helper(a, &l, &c);
    printf("- counter: %d\n", c);
    printf("- linkedlist (before): ");
    imprime(l);
    selectionSort(&l);
    printf("\n- linkedlist (after): ");
    imprime(l);
    return l;
}

AB *inicializa(void)
{
    return NULL;
}

AB *criar(int val, AB *esq, AB *dir)
{
    AB *a = (AB *)malloc(sizeof(AB));
    a->val = val;
    a->esq = esq;
    a->dir = dir;
    return a;
}

int main()
{
    AB *a = inicializa();
    a = criar(9, criar(2, NULL, NULL), criar(0, criar(10, NULL, NULL), NULL));
    Node *l = solve(a);
    return 0;
}