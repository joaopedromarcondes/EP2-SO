#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcula_tempo_medio(int n, FILE* saida_final) {
    int quantida_de_vezes = 30;
    FILE *arquivo;

    // Abrir o arquivo para inicializar
    arquivo = fopen("saida.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    fclose(arquivo);

    // Criar o comando para execução
    char aux1[100], aux2[150];
    sprintf(aux1, "time -o saida.txt -f \"%%e\" -a ./a.out entrada.txt saida.txt %d", n);
    printf("%s\n", aux1);
    
    // Rodar o comando `system()` quantida_de_vezes vezes
    int i;
    for (i = 0; i < quantida_de_vezes; i++) {
        system(aux1); // Executa o comando
    }

    double soma = 0;
    char linha[100];

    // Abrir o arquivo para ler os tempos
    arquivo = fopen("saida.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Ler os tempos do arquivo
    double a;
    while (fscanf(arquivo, "%lf", &a) != EOF) {
        soma += a;
    }

    double res = soma / quantida_de_vezes;
    fprintf(saida_final, "Cores: %d\n", n);
    fprintf(saida_final, "Média final: %.2f\n", res);
    printf("\nMédia final: %.2f\n\n", res);

    // Fechar o arquivo
    fclose(arquivo);

    return 0; // Retorno de sucesso
}


int main() {
    FILE* saida_final;

    saida_final = fopen("saida_aux.txt", "w");
    if (saida_final == NULL) {
        perror("Erro ao abrir o arquivo\n");
        return 1;
    }

    int i;
    for (i = 1; i < 21; i++) {
        calcula_tempo_medio(i, saida_final);
    }

    fclose(saida_final);
}