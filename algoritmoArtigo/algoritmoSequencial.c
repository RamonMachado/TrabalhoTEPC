#include <stdio.h>
#include <time.h>

#include "util.c"

//Cabeçalho das funções
void executarAlgoritmo(unsigned char *img, int largura, int altura);

//Main
int main(void){

	unsigned char *img;
	int largura, altura, canais;
	char nomeImagem[300];

	struct timespec start, end;

	printf("Digite o nome da imagem PNG (sem .png): ");
	scanf("%s", nomeImagem);

	img = carregarImagem(nomeImagem, img, &largura, &altura, &canais);

	clock_gettime(CLOCK_MONOTONIC, &start); 

	executarAlgoritmo(img, largura, altura);
	
	clock_gettime(CLOCK_MONOTONIC, &end); 
	double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 

	salvarImagem(nomeImagem, img, largura, altura, canais);

	printf("\n\n--O algoritmo demorou %f segundos para ser executado.\n\n", time_taken);

	return 0;
}

//Função executa o algoritmo proposto no artigo
void executarAlgoritmo(unsigned char* img, int largura, int altura){

	unsigned char *imgPointer = img;

	for(int i = 0; i < largura*altura; i++){
		*imgPointer = inverterBits(*imgPointer);
		imgPointer += 1;
		*imgPointer = inverterBits(*imgPointer);
		imgPointer += 1;
		*imgPointer = inverterBits(*imgPointer);
		imgPointer += 1;
	}
}