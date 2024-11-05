#include <stdio.h>
#include <stdlib.h>

void ordena(int* chaves, FILE* arq) {

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
    int a;
    fread(&a, 4, 1, entrada);
    printf("%d\n", a);
    unsigned char b[96];
    fread(&b, 1, 96, entrada);
    //printf("%d\n", b);
    int c;
    fread(&c, 4, 1, entrada);
    printf("%d\n", c);


    if (fclose(entrada))
        perror("fclose error");

    return 0;
}