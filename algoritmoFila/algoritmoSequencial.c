#include <stdio.h>
#include <time.h>

#include "util.c"

//Cabeçalho das funções
void executarAlgoritmo(unsigned char *img, int largura, int altura, int canais);

//Main
int main(void){

	unsigned char *img;
	unsigned char *img2;
	int largura, altura, canais;
	char nomeImagem[300];

	struct timespec start, end;

	//printf("Digite o nome da imagem PNG (sem .png): ");
	//scanf("%s", nomeImagem);

	img = carregarImagem("wallpaper16k", img, &largura, &altura, &canais);
	img2 = carregarImagem("wallpaper16k", img2, &largura, &altura, &canais);

	clock_gettime(CLOCK_MONOTONIC, &start); 

	executarAlgoritmo(img, largura, altura, canais);
	executarAlgoritmo(img2, largura, altura, canais);
	
	clock_gettime(CLOCK_MONOTONIC, &end); 
	double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 

	salvarImagem("imagem", img, largura, altura, canais);
	salvarImagem("imagem2", img2, largura, altura, canais);

	printf("\n\n--O algoritmo demorou %f segundos para ser executado.\n\n", time_taken);

	FILE * file;
    	file = fopen("Sequencial_stats.txt", "a");

    	fprintf(file, "%f\n", time_taken);

    	fclose(file);

	return 0;
}

//Função executa o algoritmo proposto no artigo
void executarAlgoritmo(unsigned char* img, int largura, int altura, int canais){

	unsigned char *imgPointer = img;
	int totalSize = largura*altura*canais;

	for(int i = 0; i < totalSize; i++){
		img[i] = inverterBits(img[i]);
	}
}