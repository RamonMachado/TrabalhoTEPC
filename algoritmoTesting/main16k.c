#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//#include <mpi.h>

#include "util.h"
#include "algoritmoSequencial.h"
#include "algoritmoPthread16k.h"
#include "algoritmoOpenMP.h"
//#include "algoritmoMPI.h"

int main(int argc, char *argv[]) {
	// Nome da imagem 16k
	char image[40] = "wallpaper16k";

	sequencial(image);
	pthreads2(image);
	pthreads4(image);
	pthreads8(image);
	openMP2(image);
	openMP4(image);
	openMP8(image);
	
	return 0;
}