#include "base.h"
#include "image.h"
#include <math.h>

/* Creates a test image with a vertical pattern. */
GS* verticalPattern(unsigned int height, unsigned int width) {
	int n;
	GS* INPUT = newBMP(height, width);
	for(n = 0; n < INPUT->size; n++)
		/* Sets all the pixels on the left side of the image to 255; the rest are set to 0. */
		INPUT->pixel[n] = ((n % INPUT->width) < (INPUT->width / 2))? 255: 0;
	return INPUT;
}

/* Creates a test image with a horizontal pattern. */
GS* horizontalPattern(unsigned int height, unsigned int width) {
	int n;
	GS* INPUT = newBMP(height, width);
	for(n = 0; n < INPUT->size; n++)
		/* Sets all the pixels on the top side of the image to 255; the rest are set to 0. */
		INPUT->pixel[n] = ((n / INPUT->width) >= (INPUT->height / 2))? 255: 0;
	return INPUT;
}

/* Creates a test image with a grid pattern. */
GS* gridPattern(unsigned int height, unsigned int width) {
	int n;
	GS* INPUT = newBMP(height, width);
	for(n = 0; n < INPUT->size; n++) {
	/* cookies: i = n / INPUT->width, j = n % INPUT->width; */
		INPUT->pixel[n] = ((((n / INPUT->width) % 2) == 0) && (((n % INPUT->width) % 2) != 0))? 255: 0;
	}
	return INPUT;
}

/* Copies an image from execution memory into a new one. */
GS* copy(GS* INPUT) {
	GS* OUTPUT = newBMP(INPUT->height, INPUT->width);
	int n;
	for(n = 0; n < INPUT->size; n++)
		OUTPUT->pixel[n] = INPUT->pixel[n];
	return OUTPUT;
}

/* Extracts a portion of an image (given the initial coordinates and the dimensions of the image) */
/* and creates a new image with it. */
GS* extract(const GS* INPUT, unsigned int x, unsigned int y, unsigned int height, unsigned int width) {
	GS* OUTPUT = newBMP(height, width);
	int i, j;
	for(i = 0; i < OUTPUT->height; i++)
		for(j = 0; j < OUTPUT->width; j++)
			OUTPUT->pixel[(OUTPUT->height - (i + 1)) * OUTPUT->width + j] = INPUT->pixel[(INPUT->height - (i + x)) * INPUT->width + (y + j)];
	return OUTPUT;
}

/* Paste an image on top of another (given both images and a initial coordinate). */
GS* replace(GS* INPUT_A, GS* INPUT_B, unsigned int x, unsigned int y) {
	GS* OUTPUT = copy(INPUT_A);
	int i, j;
	for(i = x; i < (INPUT_B->height + x); i++)
		for(j = y; j < (INPUT_B->width + y); j++)
			OUTPUT->pixel[(OUTPUT->height - i) * OUTPUT->width + j] = INPUT_B->pixel[(INPUT_B->height - (i - x)) * INPUT_B->width + (j - y)];
	return OUTPUT;
}

/* Rotates an image by 90 degrees (CCW) and creates a new image in memory with the result. */
GS* rotate90(const GS* INPUT) {
	GS* OUTPUT = newBMP(INPUT->width, INPUT->height);
	int i, j;
	for(i = 0; i < INPUT->height; i++)
		for(j = 0; j < INPUT->width; j++)
			OUTPUT->pixel[((OUTPUT->height - 1) - j) * OUTPUT->width + ((OUTPUT->width - 1) - i)] = INPUT->pixel[i * INPUT->width + j];
	return OUTPUT;
}

/* Rotates an image by 90 degrees (CW) and creates a new image in memory with the result. */
GS* rotate90n(const GS* INPUT) {
	GS* OUTPUT = newBMP(INPUT->width, INPUT->height);
	int i, j;
	for(i = 0; i < INPUT->height; i++)
		for(j = 0; j < INPUT->width; j++)
			OUTPUT->pixel[j * OUTPUT->width + i] = INPUT->pixel[i * INPUT->width + j];
	return OUTPUT;
}

/* Modifies the value of each pixel setting it to it's complement to 255. */
void negative(GS* INPUT) {
	int n;
	for(n = 0; n < INPUT->size; n++)
		INPUT->pixel[n] = 255 - INPUT->pixel[n];
}

/* Change the intensity of all the pixels according to the given threshold value. */
void binary(GS* INPUT, unsigned int threshold) {
	int n;
	for(n = 0; n < INPUT->size; n++)
		INPUT->pixel[n] = (INPUT->pixel[n] < threshold)? 0: 255;
}

/* Change the amount of possible intensity values within the image. */
void posterize(GS *INPUT, unsigned int levels) {
	int n;
	for(n = 0; n < INPUT->size; n++) {
		double intensity = (INPUT->pixel[n] / (double)(255)) * (levels - 1);
		intensity = round(intensity);
		INPUT->pixel[n] = (int)(intensity * 255) / (levels - 1);
	}
}
