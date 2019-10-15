#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include "util.c"

#define NTHREADS 4
#define CACHELINESIZE 64
#define OFFSET 4 * 64

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

	PARAMETROS *params = (PARAMETROS*) x;

	int start = params->threadId * CACHELINESIZE;
	int end = start + CACHELINESIZE;
	int i = start;
	int totalSize = params->largura * params->altura * params->canais;

	while(1){
		for(i = start; i < end; i++){
			params->imagem[i] = inverterBits(params->imagem[i]);
		}
		start = start + OFFSET;
		if(start > totalSize){
			break;
		}
		end = start + CACHELINESIZE;
		if(end > totalSize){
			end = totalSize;
		}
	}

	free(params);

	return NULL;
}