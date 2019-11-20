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
	unsigned char *parcial_img;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	
	if(rank == 0){
		img = carregarImagem("gallardo", img, &largura, &altura, &canais);
	}

	int size_per_proc = (sizeof(img)/sizeof(img[0]))/num_procs;

	MPI_Scatter(
		img,
		size_per_proc,
		MPI_UNSIGNED_CHAR,
		parcial_img,
		size_per_proc,
		MPI_UNSIGNED_CHAR,
		0,
		MPI_COMM_WORLD
	);

	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC, &start); 

	size_t real_size_per_proc = sizeof(parcial_img)/sizeof(parcial_img[0]);

	executarAlgoritmo(img, real_size_per_proc);
	
	if(rank == 0){
		MPI_Gather(
			&parcial_img,
			real_size_per_proc,
			MPI_UNSIGNED_CHAR,
			&img,
			num_procs,
			MPI_UNSIGNED_CHAR,
			0,
			MPI_COMM_WORLD
		);
	}

	clock_gettime(CLOCK_MONOTONIC, &end); 
	double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 

	salvarImagem("gallardo", img, largura, altura, canais);

	printf("\n\n--O algoritmo demorou %f segundos para ser executado.\n\n", time_taken);

	return 0;
}

//Função executa o algoritmo proposto no artigo
void executarAlgoritmo(unsigned char* img, int total_size){

	for(int i = 0; i < total_size; i++){
		img[i] = inverterBits(img[i]);
	}
}