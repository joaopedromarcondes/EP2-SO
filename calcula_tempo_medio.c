#include <stdio.h>
#include <stdlib.h>

int main() {
    int quantida_de_vezes = 20;
    FILE *arquivo;

    // Abrir o arquivo
    arquivo = fopen("saida.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    fclose(arquivo);


    int i;
    for (i = 0; i < quantida_de_vezes; i++) {
        system("time -o saida.txt -f \"%e\" -a ./a.out entrada.txt saida.txt 3");
    }
        
    
    double soma = 0;

    
    char linha[100];

    // Abrir o arquivo
    arquivo = fopen("saida.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }


    // Ler linha por linha
    char n1[100], n2[100], n3[100], n4[100], n5[100], n6[100];
    //fscanf(arquivo, "%s %s %s %s %s %s", n1, n2, n3, n4, n5, n6);
    int a, b;
    char l;
    while (fscanf(arquivo, "%d%c%d", &a, &l, &b) != -1) {
        soma += b;
    }
    double res = soma/quantida_de_vezes;
    printf("\nMédia final: %.2f\n\n", res);

    // Fechar o arquivo
    fclose(arquivo);
}