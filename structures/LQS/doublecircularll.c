#include<stdio.h>
#include<stdlib.h>

typedef struct ldec{int info;
                    struct ldec * ant;
                    struct ldec * prox;
                   }TLDEC;

TLDEC * TLDEC_inicializar(){
    return NULL;
}

TLDEC * TLDEC_insere_inicio(TLDEC * l, int x){
    TLDEC * novo = (TLDEC*)malloc(sizeof(TLDEC));
    novo->info = x;
    novo->prox = l;
    if (!l){
        novo->prox = novo;
        novo->ant = novo;
    }
    else{
        novo->prox = l;
        novo->ant = l->ant;
        l->ant->prox = novo;
        l->ant = novo;
    }

    return novo;

}

TLDEC * TLDEC_destroi(TLDEC * l){
    TLDEC * p = l->prox;
    while (p!=l){
        TLDEC *q = p;
        p = p->prox;
        free(q);
        
    }
    free(l);
    return NULL;
}

void * TLDEC_imprimir(TLDEC * l){
    
    TLDEC * p = l;
    do {
        printf("%d ",p->info);
        p = p->prox;
    } while (p!=l);
}

int main(){
    TLDEC * l = TLDEC_inicializar();
    l = TLDEC_insere_inicio(l,5);
    l = TLDEC_insere_inicio(l,4);
    l = TLDEC_insere_inicio(l,3);
    l = TLDEC_insere_inicio(l,2);
    l = TLDEC_insere_inicio(l,1);
    TLDEC_imprimir(l);
    l = TLDEC_destroi(l);
    return 0;
}