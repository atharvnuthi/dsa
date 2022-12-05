#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int val; 
    struct no *prox, *ant;
} No;

No* inicializa();
No* insere(No*, int);
void imprime(No*);
void libera(No*);

int main() {
    No *l;
    l = inicializa(); 
    l = insere(l,10);
    l = insere(l,20);
    l = insere(l,30);
    imprime(l);
    libera(l);
    return 0;
}

No* inicializa(){
   return NULL; 
}

No* insere(No* l, int val){
    No *novo = (No*)malloc(sizeof(No));
    novo->val = val;
    novo->prox = l;
    novo->ant = NULL;
    if(l){
      l->ant = novo; 
    }
    return novo;
}

void imprime(No *l){
  while(l){
    printf("%d\n",l->val);
    l = l->prox; 
  }
}

void libera(No *l){
  No *p = l;
  No *q;
  while(p){
    q = p;
    p = p->prox;
    free(q); 
  }
}