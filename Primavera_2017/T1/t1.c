#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t1.h"

uint insertar_bits(uint x, int pos, uint y, int len) {
	uint newy = y << pos;
	uint maskx = 1;
	uint masky = 1;
	int j = 0;
	int i = 31;
	while(pos-1>=j){
		if(maskx & x)
			newy = newy | maskx;
		maskx = maskx << 1;
		j++;
	}
	masky = maskx << len;
	while(i>=j){
		if(maskx & x)
			newy = newy | masky ;
		maskx = maskx << 1;
		masky = masky << 1;
		j++;
	}
	return newy;
}

void eliminar_espacios(char *s) {
	int len  = strlen(s)-1;
	char *aux = s;
	int i = 0;
	while(len >= i){
		if(*s==' '){
			if(*s++=='\0')
				break;
			while(*s==' '){
				s++;
				i++;
			}
			s--;
			i--;
		}
		*aux = *s;
		aux++;
		s++;
		i++;
	} 
}
