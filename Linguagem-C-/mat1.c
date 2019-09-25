#include<stdio.h>
#include<math.h>

struct Ponto{
	double x;
	double y;
}; 
int main(){
	struct Ponto a, b;
	scanf("%lf,%lf;", &a.x, &a.y);
	scanf("%lf,%lf", &b.x, &b.y);
	double dist = sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
	printf("%lf\n", dist);
	return 0;
}
