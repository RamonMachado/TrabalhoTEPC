#pragma once

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

#include "util.h"

#define NTHREADS2 2
#define NTHREADS4 4
#define NTHREADS8 8
#define CACHELINESIZE 64
#define OFFSET2 (NTHREADS2 * CACHELINESIZE)
#define OFFSET4 (NTHREADS4 * CACHELINESIZE)
#define OFFSET8 (NTHREADS8 * CACHELINESIZE)
#define NUM_PIXELS 8294400 //4K (actually  8272800)
//#define NUM_PIXELS 33177600 //8K
//#define NUM_PIXELS 132710400 //16K

unsigned char *img;
int largura, altura, canais;
int totalSize;
int sizePerThread;

void *executarAlgoritmoPthread(void *x);
//Main
void pthreads2(char* imageName){
	// Carregando imagem
	img = carregarImagem(imageName, img, &largura, &altura, &canais);

  	//Relógio começa a contar quando o algoritmo começa
  	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	// Começando o pthreads
	pthread_t threads[NTHREADS2];
	int thread_args[NTHREADS2];
  	int rc;
	totalSize = largura * altura * canais;
	sizePerThread = totalSize/NTHREADS2; 

  	for(int i = 0; i < NTHREADS2; ++i){
  		thread_args[i] = i;
		
		rc = pthread_create(&threads[i], NULL, executarAlgoritmoPthread, (void *) &thread_args[i]);
    }	

    //Aguardando as threads terminarem
	for(int i = 0; i < NTHREADS2; ++i) {
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
	strcat(fileName, "_2thread.txt");
	FILE * file;
	file = fopen(fileName, "a");
	fprintf(file, "%f\n", time_taken);
	fclose(file);
}

//Main
void pthreads4(char* imageName){
	// Carregando imagem
	img = carregarImagem(imageName, img, &largura, &altura, &canais);

  	//Relógio começa a contar quando o algoritmo começa
  	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	// Começando o pthreads
	pthread_t threads[NTHREADS4];
	int thread_args[NTHREADS4];
  	int rc;
	totalSize = largura * altura * canais;
	sizePerThread = totalSize/NTHREADS4; 

  	for(int i = 0; i < NTHREADS4; ++i){
  		thread_args[i] = i;
		
		rc = pthread_create(&threads[i], NULL, executarAlgoritmoPthread, (void *) &thread_args[i]);
    }	

    //Aguardando as threads terminarem
	for(int i = 0; i < NTHREADS4; ++i) {
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
	strcat(fileName, "_4thread.txt");
	FILE * file;
	file = fopen(fileName, "a");
	fprintf(file, "%f\n", time_taken);
	fclose(file);
}

//Main
void pthreads8(char* imageName){
	// Carregando imagem
	img = carregarImagem(imageName, img, &largura, &altura, &canais);

  	//Relógio começa a contar quando o algoritmo começa
  	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	// Começando o pthreads
	pthread_t threads[NTHREADS8];
	int thread_args[NTHREADS8];
  	int rc;
	totalSize = largura * altura * canais;
	sizePerThread = totalSize/NTHREADS8; 

  	for(int i = 0; i < NTHREADS8; ++i){
  		thread_args[i] = i;
		
		rc = pthread_create(&threads[i], NULL, executarAlgoritmoPthread, (void *) &thread_args[i]);
    }	

    //Aguardando as threads terminarem
	for(int i = 0; i < NTHREADS8; ++i) {
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
	strcat(fileName, "_8thread.txt");
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