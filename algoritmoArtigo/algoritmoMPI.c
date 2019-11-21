#include <stdio.h>
#include <time.h>
#include <mpi.h>

#include "util.c"

//Cabeçalho das funções
void executarAlgoritmo(unsigned char *img, int total_size);

//Main
int main(int argc, char *argv[]){

	MPI_Init(&argc, &argv);

	unsigned char *img=NULL;
	int largura, altura, canais;
	int rank, num_procs;
	unsigned char *partial_img;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	if(rank == 0){
		img = carregarImagem("gallardo", img, &largura, &altura, &canais);
	}

	int size_per_proc = (largura*altura*canais)/num_procs;

	printf("Tamanho: %d\n", num_procs);

	fflush(stdout);

	partial_img = malloc(sizeof(unsigned char)*size_per_proc);

	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC, &start); 

	printf("Scatter start - %d\n", rank);

	MPI_Scatter(
		(void *)img,
		size_per_proc,
		MPI_UNSIGNED_CHAR,
		(void *)partial_img,
		size_per_proc,
		MPI_UNSIGNED_CHAR,
		0,
		MPI_COMM_WORLD
	);

	printf("Scatter finish - %d\n", rank);
	printf("%c - %d", partial_img[0], rank);
	fflush(stdout);
	MPI_Barrier(MPI_COMM_WORLD);
	executarAlgoritmo(partial_img, size_per_proc);
	
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

	clock_gettime(CLOCK_MONOTONIC, &end); 
	double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 

	salvarImagem("imagem", img, largura, altura, canais);

	printf("\n\n--O algoritmo demorou %f segundos para ser executado.\n\n", time_taken);

	free(partial_img);
	MPI_Finalize();
	return 0;
}

//Função executa o algoritmo proposto no artigo
void executarAlgoritmo(unsigned char* img, int total_size){

	for(int i = 0; i < total_size; i++){
		img[i] = inverterBits(img[i]);
	}
}