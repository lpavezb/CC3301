#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t1.h"

uint insertar_bits(uint x, int pos, uint y, int len) {
	int res  = 0;
	int maskx = 1;
	int masky = 1;
	int i = 31 - len;
	int j = 0;
	int aux = 0;
	while(i>=j){
		if(j==pos){
			while(len > aux){
				if(masky & y)
					res = res | masky;
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
	return res;

}


void eliminar_espacios(char *s) {
	printf("%s\n", "\n");
}

/*int main(int argc, char const *argv[]) {
	insertar_bits(0x2, 0, 1, 1);
	return 0;
}*/
