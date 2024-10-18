#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Erro na passagem de parâmetros. Execute no formato: ./psort<nusp> <entrada> <saída> <threads>");
        return -1;
    }
    FILE* entrada = fopen(argv[1], "r");
    FILE* saida = fopen(argv[2], "w");
    int* num;
    while (fscanf(entrada, "%d", num) > 0) {
        printf("Olá, %d!\n", *num);
    }
    printf("\n");
    return 0;
}