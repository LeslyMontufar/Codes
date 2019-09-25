#include<stdio.h>
#include<math.h>

void raizes(double *x1, double *x2, double a, double b, double c){
	*x1= (-b+sqrt(pow(b,2)-4*a*c))/(2*a);
	*x2= (-b-sqrt(pow(b,2)-4*a*c))/(2*a);
}

int main(){
	double x1, x2, a, b, c;
	scanf("%lf, %lf, %lf",&a, &b, &c);
	raizes(&x1, &x2, a,b,c);
	printf("x1=%lf\nx2=%lf\n", x1, x2);
	return 0;
}
