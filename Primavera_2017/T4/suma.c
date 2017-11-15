#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "suma.h"
Set buscar(int a[], int n) {
    Set comb= (1<<(n-1)<<1)-1; 
    for (Set k= 1; k<=comb; k++) {
    
        long long sum= 0;
        for (int i= 0; i<n; i++) {
            if ( k & ((Set)1<<i) )
                sum+= a[i];
        }
        if (sum==0)
            return k;
    } 
    return 0;
}