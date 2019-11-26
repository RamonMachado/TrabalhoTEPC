#include <stdio.h>

int main(int argc, char** argv){

	FILE * file;
	file = fopen(argv[1], "r");
	float media = 0;
	float n;
	for(int i = 0; i < 5; i++){
		fscanf(file, "%f", &n);
		media += n;
	}
	
	media = media / 5;

	fclose(file);
	file = fopen(argv[1], "a");
	fprintf(file, "Media: %f\n", media);
	fclose(file);

	return 0;
}