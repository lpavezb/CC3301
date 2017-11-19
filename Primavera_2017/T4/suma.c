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


Set buscar(int a[], int n) {
	int fds[8][2];
	Set comb= ((1<<(n-1)<<1)-1)/8;
	for (int i = 0; i < 8; ++i)	{
		int fd[2];
		fds[i][0]=fd[0];
		fds[i][1]=fd[1];
		if (pipe(fd) != 0) {
			perror("Can't pipe");
			exit(1);
		}
		if ((children[i]=fork())==0){
			Set k   = (comb*i) + 1;
			Set end = k + comb -1;
			for (; k<=end; k++) {
				long long sum= 0;
				for (int j= 0; j<n; j++) {
					if ( k & ((Set)1<<j) ) 
						sum+= a[j];
				}
				if (sum==0){
					printf("child: %lld\n", k);
					close(fds[i][0]);
					write(fds[i][1],&k,sizeof(k));
					exit(0);
				}
			}
			exit(0);
		}
	}
	for (int i = 0; i < 8; i++){
		pid_t pid = waitpid(children[i],NULL,0);
		for (int j = 0; j < 8; ++j){
			if(children[j]==pid){
				children[j] = -1;
				Set res;
				close(fds[j][1]);
				read(fds[j][0],&res,sizeof(res));
				if(res!=0 && res<1000000){
					for (int k = 0; k < 8; k++){
						if(children[k]!=-1)
							kill(children[k], SIGTERM);
					}
					return res;
				}
			}
		}
	}
	return 0;
}