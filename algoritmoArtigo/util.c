#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image/stb_image_write.h"

unsigned char* carregarImagem(char* nomeImagem, unsigned char *img, int *largura, int *altura, int *canais);
void salvarImagem(char* nomeImagem, unsigned char *img, int largura, int altura, int canais);
unsigned char inverterBits(unsigned char pixel);

//Função carrega a imagem e armazena no vetor img.
unsigned char* carregarImagem(char* nomeImagem, unsigned char *img, int *largura, int *altura, int *canais){
	char caminho[350];
	sprintf(caminho, "../images/%s.png", nomeImagem);
	printf("%s\n", caminho);
    img = stbi_load(caminho, largura, altura, canais, 0);
 	if(img == NULL) {
 		printf("Erro ao carregar a imagem\n");
 		exit(1);
 	}
	printf("-- Carregada imagem com largura de %dpx, altura de %dpx e %d canais\n", *largura, *altura, *canais);
	return img;
}

//Função salva a imagem nova utilizando o vetor img 
void salvarImagem(char* nomeImagem, unsigned char *img, int largura, int altura, int canais){
	char caminho[350];
	sprintf(caminho, "%sEncriptedInThreads.png", nomeImagem);
	printf("-- Salvando nova imagem como %sEncripted.png\n", nomeImagem);
	stbi_write_png(caminho, largura, altura, canais, img, largura * canais);
	stbi_image_free(img);
	printf("---- Imagem salva com sucesso!\n\n");
}

//Recebe um char e inverte a posição dos 4 MSB com os 4 LSB
unsigned char inverterBits(unsigned char pixel){
	unsigned char pixel2 = pixel;
	pixel = pixel << 4;
	pixel2 = pixel2 >> 4;

	return pixel + pixel2;
}