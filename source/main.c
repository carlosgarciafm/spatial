#include "base.h"
#include "image.h"

int main() {
	GS* A = getBMP("inputs/aircraft.bmp");
	freeBMP(A);
	return 0;
}
