#include<stdio.h>
#include<math.h>

int main(){
	double a, b, ln;
	scanf("%lf, %lf", &a, &b);
	ln=log(a)/log(b);
	printf("%g\n", ln);//%g nao mostra os zeros a mais do double
	return 0;
}
