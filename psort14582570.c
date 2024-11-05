#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct {
    int ch;
    unsigned char* dados;
} NO;

typedef struct {
    NO nos[MAX_SIZE];
    int tam;
} LISTA;


void swap(int i, int j, LISTA* l) {

}


void ordena(int* chaves, FILE* arq) {

}


void inicializar_lista(FILE* entrada, LISTA* l) {
    l = (LISTA*) malloc(sizeof(LISTA));
    l->tam = 0;

    int chave;
    unsigned char* dados;
    while (fread(&chave, 4, 1, entrada) > 0) {
        dados = (unsigned char*) malloc(sizeof(unsigned char)*96);
        fread(dados, 1, 96, entrada);
        l->nos[l->tam].ch = chave;
        l->nos[l->tam].dados = dados;
        l->tam++;
    }
}







int main(int argc, char *argv[]) {
    /* if (argc != 4) {
        fprintf(stderr, "Erro na passagem de parâmetros. Execute no formato: ./psort<nusp> <entrada> <saída> <threads>");
        return -1;
    }
    FILE* entrada = fopen(argv[1], "r");
    FILE* saida = fopen(argv[2], "w");
    int* num;
    while (fscanf(entrada, "%d", num) > 0) {
        printf("Olá, %d!\n", *num);
    }
    printf("\n"); */


    FILE * entrada = fopen("testes/10_registros_ja_ordenados.dat", "r");

    LISTA* l;
    inicializar_lista(entrada, l);

    if (fclose(entrada))
        perror("fclose error");

    return 0;
}