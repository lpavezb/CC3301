#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "suma.h"

#define BUFF_SIZE 8192


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
	pid_t children[8];
	int fds[8][2];
	Set comb= ((1<<(n-1)<<1)-1)/8;
	Set res = 0;
	for (int i = 0; i < 8; ++i)	{
		int fd[2];
		fds[i][0]=fd[0];
		fds[i][1]=fd[1];
		if (pipe(fd) != 0) {
			perror("Can't pipe");
			exit(1);
		}
		if ((children[i]=fork())==0){
			Set k   = comb*i +1;
			Set end = k + comb;
			for (; k<=end; k++) {
				long long sum= 0;
				for (int j= 0; j<n; j++) {
					if ( k & ((Set)1<<j) ) 
						sum+= a[j];
				}
				if (sum==0){
					close(fds[i][0]);
					write(fds[i][1],&k,sizeof(Set));
					close(fds[i][1]);
					exit(0);
				}
			}
			exit(0);
		}
		else if(children[i]>0)
			continue;
		else
			perror("fork error");
	}

	int break_aux = 0;

	for (int i = 0; i < 8; i++){
		pid_t pid = waitpid(0,NULL,0);
		for (int j = 0; j < 8; ++j){
			if(children[j]==pid){
				children[j] = -1;
				close(fds[j][1]);
				leer(fds[j][0],&res,sizeof(Set));
				close(fds[i][0]);
				if(res!=0){
					break_aux = 1;
					for (int k = 0; k < 8; k++){
						if(children[k]!=-1)
							kill(children[k], SIGTERM);
					}
					break;
				}
			}
		}
		if(break_aux){break;}
	}
	for (int i = 0; i < 8; ++i)
		waitpid(children[i],NULL,0);
	return res;
}