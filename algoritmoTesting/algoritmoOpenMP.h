#pragma once

#include <stdio.h>
#include <time.h>

#include "util.h"

//Cabeçalho das funções
void executarAlgoritmoOpenMP(unsigned char *img, int largura, int altura, int canais);

//Main
void openMP(char* imageName){
	// Carregando imagem
	unsigned char *img;
	int largura, altura, canais;
	img = carregarImagem(imageName, img, &largura, &altura, &canais);

	// Preparando contagem
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start); 

	// Executando algoritmo
	executarAlgoritmoOpenMP(img, largura, altura, canais);
	
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
	strcat(fileName, ".txt");
	FILE * file;
	file = fopen(fileName, "a");
	fprintf(file, "%f\n", time_taken);
	fclose(file);
}

//Função executa o algoritmo proposto no artigo
void executarAlgoritmoOpenMP(unsigned char* img, int largura, int altura, int canais){

	unsigned char *imgPointer = img;
	int totalSize = largura*altura*canais;

	#pragma omp parallel for num_threads(2)
	for(int i = 0; i < totalSize; i++){
		img[i] = inverterBits(img[i]);
	}
}