#include<stdio.h>
#include<math.h>

int main(){
	double A, a, b, c;
	scanf("%lf, %lf, %lf", &b, &c, &A);
	a = sqrt(pow(b,2)+pow(c,2)-(2*b*c*cos(A)));
	printf("%lf\n", a);
	return 0;
}
