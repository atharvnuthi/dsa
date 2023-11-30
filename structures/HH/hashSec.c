// hash em arquivo binário
// 1 arquivo de dados, 1 arquivo de hash
// -1 means NULL

#include <stdio.h>
#include <stdlib.h>

// 16 bytes (4 x 4 bytes)
typedef struct aluno
{
    int mat, prox, status;
    float cr;
} TA;

// função de divisão
int hash_function(int mat, int tam)
{
    return mat % tam;
}

void inicializa(char *hash, char *dados, int n)
{
    FILE *fp = fopen(dados, "wb");
    if (!fp)
        exit(1);
    fclose(fp);
    fp = fopen(hash, "wb");
    if (!fp)
        exit(1);
    int i, elem = -1;
    for (i = 0; i < n; i++)
        fwrite(&elem, sizeof(int), 1, fp);
    fclose(fp);
}

TA *aloca(int mat, float cr)
{
    TA *novo = (TA *)malloc(sizeof(TA));
    novo->mat = mat;
    novo->cr = cr;
    novo->prox = -1;
    novo->status = 1;
    return novo;
}

TA *busca(char *hash, char *dados, int n, int mat)
{
    FILE *fp = fopen(hash, "rb");
    if (!fp)
        exit(1);
    int pos;
    int h = hash_function(mat, n);
    fseek(fp, h * sizeof(int), SEEK_SET); // go to the position of hash in the hash file
    fread(&pos, sizeof(int), 1, fp);      // read in the hash file, the position of the initial element in the data file
    fclose(fp);
    if (pos == -1)
        return NULL;

    fp = fopen(dados, "rb");
    if (!fp)
        exit(1);
    fseek(fp, pos, SEEK_SET); // go to the position of the initial element in the data file
    TA aux;
    while (1)
    {
        // check if it is the element
        fread(&aux, sizeof(TA), 1, fp); // read the initial element into the aux variable
        if ((aux.mat == mat) && (aux.status))
        {
            TA *resp = TH_aloca(aux.mat, aux.cr);
            resp->prox = aux.prox;
            fclose(fp);
            return resp;
        }
        // otherwise return when the next element is NULL
        if (aux.prox == -1)
        {
            fclose(fp);
            return NULL;
        }
        // go to the next element
        fseek(fp, aux.prox, SEEK_SET);
    }
}

float retira(char *hash, char *dados, int n, int mat)
{
    FILE *fp = fopen(hash, "rb");
    if (!fp)
        exit(1);
    int pos;
    int h = hash_function(mat, n);
    fseek(fp, h * sizeof(int), SEEK_SET);
    fread(&pos, sizeof(int), 1, fp);
    fclose(fp);
    if (pos == -1)
        return -1;
    float cr = -1; // initial value is NULL, so if not found return NULL

    fp = fopen(dados, "rb+");
    if (!fp)
        exit(1);
    TA aux;
    while (1)
    {
        fseek(fp, pos, SEEK_SET);
        fread(&aux, sizeof(TA), 1, fp);
        if ((aux.mat == mat) && (aux.status))
        {
            cr = aux.cr;
            aux.status = 0;
            fseek(fp, pos, SEEK_SET);
            fwrite(&aux, sizeof(TA), 1, fp);
            fclose(fp);
            return cr;
        }
        if (aux.prox == -1)
        {
            fclose(fp);
            return cr;
        }
        pos = aux.prox;
    }
}

void insere(char *hash, char *dados, int n, int mat, float cr)
{
    FILE *fph = fopen(hash, "rb+");
    if (!fph)
        exit(1);
    int pos;
    int h = hash_function(mat, n);
    fseek(fph, h * sizeof(int), SEEK_SET);
    fread(&pos, sizeof(int), 1, fph);
    int ant;
    int prim_pos_livre;
    ant = prim_pos_livre = -1;
    FILE *fpd = fopen(dados, "rb+");
    if (!fpd)
    {
        fclose(fph);
        exit(1);
    }
    TA aux;
    while (pos != -1)
    {
        fseek(fpd, pos, SEEK_SET);
        fread(&aux, sizeof(TA), 1, fpd);
        if (aux.mat == mat)
        {
            aux.cr = cr;
            aux.status = 1;
            fseek(fpd, pos, SEEK_SET);
            fwrite(&aux, sizeof(TA), 1, fpd);
            fclose(fpd);
            fclose(fph);
            return;
        }
        if ((!aux.status) && (prim_pos_livre == -1))
            prim_pos_livre = pos;
        ant = pos;
        pos = aux.prox;
    }
    if (prim_pos_livre == -1)
    {
        aux.mat = mat;
        aux.cr = cr;
        aux.prox = -1;
        aux.status = 1;
        fseek(fpd, 0, SEEK_END);
        pos = ftell(fpd);
        fwrite(&aux, sizeof(TA), 1, fpd);
        if (ant != -1)
        {
            fseek(fpd, ant, SEEK_SET);
            fread(&aux, sizeof(TA), 1, fpd);
            aux.prox = pos;
            fseek(fpd, ant, SEEK_SET);
            fwrite(&aux, sizeof(TA), 1, fpd);
        }
        else
        {
            fseek(fph, h * sizeof(int), SEEK_SET);
            fwrite(&pos, sizeof(int), 1, fpd);
        }
        fclose(fpd);
        fclose(fph);
        return;
    }
    fseek(fpd, prim_pos_livre, SEEK_SET);
    fread(&aux, sizeof(TA), 1, fpd);
    aux.mat = mat;
    aux.cr = cr;
    aux.status = 1;
    fseek(fpd, prim_pos_livre, SEEK_SET);
    fwrite(&aux, sizeof(TA), 1, fpd);
    fclose(fpd);
    fclose(fph);
    return;
}

void imprime(char *hash, char *dados, int n)
{
    FILE *fp = fopen(hash, "rb");
    if (!fp)
        exit(1);
    int vet[n];
    fread(&vet, sizeof(int), n, fp); // ler todos as n posições no hash
    fclose(fp);

    fp = fopen(dados, "rb");
    if (!fp)
        exit(1);
    int pos;
    TA x;
    for (int i = 0; i < n; ++i)
    {
        if (vet[i] != -1)
            printf("%d:\n", i);

        int p = vet[i]; // current position
        while (p != -1)
        {
            fseek(fp, p, SEEK_SET);
            pos = ftell(fp);
            fread(&x, sizeof(TA), 1, fp);
            printf("$%d: matricula: %d\tcr: %f\tstatus: %d\tprox_end: $%d\n", pos, x.mat, x.cr, x.status, x.prox);
            p = x.prox;
        }
    }
    fclose(fp);
}