#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "bolsa.h"

void eliminar_espacios(char* s){
    int len = strlen(s)-1;
    int i = 0;
    while(i<len){
        if(*s == ' '){
            *s='\0';
            break;
        }
        s++;
        i++;
    }
}

pthread_mutex_t Buyer;
pthread_mutex_t m;
pthread_cond_t buyer;

int m_precio = 0;
char* sell;
char* buy;

int vendo(int precio, char *vendedor, char *comprador){
	pthread_mutex_lock(&m);
	if(m_precio == 0 || m_precio >= precio){
		m_precio = precio;
		sell = vendedor;
		pthread_cond_wait(&buyer, &m);
		int len = strlen(buy);
		for(int i = 0; i<len; i++)
			comprador[i]=buy[i];
		comprador[len]='\0';
		pthread_mutex_unlock(&m);
		return 1;
	}
	else{
		pthread_mutex_unlock(&m);
		return 0;
	}	
}

int compro(char *comprador, char *vendedor){
	if(m_precio == 0)
		return 0;
	pthread_mutex_lock(&Buyer);
	int len = strlen(sell);
	for(int i = 0; i<len; i++)
		vendedor[i]=sell[i];
	vendedor[len]='\0';
	buy = comprador;
	pthread_mutex_unlock(&Buyer);
	pthread_cond_broadcast(&buyer);
	int res = m_precio;
	m_precio = 0;
	return res;
}

