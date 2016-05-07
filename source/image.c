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
