// filas - FIFO 

#include <stdio.h>
#include <stdlib.h>

typedef struct fila{
  int n, tam;
  int *vet;
} Fila;

Fila* cria(){
  Fila *f = (Fila*) malloc(sizeof(Fila));
  f->tam = 10;
  f->vet = (int*) malloc(sizeof(int)*f->tam);
  f->n = 0;
  return f;
}

void insere(Fila *f, int x){
  if (f->n == f->tam) { // cheia 
    f->tam *= 2;
    f->vet = realloc(f->vet,f->tam*sizeof(int)); 
  }
  f->vet[f->n] = x; 
  f->n++;
}

void retira(Fila *f){
  if (f->n == 0){exit(1);}; // vazia
  int y = 0;
  while (y != f->n-1){
    f->vet[y] = f->vet[y+1];
    y++;
  }
  int x;
  f->vet[y] = x; 
  f->n--; 
}

void libera(Fila *f){
  free(f->vet);
  free(f);
}

int main() {
  Fila *f;
  f = cria();
  insere(f,10);
  insere(f,30);
  insere(f,40); 
  insere(f,60);
  retira(f);
  libera(f);
  return 0;
}