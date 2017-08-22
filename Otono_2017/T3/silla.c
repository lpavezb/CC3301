#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

pthread_mutex_t palitos[5];
pthread_mutex_t m;
pthread_cond_t cond;
int sillas[5] = {0,0,0,0,0};

int count();
int count(){
    int res = 0;
    for (int i = 0; i < 5; ++i)
        res+=sillas[i];
    return res;
}
int buscarSilla(){
    pthread_mutex_lock(&m);
    int k;
    if(count()>4){
        pthread_cond_wait(&cond, palitos);
    }
    else{
        for (int i = 0; i < 5; ++i) {
            if (sillas[i]==0){
                sillas[i]=1;
                sillas[(i+1)%5]=1;
                k=i;
                break;
            }
        }
    }
    int m1= min(k, (k+1)%5);
    int m2= max(k, (k+1)%5);
    pthread_mutex_lock(&palitos[m1]);
    pthread_mutex_lock(&palitos[m2]);
    pthread_mutex_unlock(&m);
    return k;
}

void desocuparSilla(int k){
    sillas[k]=0;
    sillas[(k+1)%5]=0;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&palitos[k]);
    pthread_mutex_unlock(&palitos[(k+1)%5]);
}
