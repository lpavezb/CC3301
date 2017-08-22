#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "concat.h"

uint bits2uint(char *s) {
	int len = strlen(s);
	char *aux = s + len -1;
	int res = 0;
	uint mask = 1;
	int i=0;
	while(i<len){
		if(*aux == '1'){
			res = res | mask;
		}
		mask = mask << 1;
		aux--;
		i++;
	}
  	return res;
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

uint concat_bits(uint x, int n, uint y, int m) {
	int len_x = bit_mas_significativo(x)+1;
	char *a = uint2bits(x);
	int diff_x = n - len_x;

	int len_y = bit_mas_significativo(y)+1;
	char *b = uint2bits(y);
	int diff_y = m - len_y;

	char *a_p = add_zeros(a, diff_x);
	char *b_p = add_zeros(b, diff_y);

	int len_res = m+n;
	char *new = (char*) malloc(len_res + 1);
	char *aux = new + len_res + 1;
	char *aux_a = a_p + n -1;
	char *aux_b = b_p + m ;

	*aux = '\0';
	--aux;

	int i = 0;
	while(i<=len_res){
		if(i<=m){
			*aux = *aux_b;
			aux--;
			aux_b--;
			i++;
		}
		else{
			*aux = *aux_a;
			aux--;
			aux_a--;
			i++;	
		}
	}
	free(a_p);
	free(b_p);

	return bits2uint(new);
}

char *add_zeros(char *s, int zeros) {
	int len = strlen(s);
	char *res = (char*) malloc(len + zeros + 1);
	char *aux = res + len + zeros + 1;
	char *aux_s = s + len;

	*aux = '\0';
	--aux;

	int i = 0;
	int n = len + zeros;
	while(i<=n){
		if(i<=len){
			*aux = *aux_s;
			aux--;
			aux_s--;
			i++;
		}
		else{
			*aux = '0';
			aux--;
			i++;
		}
	}
	return res;
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