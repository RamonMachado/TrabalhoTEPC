#pragma once

#include <stdio.h>
#include <time.h>

#include "util.h"

//Cabeçalho das funções
void executarAlgoritmoOpenMP2(unsigned char *img, int largura, int altura, int canais);
void executarAlgoritmoOpenMP4(unsigned char *img, int largura, int altura, int canais);
void executarAlgoritmoOpenMP8(unsigned char *img, int largura, int altura, int canais);

//Main
void openMP2(char* imageName){
	// Carregando imagem
	unsigned char *img;
	int largura, altura, canais;
	img = carregarImagem(imageName, img, &largura, &altura, &canais);

	// Preparando contagem
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start); 

	// Executando algoritmo
	executarAlgoritmoOpenMP2(img, largura, altura, canais);
	
	// Finalizando contagem 
	clock_gettime(CLOCK_MONOTONIC, &end); 
	double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 

	// Liberando imagem
	liberarImagem(img);

	// Escrevendo resultados
	char fileName[40] = "OpenMP_stats_";
	strcat(fileName, imageName);
	strcat(fileName, "_2thread.txt");
	FILE * file;
	file = fopen(fileName, "a");
	fprintf(file, "%f\n", time_taken);
	fclose(file);
}

//Função executa o algoritmo proposto no artigo
void executarAlgoritmoOpenMP2(unsigned char* img, int largura, int altura, int canais){

	unsigned char *imgPointer = img;
	int totalSize = largura*altura*canais;

	#pragma omp parallel for num_threads(2)
	for(int i = 0; i < totalSize; i++){
		img[i] = inverterBits(img[i]);
	}
}

//Main
void openMP4(char* imageName){
	// Carregando imagem
	unsigned char *img;
	int largura, altura, canais;
	img = carregarImagem(imageName, img, &largura, &altura, &canais);

	// Preparando contagem
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start); 

	// Executando algoritmo
	executarAlgoritmoOpenMP4(img, largura, altura, canais);
	
	// Finalizando contagem 
	clock_gettime(CLOCK_MONOTONIC, &end); 
	double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 

	// Liberando imagem
	liberarImagem(img);

	// Escrevendo resultados
	char fileName[40] = "OpenMP_stats_";
	strcat(fileName, imageName);
	strcat(fileName, "_4thread.txt");
	FILE * file;
	file = fopen(fileName, "a");
	fprintf(file, "%f\n", time_taken);
	fclose(file);
}

//Função executa o algoritmo proposto no artigo
void executarAlgoritmoOpenMP4(unsigned char* img, int largura, int altura, int canais){

	unsigned char *imgPointer = img;
	int totalSize = largura*altura*canais;

	#pragma omp parallel for num_threads(4)
	for(int i = 0; i < totalSize; i++){
		img[i] = inverterBits(img[i]);
	}
}

//Main
void openMP8(char* imageName){
	// Carregando imagem
	unsigned char *img;
	int largura, altura, canais;
	img = carregarImagem(imageName, img, &largura, &altura, &canais);

	// Preparando contagem
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start); 

	// Executando algoritmo
	executarAlgoritmoOpenMP8(img, largura, altura, canais);
	
	// Finalizando contagem 
	clock_gettime(CLOCK_MONOTONIC, &end); 
	double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 

	// Liberando imagem
	liberarImagem(img);

	// Escrevendo resultados
	char fileName[40] = "OpenMP_stats_";
	strcat(fileName, imageName);
	strcat(fileName, "_8thread.txt");
	FILE * file;
	file = fopen(fileName, "a");
	fprintf(file, "%f\n", time_taken);
	fclose(file);
}

//Função executa o algoritmo proposto no artigo
void executarAlgoritmoOpenMP8(unsigned char* img, int largura, int altura, int canais){

	unsigned char *imgPointer = img;
	int totalSize = largura*altura*canais;

	#pragma omp parallel for num_threads(8)
	for(int i = 0; i < totalSize; i++){
		img[i] = inverterBits(img[i]);
	}
}