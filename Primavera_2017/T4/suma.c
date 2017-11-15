#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "suma.h"

#define BUFF_SIZE 8192

pid_t children[8];
Set k;
Set end;
Set buscar(int a[], int n) {
    Set combinaciones = (1<<(n-1)<<1)-1;
    Set comb = combinaciones / 8;
    for( int i = 0; i < 8; i++ ) {
    	int fd[2];

        if (pipe(fd) != 0) {
            perror("Can't pipe");
            exit(1);
        }
    	switch( children[i]=fork()) { 
    	    case 0: /* child */
    	        k = comb*i + 1;
    	        end = k + comb;
    	        for (k; k<=end; k++) { 
    	            long long sum= 0;
    	            for (int j= 0; j<n; j++) {
    	                if ( k & ((Set)1<<j) )
    	                    sum+= a[j];
    	            }
    	            if (sum==0){
    	            	close(fd[0]);
    	                write(fd[1],&k,sizeof(k));
    	                exit(0);
    	            }
    	        }
    	        Set s = 0;
    	        write(fd[1],&s,sizeof(s));
    	        exit( 0 );
    	    case -1:
    	        perror( "fork" );
    	        exit( 1 );
    	    default:  /* parent */
    	        close(fd[1]);
            	Set d;
            	read(fd[0],&d,sizeof(d));
            	printf("parent %d: %d\n", i, (int)d);
            	if (d!=0)
            	    return d;
    	} 
	}
    for (int i = 0; i < 8; ++i)
    	waitpid(children[i], NULL, 0);
    
    return 0;
}