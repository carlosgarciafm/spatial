#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned long int DWORD;

typedef struct {
	BYTE id[1], bpp, *head;
	WORD offset, width, height;
	int size;
	float *pixel;
}GS;

#endif
