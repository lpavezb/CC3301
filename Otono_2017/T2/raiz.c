#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "raiz.h"
double poli(void *ptr, double x);
double *add(double a[], int n, double *p);

double raiz(Funcion f, void *ptr, double x0, double x1, double eps){
	double xm;
	double ym;
	double y0;
	double s0;
	while(fabs(x1 - x0) > eps){
		xm = (x0 + x1)/2;
		ym = f(ptr,xm);
		y0 = f(ptr,x0);
		s0 = ym * y0;
		if(s0>0)
			x0=xm;
		else
			x1=xm;
	}
	return xm;
}
double raiz_poli(double a[], int n, double x0, double x1, double eps){
	double new[n+1];
	for (int i = 0; i <= n; ++i)
		new[i]=a[i];
	double *aux = new;
	double *p=add(new,n,aux);
	return raiz(poli,p,x0,x1,eps);
}

double poli(void *ptr, double x) {
	double *pa= ptr;
	double n = *pa;
	double f = 0.0;
	for (int i = 0; i <= n; i++)
		f+=*(pa+i+1)*pow(x,i);
	return f;
}

double *add(double a[], int n, double *p) {
	double new[n+2];
	new[0]=n*1.0;
	int i;
	for(i=0; i<n+1; i++)
		new[i+1]=a[i];
	for (int i = 0; i < n+2; ++i)
		*(p+i)=new[i];
	return p;
}