#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "bolsa.h"

pthread_mutex_t m;
pthread_cond_t buying;


int m_precio = 0;
char* seller;
char* buyer;
int buy=0;

void copy(char* copy_this, char* here){
	int len = strlen(copy_this);
	for(int i = 0; i<len; i++)
		here[i]=copy_this[i];
	here[len]='\0';
}

int vendo(int precio, char *vendedor, char *comprador){
	pthread_mutex_lock(&m);
	while(buy)
		pthread_cond_wait(&buying, &m);
	if(m_precio > precio || m_precio == 0){
		m_precio = precio;
		seller = vendedor;
		pthread_cond_broadcast(&buying);
		pthread_cond_wait(&buying, &m);
		if(m_precio < precio || seller != vendedor){
			pthread_mutex_unlock(&m);
			return 0;
		}
		copy(buyer, comprador);
		buyer  = NULL;
		seller = NULL;
		m_precio = 0;
		buy=0;
		pthread_cond_broadcast(&buying);
		pthread_mutex_unlock(&m);
		return 1;
	}
	else{
		pthread_mutex_unlock(&m);
		return 0;
	}
	
}

int compro(char *comprador, char *vendedor){
	pthread_mutex_lock(&m);
	while(buy)
		pthread_cond_wait(&buying, &m);
	if(m_precio == 0){
		pthread_mutex_unlock(&m);
		return 0;
	}
	buy=1;
	copy(seller,vendedor);
	buyer = comprador;
	int res = m_precio;
	pthread_cond_broadcast(&buying);
	pthread_mutex_unlock(&m);
	return res;
}

