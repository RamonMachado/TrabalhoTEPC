#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <mpi.h>

#include "util.h"
#include "algoritmoSequencial.h"
#include "algoritmoPthread.h"
#include "algoritmoOpenMP.h"
#include "algoritmoMPI.h"

int main(int argc, char *argv[]) {
	// Nome da imagem 4k
	char image4k[40] = "wallpaper4k";

	sequencial(image4k);
	pthreads(image4k);
	openMP(image4k);
	//mpi(image4k, argc, argv);
	
	return 0;
}