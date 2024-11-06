#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int ch;
    unsigned char* dados;
} NO;

typedef struct {
    NO nos[MAX_SIZE];
    int tam;
} LISTA;

void swap(int i, int j, LISTA* l);
void mostra(LISTA* l);
void ordena(LISTA* l);
void quick_sort(LISTA* l, int inicio, int fim);
int particiona_random(LISTA* l, int inicio, int fim);
int particiona(LISTA* l, int inicio, int fim);
void mergeSort(LISTA* l, int left, int right);
void merge(LISTA* l, int left, int middle, int right);



void swap(int i, int j, LISTA* l) {
    NO aux;
    aux.ch = l->nos[i].ch;
    aux.dados = l->nos[i].dados;

    l->nos[i].ch = l->nos[j].ch;
    l->nos[i].dados = l->nos[j].dados;

    l->nos[j].ch = aux.ch;
    l->nos[j].dados = aux.dados;
}

void mergeSort(LISTA* l, int left, int right) {   
        
        if (left >= right)
            return;
        
        else {
            
            int middle = (left + right) / 2;
            mergeSort(l, left, middle);
            mergeSort(l, middle + 1, right);
    
            merge(l, left, middle, right);
        }
        
    }

void merge(LISTA* l, int left, int middle, int right) {
        
        // transfere os elementos entre left e right para um array auxiliar.
        LISTA* helper = (LISTA*) malloc(sizeof(LISTA));
        int i;
        for (i = left; i <= right; i++) {
            helper->nos[i] = l->nos[i];
        }
        helper->tam = l->tam;
        
        
        i = left;
        int j = middle + 1;
        int k = left;
        
        while (i <= middle && j <= right) {
            
            if (helper->nos[i].ch <= helper->nos[j].ch) {
                l->nos[k] = helper->nos[i];
                i++;
            } else {
                l->nos[k] = helper->nos[j];
                j++;
            }
            k++;    
            
        }
        
        // se a metade inicial não foi toda consumida, faz o append.
        while (i <= middle) {
            l->nos[k] = helper->nos[i];
            i++;
            k++;
        }
       
        // Não precisamos nos preocupar se a metade final foi 
        // toda consumida, já que, se esse foi o caso, ela já está
        // no array final.

    }







// particiona e retorna o índice do pivô
int particiona(LISTA* l, int inicio, int fim)
{
	int pivo, pivo_indice, i;
	
	pivo = l->nos[fim].ch; // o pivô é sempre o último elemento
	pivo_indice = inicio;
	
	for(i = inicio; i < fim; i++)
	{
		// verifica se o elemento é <= ao pivô
		if(l->nos[i].ch <= pivo)
		{
			// realiza a troca
			swap(i, pivo_indice, l);
			// incrementa o pivo_indice
			pivo_indice++;
		}
	}
	
	// troca o pivô
	swap(pivo_indice, fim, l);
	
	// retorna o índice do pivô
	return pivo_indice;
}

// escolhe um pivô aleatório para evitar o pior caso do quicksort
int particiona_random(LISTA* l, int inicio, int fim)
{
	// seleciona um número entre fim (inclusive) e inicio (inclusive)
	int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;
	
	// faz a troca para colocar o pivô no fim
	swap(pivo_indice, fim, l);
	// chama a particiona
	return particiona(l, inicio, fim);
}

void quick_sort(LISTA* l, int inicio, int fim)
{
	if(inicio < fim)
	{
		// função particionar retorna o índice do pivô
		int pivo_indice = particiona_random(l, inicio, fim);
		
		// chamadas recursivas quick_sort
		quick_sort(l, inicio, pivo_indice - 1);
		quick_sort(l, pivo_indice + 1, fim);
	}
}




void ordena(LISTA* l) {
    // Com essa variável é possível escolher qual operação fazer
    int i = 0;

    switch (i) {
    case 0:
        quick_sort(l, 0, l->tam-1);
        break;
    case 1:
        mergeSort(l, 0, l->tam-1);
        break;

    default:
        break;
    }
 
}

void mostra(LISTA* l) {
    int i;
    for (i = 0; i < l->tam; i++) {
        printf("%d\n", l->nos[i].ch);
    }
}


void inicializar_lista(FILE* entrada, LISTA* l) {
    int chave;
    l->tam = 0;
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
        fprintf(stderr, "Erro na passagem de parâmetros. Execute no formato: ./psort1458 <entrada> <saída> <threads>");
        return -1;
    }
    FILE* entrada = fopen(argv[1], "r");
    FILE* saida = fopen(argv[2], "w");
    int* num;
    while (fscanf(entrada, "%d", num) > 0) {
        printf("Olá, %d!\n", *num);
    }
    printf("\n"); */


    FILE * entrada = fopen("testes/10_registros_ordem_reversa.dat", "r");

    LISTA* l = (LISTA*) malloc(sizeof(LISTA));;
    inicializar_lista(entrada, l);
    
    mostra(l);
    ordena(l);
    mostra(l);


    if (fclose(entrada))
        perror("fclose error");

    return 0;
}