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

	printf("Digite o nome da imagem PNG (sem .png): ");
	scanf("%s", nomeImagem);

	img = carregarImagem(nomeImagem, img, &largura, &altura, &canais);

	clock_t inicio = clock();
	executarAlgoritmo(img, largura, altura);
	clock_t fim = clock();
	double tempo = ((double) fim - inicio) / CLOCKS_PER_SEC;

	salvarImagem(nomeImagem, img, largura, altura, canais);

	printf("\n\n--O algoritmo demorou %f segundos para ser executado.\n\n", tempo);

	return 0;
}

//Função executa o algoritmo proposto no artigo
void executarAlgoritmo(unsigned char* img, int largura, int altura){

	printf("-- Executando Algoritmo de Encriptação / Desencriptação\n");

	unsigned char *imgPointer = img;

	for(int i = 0; i < largura*altura; i++){
		*imgPointer = inverterBits(*imgPointer);
		imgPointer += 1;
		*imgPointer = inverterBits(*imgPointer);
		imgPointer += 1;
		*imgPointer = inverterBits(*imgPointer);
		imgPointer += 1;
	}

	printf("---- Algoritmo executado com sucesso!\n");
}