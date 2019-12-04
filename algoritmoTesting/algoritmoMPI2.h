#pragma once

#include <stdio.h>
#include <time.h>
#include <mpi.h>

#include "util.h"

//Cabeçalho das funções
void executarAlgoritmoMPI(unsigned char *img, int total_size);

//Main
int mpi2(char* imageName, int argc, char *argv[]){
	// Iniciando MPI
	int rank, num_procs;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	// Carregando imagem se é raiz
	unsigned char *img = NULL;
	int largura, altura, canais;
	unsigned char *partial_img;
	if(rank == 0){
		img = carregarImagem(imageName, img, &largura, &altura, &canais);
	}
	int size_per_proc = (largura*altura*canais)/num_procs;

	// Compartilhando a informação do tamanho para outros processos
	MPI_Bcast(&size_per_proc, 1, MPI_INT, 0, MPI_COMM_WORLD);

	fflush(stdout);

	// Gerando imagem parcial
	partial_img = malloc(sizeof(unsigned char)*size_per_proc);

	// Preparando contagem
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start); 

	// Distribuindo pedaços da imagem para os processos
	MPI_Scatter((void *)img,
		size_per_proc,
		MPI_UNSIGNED_CHAR,
		(void *)partial_img,
		size_per_proc,
		MPI_UNSIGNED_CHAR,
		0,
		MPI_COMM_WORLD
	);

	fflush(stdout);

	// Barreira para os processos
	MPI_Barrier(MPI_COMM_WORLD);
	
	// Execução do algoritmo
	executarAlgoritmoMPI2(partial_img, size_per_proc);

	// Reunindo cálculos dos processos
	MPI_Gather(
		(void *)partial_img,
		size_per_proc,
		MPI_UNSIGNED_CHAR,
		(void *)img,
		size_per_proc,
		MPI_UNSIGNED_CHAR,
		0,
		MPI_COMM_WORLD
	);

	// Finalizando contagem
	clock_gettime(CLOCK_MONOTONIC, &end); 
	double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 

    // Esperando processo raiz
    if(rank == 0){
    	// Liberando liberando imagem
    	liberarImagem(img);

    	// Escrevendo resultados
    	char fileName[40] = "MPI_stats_";
		strcat(fileName, imageName);
		strcat(fileName, "_2np.txt");
    	FILE * file;
    	file = fopen(fileName, "a");
    	fprintf(file, "%f\n", time_taken);
    	fclose(file);
    }
	
	// Liberando imagem parcial e finalizando MPI
	free(partial_img);
	MPI_Finalize();
}

//Função executa o algoritmo proposto no artigo
void executarAlgoritmoMPI2(unsigned char* img, int total_size){

	for(int i = 0; i < total_size; i++){
		img[i] = inverterBits(img[i]);
	}
}