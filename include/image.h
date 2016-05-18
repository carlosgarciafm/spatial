#ifndef IMAGE_H
#define IMAGE_H

#include "base.h"

GS* verticalPattern(unsigned int height, unsigned int width);

GS* horizontalPattern(unsigned int height, unsigned int width);

GS* gridPattern(unsigned int height, unsigned int width);

GS* copy(GS* INPUT);

GS* extract(const GS* INPUT, unsigned int x, unsigned int y, unsigned int height, unsigned int width);

GS* replace(GS* INPUT_A, GS* INPUT_B, unsigned int x, unsigned int y);

GS* rotate90(const GS* INPUT);

GS* rotate90n(const GS* INPUT);

void negative(GS* INPUT);

void binary(GS* INPUT, unsigned int threshold);

#endif
