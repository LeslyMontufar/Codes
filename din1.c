#include <stdio.h>
#include <stdlib.h> //para fazer alocação dinâmica
#include <math.h>

double soma (double *num, int n){
	return (n<0)? 0 : num[n]+soma(num, n-1);
}

double somaDosQuadrados (double *num, int m, int n){
	return (n<0)? 0 : pow(num[n]-m, 2) + somaDosQuadrados(num, m, n-1); //zero é o elemento neutro da soma
}

int main(){
	double *num,m;
	int n, i;
	scanf("%i", &n);
	
	num = (double *) malloc(n*sizeof(double));
	
	for(i=0; i<n; i++){
		scanf("%lf", &num[i]);
	}
	
	m=soma(num, n-1)/n;
	printf("%lf, %lf", m, sqrt(somaDosQuadrados(num, m, n-1)/(n-1)));
	free(num);
	return 0;
}
