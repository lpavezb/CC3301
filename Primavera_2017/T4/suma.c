#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "suma.h"

#define BUFF_SIZE 8192

pid_t children[8];

Set buscar(int a[], int n) {
    Set combinaciones = (1<<(n-1)<<1)-1;
    Set comb = combinaciones / 8;
    for (int i = 0; i < 8; i++) {
        int fd[2];

        if (pipe(fd) != 0) {
            perror("Can't pipe");
            exit(1);
        }

        if ((children[i] = fork()) == 0){
            Set k = comb*i + 1;
            Set end = k + comb;
            for (Set k= 1; k<=end; k++) { 
                long long sum= 0;
                for (int j= 0; j<n; j++) {
                    if ( k & ((Set)1<<j) )
                        sum+= a[j];
                }
                if (sum==0){
                    write(fd[1],&k,sizeof(k));
                    exit(1);//return k;
                }
            }
            Set s = 0;
            write(fd[1],&s,sizeof(s));
            exit(1);
        }
        else{
            Set d;
            read(fd[0],&d,sizeof(d));
            printf("parent: %d: %d\n", i, (int)d);
            waitpid(children[i], NULL, 0);
            if (d!=0)
                return d;
        }

    }
    return 0;
}