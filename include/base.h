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

GS* getBMP(char* name);

void putBMP(char* name, GS* INPUT);

GS* newBMP(unsigned int height, unsigned int width);

void freeBMP(GS* INPUT);

#endif
