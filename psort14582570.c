#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <string.h>
//#include <sys/time.h>

#define MAX_SIZE 10000000

typedef struct {
    int ch;
    unsigned char* dados;
} NO;

typedef struct {
    NO nos[MAX_SIZE];
    int tam;
} LISTA;

typedef struct {
    LISTA* l;
    int ini;
    int fim;
} PAR;

void swap(int i, int j, LISTA* l);
void mostra(LISTA* l);
void ordena(LISTA* l, int n);
void quick_sort(LISTA* l, int inicio, int fim);
int particiona_random(LISTA* l, int inicio, int fim);
int particiona(LISTA* l, int inicio, int fim);
void mergeSort(LISTA* l, int left, int right);
void merge(LISTA* l, int left, int middle, int right);
void* func_aux(void* arg);



void swap(int i, int j, LISTA* l) {
    if (i == j)
        return;
    //printf("swap: %d %d\n", i, j);
    NO aux;
    aux.ch = l->nos[i].ch;
    aux.dados = l->nos[i].dados;

    l->nos[i].ch = l->nos[j].ch;
    l->nos[i].dados = l->nos[j].dados;

    l->nos[j].ch = aux.ch;
    l->nos[j].dados = aux.dados;
    //printf("Acabou swap!\n");
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

void quick_sort(LISTA* l, int inicio, int fim) {

	if(inicio < fim)
	{
		// função particionar retorna o índice do pivô
		int pivo_indice = particiona_random(l, inicio, fim);
        //printf("pivo: %d\n", pivo_indice);
		
		// chamadas recursivas quick_sort
		quick_sort(l, inicio, pivo_indice - 1);
        //printf("Funcionou o primeiro\n");
		quick_sort(l, pivo_indice + 1, fim);
        //printf("Funcionou o segundo\n");
	}
}

void* func_aux(void* arg) {
    PAR* par = (PAR*) arg;
    //printf("%d %d\n", par->ini, par->fim);
    quick_sort(par->l, par->ini, par->fim);
    //printf("Funcionou!\n");
    return NULL;
}



// n é o número de threads
void ordena(LISTA* l, int n) {
    // Com essa variável é possível escolher qual operação fazer

    int escolha = 2;
    pthread_t* threads = (pthread_t *) malloc(sizeof(pthread_t)*n);

    switch (escolha) {
    case 0:
        quick_sort(l, 0, l->tam-1);
        break;
    case 1:
        mergeSort(l, 0, l->tam-1);
        break;
    case 2:  
        PAR* par;
        int tam = l->tam/n;
        int i;
        for (i = 0; i < n; i++) {
            PAR* par = (PAR*) malloc(sizeof(PAR));
            par->l = l;
            par->ini = i*tam;
            par->fim = (i+1)*tam;
            if (i != 0) {
                par->ini++;
            } 
            if (n-1 == i) {
                par->fim = l->tam-1;
            }

            pthread_create(&threads[i], NULL, func_aux, (void*)(par));
        }

        for (i = 0; i < n; i++) {
            pthread_join(threads[i], NULL);
        } 
        for (i = 0; i < n-1; i++) {
            int meio = ((i+1)*tam);
            int fim = (i+2)*tam;
            if (n-2 == i) 
                fim = l->tam-1;
            merge(l, 0, meio, fim);
        } 
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

    // Obtendo o tamanho do arquivo
    fseek(entrada, 0, SEEK_END);
    long size = ftell(entrada);
    fseek(entrada, 0, SEEK_SET);

    // Mapeando o arquivo para a memória
    int fd = fileno(entrada);
    unsigned char* map = (unsigned char*) mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) {
        perror("Erro ao mapear o arquivo");
        return;
    }

    // Calculando o número total de nós que podem ser lidos
    size_t num_nos = size / (4 + 96); // 4 bytes para chave + 96 bytes para os dados

    // Alocando memória para todos os dados de uma vez
    unsigned char* dados = (unsigned char*) malloc(96 * num_nos * sizeof(unsigned char));
    if (dados == NULL) {
        perror("Erro ao alocar memória para dados");
        munmap(map, size);
        return;
    }

    // Processando os dados mapeados
    unsigned char* ptr = map;
    for (size_t i = 0; i < num_nos; ++i) {
        chave = *(int*)ptr;
        ptr += 4;  // Avança 4 bytes para o próximo inteiro (chave)
        
        // Copiando os dados diretamente para a memória já alocada
        memcpy(dados + i * 96, ptr, 96);
        ptr += 96;  // Avança 96 bytes para os próximos dados

        l->nos[i].ch = chave;
        l->nos[i].dados = dados + i * 96;  // Aponta para o local correto
        l->tam++;
    }

    // Desmapeando o arquivo após a leitura
    munmap(map, size);

}







int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Erro na passagem de parâmetros. Execute no formato: ./psort1458 <entrada> <saída> <threads>");
        return -1;
    }
    
    /* FILE* entrada = fopen(argv[1], "r");
    FILE* saida = fopen(argv[2], "w");
    int* num;
    while (fscanf(entrada, "%d", num) > 0) {
        printf("Olá, %d!\n", *num);
    }
    printf("\n"); */


    FILE * entrada = fopen("testes/5000000_aleat.dat", "r");

    LISTA* l = (LISTA*) malloc(sizeof(LISTA));;
    inicializar_lista(entrada, l);

    //struct timeval start, end;
    //long seconds, micros;
    //gettimeofday(&start, NULL);
    //mostra(l);
    long n =  atoi(argv[3]);
    ordena(l, n);
    //mostra(l);
    //gettimeofday(&end, NULL);

    // Calcula o tempo gasto
    //seconds = end.tv_sec - start.tv_sec;
    //micros = (end.tv_usec - start.tv_usec);

    // Converte para segundos e microsegundos
    //double elapsed = seconds + micros*1e-6;

    //printf("Tempo gasto: %.6f segundos\n", elapsed);

    if (fclose(entrada))
        perror("fclose error");

    return 0;
}