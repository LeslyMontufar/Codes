#include<stdio.h>
#include<stdint.h>
#include<time.h>
#include<stdlib.h>//para usar a srand();

int main(){
	srand(time(NULL));
	float n;
	int i, cont=0;
	scanf("%f", &n);
	for(i=0; i<1000;i++){
		if((float)rand()/RAND_MAX == n) cont++;
	}
	
	int64_t a=120;
	//printf("%"PRId64"\n", a);
	printf("+/-%i\n", cont);
	return 0;
}
