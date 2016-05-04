#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned long int DWORD;

typedef struct {
	BYTE id[1];
	WORD offset;
	WORD width;
	WORD height;
	BYTE bpp;
	int size;
	BYTE *head;
	float *pixel;
}GS;

GS* getBMP(char* name) {
	GS* INPUT;
	FILE* file;
	int i, j, w, W;

	// Open the input file
	if((file = fopen(name, "rb")) == NULL) {
		printf("Couldn't open given file.\n");
		exit(1);
	}

	// Allocate memory for the structure GS
	if((INPUT = (GS*)malloc(sizeof(GS))) == NULL) {
		printf("Couldn't allocate memory for GS.\n");
		exit(1);
	}

	fread(INPUT->id, 2, 1, file);
	fseek(file, 10, SEEK_SET);
	fread(&INPUT->offset, 2, 1, file);
	fseek(file, 18, SEEK_SET);
	fread(&INPUT->width, 2, 1, file);
	fseek(file, 22, SEEK_SET);
	fread(&INPUT->height, 2, 1, file);
	fseek(file, 28, SEEK_SET);
	fread(&INPUT->bpp, 1, 1, file);
	fseek(file, 34, SEEK_SET);
	fread(&INPUT->size, 4, 1, file);

	// Corroborate valid file
	if((INPUT->id[0] != 'B') || (INPUT->id[1] != 'M')) {
		printf("Invalid format type.\n");
		exit(1);
	}

	// Allocate memory for the header
	if((INPUT->head = (BYTE*)malloc(INPUT->offset)) == NULL) {
		printf("Couldn't allocate memory for the header.\n");
		exit(1);
	}

	// Allocate memory for the image
	if((INPUT->pixel = (float*)calloc(INPUT->width * INPUT->height, sizeof(float))) == NULL) {
		printf("Couldn't allocate memory for the image.\n");
		exit(1);
	}

	// Read the header
	rewind(file);
	fread(INPUT->head, 1078, 1, file);

	// Read the image
	w = INPUT->width;
	W = INPUT->size / INPUT->height;
	fseek(file, INPUT->offset, SEEK_SET);
	for(i = 0; i < INPUT->height; i++) {
		for(j = 0; j < INPUT->width; j++)
			INPUT->pixel[i * w + j] = (float)fgetc(file);
		if(w != W)
			for(j = 0; j < W - w; j++)
				fgetc(file);
	}

	fclose(file);
	INPUT->size = INPUT->width * INPUT->height;
	return INPUT;
}

#endif
