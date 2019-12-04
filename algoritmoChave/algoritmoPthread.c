#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include "util.c"

#define NTHREADS 2
//#define NUM_PIXELS 8294400 //4K
#define NUM_PIXELS 132710400 //16K

unsigned char *img;
unsigned char *imgChave;
int largura, altura, canais;
int totalSize;
int sizePerThread;

void *executarAlgoritmo(void *x);

//Main
int main(void){
	
	struct timespec start, end;

	char nomeImagem[300];
	

	//printf("Digite o nome da imagem PNG (sem .png): ");
	//scanf("%s", nomeImagem);


	img = carregarImagem("wallpaper16k", img, &largura, &altura, &canais);
	imgChave = carregarImagem("wallpaper16k", imgChave, &largura, &altura, &canais);

  	//Relógio começa a contar quando o algoritmo começa
	clock_gettime(CLOCK_MONOTONIC, &start);
	pthread_t threads[NTHREADS];
	int thread_args[NTHREADS];
  	int rc;
	totalSize = largura * altura * canais;
	sizePerThread = totalSize/NTHREADS; 

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

	int start = tid * sizePerThread;
	int end = start + sizePerThread;
	if(end > totalSize){
		end = totalSize;
	}
	int i;

	for(i = start; i < end; i++){
		img[i] = manipularBits(img[i], imgChave[i]);
	}

	return NULL;
}