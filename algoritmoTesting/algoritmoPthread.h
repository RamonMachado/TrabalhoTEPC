#pragma once

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

#include "util.h"

#define NTHREADS 2
#define CACHELINESIZE 64
#define OFFSET (NTHREADS * CACHELINESIZE)
#define NUM_PIXELS 8294400 //4K (actually  8272800)
//#define NUM_PIXELS 33177600 //8K
//#define NUM_PIXELS 132710400 //16K

unsigned char *img;
int largura, altura, canais;
int totalSize;
int sizePerThread;

void *executarAlgoritmoPthread(void *x);

//Main
void pthreads(char* imageName){
	// Carregando imagem
	img = carregarImagem(imageName, img, &largura, &altura, &canais);

  	//Relógio começa a contar quando o algoritmo começa
  	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	// Começando o pthreads
	pthread_t threads[NTHREADS];
	int thread_args[NTHREADS];
  	int rc;
	totalSize = largura * altura * canais;
	sizePerThread = totalSize/NTHREADS; 

  	for(int i = 0; i < NTHREADS; ++i){
  		thread_args[i] = i;
		
		rc = pthread_create(&threads[i], NULL, executarAlgoritmoPthread, (void *) &thread_args[i]);
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

	liberarImagem(img);

	// Escrevendo resultados
	char fileName[40] = "Pthread_stats_";
	strcat(fileName, imageName);
	strcat(fileName, ".txt");
	FILE * file;
	file = fopen(fileName, "a");
	fprintf(file, "%f\n", time_taken);
	fclose(file);
}

//Função executa o algoritmo proposto no artigo
void *executarAlgoritmoPthread(void *x){

	int tid = *((int *)x);

	int start = tid * NUM_PIXELS;
	int end = start + NUM_PIXELS;
	if(end > NUM_PIXELS){
		end = NUM_PIXELS;
	}
	int i;

	for(i = start; i < end; i++){
		img[i] = inverterBits(img[i]);
	}

	return NULL;
}