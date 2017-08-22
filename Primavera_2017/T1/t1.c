#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t1.h"

uint insertar_bits(uint x, int pos, uint y, int len) {
	uint mask = 0xffffffff;
	printf("%d\n", mask & 0xf);
	return mask;

}


void eliminar_espacios(char *s) {
	printf("%s\n", "\n");
}

int main(int argc, char const *argv[])
{
	insertar_bits(0x2, 0, 1, 1);
	return 0;
}
