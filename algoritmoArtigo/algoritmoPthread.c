#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include "util.c"

#define NTHREADS 1

typedef struct parametros{
	int threadId;
	unsigned char* imagem;
	int largura;
	int altura;
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
  		PARAMETROS thread_args = {
  			.threadId = i,
  			.imagem = img,
  			.largura = largura,
  			.altura = altura
  		};
		//unsigned char* thread_args = img;
		printf("\n-Iniciando a thread %d\n", i);
		rc = pthread_create(&threads[i], NULL, executarAlgoritmo, (void *) &thread_args);
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

	PARAMETROS* params = (PARAMETROS*) x;

	//unsigned char *imgPointer = x;

	for(int i = 0; i < params->largura * params->altura; i++){
		*params->imagem = inverterBits(*params->imagem);
		params->imagem += 1;
		*params->imagem = inverterBits(*params->imagem);
		params->imagem += 1;
		*params->imagem = inverterBits(*params->imagem);
		params->imagem += 1;
	}

	printf("---- Algoritmo executado com sucesso!\n\n");

	return NULL;
}