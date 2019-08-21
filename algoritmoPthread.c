#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#define NTHREADS 2

//Variáveis globais para facilitar o código
int largura, altura, canais;
unsigned char *img;


//Cabeçalho das funções
void carregarImagem(char* nomeImagem);
void salvarImagem(char* nomeImagem);
void *executarAlgoritmo(void *x);
unsigned char inverterBits(unsigned char pixel);


//Main
int main(void){
	
	char nomeImagem[300];

	printf("Digite o nome da imagem PNG (sem .png): ");
	scanf("%s", nomeImagem);

	carregarImagem(nomeImagem);

	pthread_t threads[NTHREADS];
  	int thread_args[NTHREADS];
  	int rc;

  	//Relógio começa a contar quando o algoritmo começa
	clock_t inicio = clock();

  	for(int i = 0; i < NTHREADS; ++i){
      thread_args[i] = i;
      printf("\n-Iniciando a thread %d\n", i);
      rc = pthread_create(&threads[i], NULL, executarAlgoritmo, (void *) &thread_args[i]);
    }	

    //Aguardando as threads terminarem
	for(int i = 0; i < NTHREADS; ++i) {
    	rc = pthread_join(threads[i], NULL);
  	}

  	//Relógio termina de contar após o fim do algoritmo
	clock_t fim = clock();
	double tempo = ((double) fim - inicio) / CLOCKS_PER_SEC;

	salvarImagem(nomeImagem);

	printf("\n\n-- O algoritmo demorou %f segundos para ser executado.\n\n", tempo);

	return 0;
}


//Função carrega a imagem e armazena no vetor img.
void carregarImagem(char* nomeImagem){
	printf("\n-- Carregando imagem\n");
	char caminho[350];
	sprintf(caminho, "images/%s.png", nomeImagem);
    img = stbi_load(caminho, &largura, &altura, &canais, 0);
 	if(img == NULL) {
 		printf("Erro ao carregar a imagem\n");
 		exit(1);
 	}
	printf("---- Carregada imagem com largura de %dpx, altura de %dpx e %d canais!\n\n", largura, altura, canais);
}

//Função salva a imagem nova utilizando o vetor img 
void salvarImagem(char* nomeImagem){
	char caminho[350];
	sprintf(caminho, "encripted/%sEncripted.png", nomeImagem);
	printf("-- Salvando nova imagem como %sEncripted.png\n", nomeImagem);
	stbi_write_png(caminho, largura, altura, canais, img, largura * canais);
	stbi_image_free(img);
	printf("---- Imagem salva com sucesso!\n\n");
}

//Função executa o algoritmo proposto no artigo
void *executarAlgoritmo(void *x){

	int intervalo = (int) floor(altura/NTHREADS);
	printf("Intervalo:%d\n", intervalo);

	int tid;
	tid = *((int *) x);

	int alturaInicio = tid * intervalo;
	int alturaFim;

	if(tid == NTHREADS-1){
		alturaFim = altura;
	}
	else{
		alturaFim = alturaInicio + intervalo;
	}

	printf("-- Executando Algoritmo de Encriptação / Desencriptação\n");

	for(int x = 0; x < largura; x++){
		for (int y = alturaInicio; y < alturaFim; y++){
			unsigned bytePorPixel = canais;	
			unsigned char* pixelOffset = img + (y + altura * x) * bytePorPixel;
			unsigned char r = pixelOffset[0];
			pixelOffset[0] = inverterBits(r);
			unsigned char g = pixelOffset[1];
			pixelOffset[1] = inverterBits(g);
			unsigned char b = pixelOffset[2];
			pixelOffset[2] = inverterBits(b);
			//unsigned char a = canais >= 4 ? pixelOffset[3] : 0xff;

			//printf("Posição(%d,%d) - R = %d, G = %d, B = %d, A = %d\n", x, y, r, g, b, a);
		}
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

