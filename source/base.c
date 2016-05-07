#include "base.h"
#include <stdio.h>
#include <stdlib.h>


/* Reads an image from a file and keeps it in the execution memory. */
GS* getBMP(char* name) {
	GS* INPUT;
	FILE* file;
	int i, j, width, n_width;

	/* Open the input file */
	if((file = fopen(name, "rb")) == NULL) {
		printf("Couldn't open given file.\n");
		exit(1);
	}

	/* Allocate memory for the structure GS */
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

	/* Corroborate valid file */
	if((INPUT->id[0] != 'B') || (INPUT->id[1] != 'M')) {
		printf("Invalid format type.\n");
		exit(1);
	}

	/* Allocate memory for the header */
	if((INPUT->head = (BYTE*)malloc(INPUT->offset)) == NULL) {
		printf("Couldn't allocate memory for the header.\n");
		exit(1);
	}

	/* Allocate memory for the image */
	if((INPUT->pixel = (float*)calloc(INPUT->width * INPUT->height, sizeof(float))) == NULL) {
		printf("Couldn't allocate memory for the image.\n");
		exit(1);
	}

	/* Read the header */
	rewind(file);
	fread(INPUT->head, 1078, 1, file);

	/* Read the image */
	width = INPUT->width;
	n_width = INPUT->size / INPUT->height;
	fseek(file, INPUT->offset, SEEK_SET);
	for(i = 0; i < INPUT->height; i++) {
		for(j = 0; j < INPUT->width; j++)
			INPUT->pixel[i * width + j] = (float)fgetc(file);
		if(width != n_width)
			for(j = 0; j < (n_width - width); j++)
				fgetc(file);
	}

	fclose(file);
	INPUT->size = INPUT->width * INPUT->height;
	return INPUT;
}


/* Writes an image from the execution memory to the disk. */
void putBMP(char* name, GS* INPUT) {
	FILE* file;
	int i, j, temp, offset, n_width, ZERO = 0;

	/* Create new file */
	if((file = fopen(name, "w+b")) == NULL) {
		printf("Couldn't open the file.\n");
		exit(1);
	}

	/* For convenction, the width must be divisible by 4; check if the condition is met. */
	offset = INPUT->width % 4;
	n_width = (offset)? (INPUT->width + (4 - offset)): (INPUT->width);

	/* Check the header. */
	if(INPUT->head) {
		INPUT->size = (n_width * INPUT->height);
		fwrite(INPUT->head, 1078, 1, file);
	}

	/* Generate header. */
	else {
		fputc('B', file);
		fputc('M', file);
		temp = n_width * INPUT->height + 1078;
		fwrite(&temp, 4, 1, file);
		fwrite(&ZERO, 4, 1, file);
		temp = 1078;
		fwrite(&temp, 4, 1, file);
		temp = 40;
		fwrite(&temp, 4, 1, file);
		temp = INPUT->width;
		fwrite(&temp, 4, 1, file);
		temp = INPUT->height;
		fwrite(&temp, 4, 1, file);
		temp = 1;
		fwrite(&temp, 2, 1, file);
		temp = 8;
		fwrite(&temp, 2, 1, file);
		temp = 0;
		fwrite(&temp, 4, 1, file);
		temp = (n_width * INPUT->height);
		fwrite(&temp, 4, 1, file);
		temp = 0;
		fwrite(&temp, 4, 1, file);
		fwrite(&temp, 4, 1, file);
		temp = 256;
		fwrite(&temp, 4, 1, file);
		temp = 0;
		fwrite(&temp, 4, 1, file);

		/* Write palette. */
		for(temp = 0; temp < 256; temp++) {
			for(i = 0; i < 3; i++)
				fwrite(&temp, 1, 1, file);
			fwrite(&ZERO, 1, 1, file);
		}
	}

	/* Write bitmap. */
	for(i = 0; i < INPUT->height; i++)
		for(j = 0; j < n_width; j++) {
			if(j > (INPUT->width - 1))
				fputc(0, file);
			else
				fputc(((BYTE)INPUT->pixel[i * INPUT->width + j]), file);
		}

	fclose(file);
}


/* Generates a new image with the given dimensions (the default intensity value is zero). */
GS* newBMP(unsigned int height, unsigned int width) {
	GS* INPUT;
	int ONE = 1;

	/* Allocate memory for the structure. */
	if((INPUT = (GS*)calloc(ONE, sizeof(GS))) == NULL) {
		printf("Couldn't allocate memory for the structure GS.\n");
		exit(1);
	}

	/* Set the dimensions of the image with the given parameters. */
	INPUT->width = width;
	INPUT->height = height;
	INPUT->size = width * height;

	/* Allocate memory for the image. */
	if((INPUT->pixel = (float*)calloc(INPUT->size, sizeof(float))) == NULL) {
		printf("Couldn't allocate memory for the image.\n");
		exit(1);
	}

	INPUT->head = NULL;

	return INPUT;
}


/* Free the memory occupied by an image. */
void freeBMP(GS* INPUT) {
	free(INPUT->head);
	free(INPUT->pixel);
	free(INPUT);
}
