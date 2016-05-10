#ifndef IMAGE_H
#define IMAGE_H

#include "base.h"

GS* verticalPattern(unsigned int height, unsigned int width);

GS* horizontalPattern(unsigned int height, unsigned int width);

GS* gridPattern(unsigned int height, unsigned int width);

GS* copy(GS* INPUT);

void negative(GS* INPUT);

#endif
