#include "base.h"
#include "image.h"

/* Creates a test image with a vertical pattern. */
GS* verticalPattern(unsigned int height, unsigned int width) {
	int n;
	GS* INPUT = newBMP(height, width);
	for(n = 0; n < INPUT->size; n++)
		/* Sets all the pixels on the left side of the image to 255; the rest are set to 0. */
		INPUT->pixel[n] = ((n / (INPUT->width / 2)) % 2 == 0)? 255: 0;
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
