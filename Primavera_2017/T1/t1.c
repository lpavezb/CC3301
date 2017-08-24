#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t1.h"
char *uint2bits(uint x);
int bit_mas_significativo(uint x);

uint insertar_bits(uint x, int pos, uint y, int len) {
	uint res  = 0;
	uint newy = 0;
	uint maskx = 1;
	uint masky = 1;
	int i = 31;
	int j = 0;
	int aux = 0;
	while(i>=j){
		if(j==pos){
			while(len >= aux){
				if(masky & y){
					res = res | masky;
					newy= newy | masky;
				}
				masky = masky << 1;
				aux++;
			}
		}
		if(maskx & x)
			res = res | masky;
		maskx = maskx << 1;
		masky = masky << 1;
		j++;
	}
	printf("%s\n", uint2bits(newy));
	return res;

}

int main(int argc, char const *argv[]) {
	if (insertar_bits(0x17, 2, 0x0e, 5)==0x2bb){
		printf("%s\n", "success");
	}
	
	return 0;
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


int bit_mas_significativo(uint x) {
    int i = 31, j = 0;
    while (i >= j) {
        int k = (i + j + 1) / 2;
        int mascara = 0xffffffff << (k + 1);
        if (x & mascara) {
            j = k + 1;
        } else if (x & (1 << k)) {
            return k;
        } else {
            i = k - 1;
        }
    }

    return -1;
}


char *uint2bits(uint x) {
	int len = bit_mas_significativo(x)+1;
	if (len==0){
		char *new = (char*) malloc(2);
		char *aux = new + 1;
		*aux = '\0';
		aux--;
		*aux = '0';
		return new;
	}

	char *new = (char*) malloc(len + 1);
	char *aux = new + len;
	*aux = '\0';
	aux--;
	uint mask = 1;
	int i = 0;
	while(i < len) {
		if((x & mask) != 0){
			*aux = '1';
		}
		else{
			*aux = '0';
		}
		
		--aux;
		mask = mask << 1;
		i++;
	}
	return new;
}

