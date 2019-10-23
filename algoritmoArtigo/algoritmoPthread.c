#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include "util.c"

#define NTHREADS 4
#define CACHELINESIZE 64
#define OFFSET (NTHREADS * CACHELINESIZE)

unsigned char *img;
int largura, altura, canais;

void *executarAlgoritmo(void *x);

//Main
int main(void){
	
	struct timespec start, end;

	unsigned char *img;

	char nomeImagem[300];
	

	printf("Digite o nome da imagem PNG (sem .png): ");
	scanf("%s", nomeImagem);

	img = carregarImagem(nomeImagem, img, &largura, &altura, &canais);

	pthread_t threads[NTHREADS];
	int thread_args[NTHREADS];
  	int rc;

  	//Relógio começa a contar quando o algoritmo começa
	clock_gettime(CLOCK_MONOTONIC, &start); 

  	for(int i = 0; i < NTHREADS; ++i){
  		thread_args[i] = i;
		
		rc = pthread_create(&threads[i], NULL, executarAlgoritmo, (void *) &thread_args[i]);
    }	

    //Aguardando as threads terminarem
	for(int i = 0; i < NTHREADS; ++i) {
    	rc = pthread_join(threads[i], NULL);
  	}

  	//Relógio termina de contar após o fim do algoritmo
	clock_gettime(CLOCK_MONOTONIC, &end); 
	double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 

	salvarImagem(nomeImagem, img, largura, altura, canais);

	printf("\n\n-- O algoritmo demorou %f segundos para ser executado.\n\n", time_taken);

	return 0;
}

//Função executa o algoritmo proposto no artigo
void *executarAlgoritmo(void *x){

	int tid = *((int *)x);

	int start = tid * CACHELINESIZE;
	int end = start + CACHELINESIZE;
	int totalSize = largura * altura * canais;
	int i;

	while(1){
		for(i = start; i < end; i++){
			img[i] = inverterBits(img[i]);
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

	return NULL;
}