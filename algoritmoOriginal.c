#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int largura, altura, canais;
unsigned char *img;

void carregarImagem();
void salvarImagem();
void executarAlgoritmo();
char inverterBits(char pixel);

int main(void){
	
	carregarImagem();

	executarAlgoritmo();

	salvarImagem();


	return 0;
}

void carregarImagem(){
    img = stbi_load("image.jpg", &largura, &altura, &canais, 0);
 	if(img == NULL) {
 		printf("Erro ao carregar a imagem\n");
 		exit(1);
 	}
	printf("Carregada imagem com largura de %dpx, altura de %dpx e %d canais\n", largura, altura, canais);
}

void salvarImagem(){
	stbi_write_png("imageNew.png", largura, altura, canais, img, largura * canais);
	stbi_image_free(img);
}

void executarAlgoritmo(){

	for(int x = 0; x < largura; x++){
		for (int y = 0; y < altura; y++){
			unsigned bytePorPixel = canais;
			unsigned char* pixelOffset = img + (y + altura * x) * bytePorPixel;
			unsigned char r = pixelOffset[0];
			pixelOffset[0] = inverterBits(r);
			unsigned char g = pixelOffset[1];
			pixelOffset[1] = inverterBits(g);
			unsigned char b = pixelOffset[2];
			pixelOffset[2] = inverterBits(b);
			unsigned char a = canais >= 4 ? pixelOffset[3] : 0xff;

			printf("(%d,%d) - R = %d, G = %d, B = %d, A = %d\n", x, y, r, g, b, a);
		}
	}
}


char inverterBits(char pixel){

	char pixel2 = pixel;
	pixel = pixel << 4;
	pixel2 = pixel2 >> 4;

	return pixel + pixel2;
}

