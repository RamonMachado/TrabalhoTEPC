#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include "util.c"

#define NTHREADS 2
#define CACHELINESIZE 64

typedef struct parametros{
	int threadId;
	unsigned char* imagem;
	int largura;
	int altura;
	int canais;
} PARAMETROS;

void *executarAlgoritmo(void *x);

//Main
int main(void){
	
	unsigned char *img;
	char nomeImagem[300];
	int largura, altura, canais;

	printf("Digite o nome da imagem PNG (sem .png): ");
	scanf("%s", nomeImagem);

	img = carregarImagem(nomeImagem, img, &largura, &altura, &canais);

	pthread_t threads[NTHREADS];
  	int rc;

  	//Relógio começa a contar quando o algoritmo começa
	clock_t inicio = clock();

  	for(int i = 0; i < NTHREADS; ++i){
  		PARAMETROS* params = (PARAMETROS*) malloc(sizeof(PARAMETROS));
  		  	params->threadId = i;
  			params->imagem = img;
  			params->largura = largura;
  			params->altura = altura;
  			params->canais = canais;
		
		//unsigned char* thread_args = img;
		printf("\n-Iniciando a thread %d\n", i);
		rc = pthread_create(&threads[i], NULL, executarAlgoritmo, (void *) params);
    }	

    //Aguardando as threads terminarem
	for(int i = 0; i < NTHREADS; ++i) {
    	rc = pthread_join(threads[i], NULL);
  	}

  	//Relógio termina de contar após o fim do algoritmo
	clock_t fim = clock();
	double tempo = ((double) fim - inicio) / CLOCKS_PER_SEC;

	salvarImagem(nomeImagem, img, largura, altura, canais);

	printf("\n\n-- O algoritmo demorou %f segundos para ser executado.\n\n", tempo);

	return 0;
}

//Função executa o algoritmo proposto no artigo
void *executarAlgoritmo(void *x){

	printf("-- Executando Algoritmo de Encriptação / Desencriptação\n");

	PARAMETROS *params = (PARAMETROS*) x;
	printf("Thread %d\n", params->threadId);

	//unsigned char *imgPointer = x;
	int start = params->threadId * CACHELINESIZE;
	int end = start + CACHELINESIZE;
	int i = start;

	while(i < params->largura * params->altura * params->canais){
		//printf("i = %d | thread = %d\n", i, params->threadId);
		params->imagem[i] = inverterBits(params->imagem[i]);
		i++;
		if(i == end){
			start = start + (NTHREADS * CACHELINESIZE);
			end = start + CACHELINESIZE;
			i = start;
		}
	}

	free(params);
	printf("---- Algoritmo executado com sucesso!\n\n");

	return NULL;
}