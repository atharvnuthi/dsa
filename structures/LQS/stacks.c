// pilhas - LIFO 

#include <stdio.h>
#include <stdlib.h>

typedef struct pilha{
    int top, n; 
    int *vet;
} TP; 

TP *cria(){
    TP *p = (TP*) malloc(sizeof(TP));
    p->top = 0;
    p->n = 1; // tamanho 
    p->vet = (int*) malloc(p->n*sizeof(int));
    return p; 
}

void push(TP *p, int x){
    if (p->top == p->n){
        p->n*=2;
        p->vet = realloc(p->vet,p->n*sizeof(int));
    }
    p->vet[p->top] = x; 
    p->top++; 
}

void pop(TP *p){
    if (p->top != 0){
      int x;
      p->vet[p->top-1] = x;
      p->top--;
    }
}

void imprime(TP *p){
    if (p->top != 0){
        for (int i = p->top-1; i >= 0; --i){
            printf("%d\n",p->vet[i]);
        }
    }
}

void libera(TP *p){
  free(p->vet);
  free(p);
}

int main() {
    TP *p = cria();
    push(p,10);
    push(p,20);
    push(p,30);
    libera(p);
    return 0;
}