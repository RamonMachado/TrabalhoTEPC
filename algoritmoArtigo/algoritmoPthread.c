#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image/stb_image_write.h"

#define NTHREADS 1

//Variáveis globais para facilitar o código
int largura, altura, canais;

//Cabeçalho das funções
unsigned char* carregarImagem(char* nomeImagem, unsigned char *img);
void salvarImagem(char* nomeImagem, unsigned char *img);
void *executarAlgoritmo(void *x);
unsigned char inverterBits(unsigned char pixel);


//Main
int main(void){
	
	unsigned char *img;
	char nomeImagem[300];

	printf("Digite o nome da imagem PNG (sem .png): ");
	scanf("%s", nomeImagem);

	img = carregarImagem(nomeImagem, img);

	pthread_t threads[NTHREADS];
  	int rc;

  	//Relógio começa a contar quando o algoritmo começa
	clock_t inicio = clock();

  	for(int i = 0; i < NTHREADS; ++i){
  	  unsigned char* thread_args = img;
      printf("\n-Iniciando a thread %d\n", i);
      rc = pthread_create(&threads[i], NULL, executarAlgoritmo, (void *) thread_args);
    }	

    //Aguardando as threads terminarem
	for(int i = 0; i < NTHREADS; ++i) {
    	rc = pthread_join(threads[i], NULL);
  	}

  	//Relógio termina de contar após o fim do algoritmo
	clock_t fim = clock();
	double tempo = ((double) fim - inicio) / CLOCKS_PER_SEC;

	salvarImagem(nomeImagem, img);

	printf("\n\n-- O algoritmo demorou %f segundos para ser executado.\n\n", tempo);

	return 0;
}


//Função carrega a imagem e armazena no vetor img.
unsigned char* carregarImagem(char* nomeImagem, unsigned char* img){
	char caminho[350];
	sprintf(caminho, "../images/%s.png", nomeImagem);
	printf("%s\n", caminho);
    img = stbi_load(caminho, &largura, &altura, &canais, 0);
 	if(img == NULL) {
 		printf("Erro ao carregar a imagem\n");
 		exit(1);
 	}
	printf("-- Carregada imagem com largura de %dpx, altura de %dpx e %d canais\n", largura, altura, canais);
	return img;
}

//Função salva a imagem nova utilizando o vetor img 
void salvarImagem(char* nomeImagem, unsigned char *img){
	char caminho[350];
	sprintf(caminho, "encripted-algoritmoPthread/%sEncripted.png", nomeImagem);
	printf("-- Salvando nova imagem como %sEncripted.png\n", nomeImagem);
	stbi_write_png(caminho, largura, altura, canais, img, largura * canais);
	stbi_image_free(img);
	printf("---- Imagem salva com sucesso!\n\n");
}

//Função executa o algoritmo proposto no artigo
void *executarAlgoritmo(void *x){

	printf("-- Executando Algoritmo de Encriptação / Desencriptação\n");

	unsigned char *imgPointer = x;

	for(int i = 0; i < largura*altura; i++){
		*imgPointer = inverterBits(*imgPointer);
		imgPointer += 1;
		*imgPointer = inverterBits(*imgPointer);
		imgPointer += 1;
		*imgPointer = inverterBits(*imgPointer);
		imgPointer += 1;
		printf("%d\n", i);
	}

	printf("---- Algoritmo executado com sucesso!\n\n");

	return NULL;
}

//Recebe um char e inverte a posição dos 4 MSB com os 4 LSB
unsigned char inverterBits(unsigned char pixel){
	unsigned char pixel2 = pixel;
	pixel = pixel << 4;
	pixel2 = pixel2 >> 4;

	return pixel + pixel2;
}

