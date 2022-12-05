#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int val; 
    struct no *prox; 
} No; 

No* inicializa();
No* insere(No *, int);
No* retira(No *, int);
void imprime(No *);
void libera(No *);

int main() {
    No *l;
    l = inicializa();
    l = insere(l,10);
    l = insere(l,20);
    l = insere(l,30);
    l = retira(l,30);
    l = insere(l,40);
    l = retira(l,20);
    imprime(l);
    libera(l);
    return 0;
}

No* inicializa(){
    return NULL; 
}

No* insere(No* l, int val){
    No* novo = (No*) malloc(sizeof(No));
    novo->val = val;
    if(!l){
        novo->prox = novo;
        return novo;
    }
    No* p = l;
    while (p->prox != l){
      p = p->prox;
    };
    novo->prox = l;
    p->prox = novo;
    return novo;
}

No* retira(No* l, int val){
    No* p = l;
    No* q = p;
    while((p->prox != l) && (p->val != val)){
        q = p;
        p = p->prox;
    }
    if(p == l){
        l = l->prox;
        No* temp = l;
        while(temp->prox !=p){
          temp = temp->prox;
        }
        free(p);
        temp->prox = l;
        return l;
    }
    q->prox = p->prox;
    free(p);
    return l;
}

void imprime(No* l){
    if(l){
        printf("%d\n",l->val);
        No* p = l->prox;
        while(p!=l){
            printf("%d\n",p->val);
            p = p->prox;
        }
    }
};

void libera(No *l){
    if(l){
        No *p = l->prox;
        while(p!=l){
            No *temp = p;
            p = p->prox;
            free(temp);
        };
        free(l);
    }
}