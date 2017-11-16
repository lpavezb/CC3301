#define _POSIX_C_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "suma.h"

#define BUFF_SIZE 8192

pid_t children[8];

int leer(int fd, void *buf, int n) {
  if (n==0)
    return 0;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf= (char*)buf + rc; /* avanzamos el buffer */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

Set buscar(int a[], int n) {
	Set combinaciones = (1<<(n-1)<<1)-1;
	Set comb = combinaciones / 8;
	for( int i = 0; i < 8; i++ ) {
		children[i]=fork();
	}
	for( int i = 0; i < 8; i++ ) {
		int fd[2];
		if (pipe(fd) != 0) {
			perror("Can't pipe");
			exit(1);
		}
		if(children[i]==0){/*child*/
			Set k   = (comb*i + 1);
			Set end = (k + comb);
			for (; k <= end; k++) { 
				long long sum= 0;
				for (int j= 0; j<n; j++) {
					if ( k & ((Set)1<<j) )
						sum+= a[j];
				}
				if (sum==0){
					close(fd[0]);
					write(fd[1],&k,sizeof(k));
					exit(0);
				}else{
					close(fd[0]);
					Set s = 0;
					write(fd[1],&s,sizeof(s));
					exit(0);
				}
			}
		}
		else if(children[i]>0){/*parent*/
			printf("########################: %d\n", i);
			waitpid(children[i], NULL, 0);
			children[i]=-1;
			close(fd[1]);
			Set d;
			leer(fd[0],&d,sizeof(d));
			printf("parent %d: %d\n", i, (int)d);
			if (d!=0){
				return d;
			}
			
		}
		else{/*error*/
			perror( "fork" );
			exit( 1 );
		}
	}
	for (int pid = 0; pid < 8; pid++){
		printf("####################\n");
		if(children[pid]!=-1)
			kill(children[pid], SIGTERM);
	}
	return 0;
}