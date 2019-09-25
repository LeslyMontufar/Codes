#include <stdio.h>

struct Fracao{
	int num;
	int den;
};

void somaFracao(int a, int b, int c, int d, int *num, int *den){
    *num=d*a+b*c;
    *den=b*d;
}

int main(){
	struct Fracao a, b, soma;
	scanf("%i/%i, %i/%i", &a.num,&a.den, &b.num, &b.den);
    if(a.den!=0 && b.den!=0){
    	somaFracao(a.num, a.den, b.num, b.den, &soma.num, &soma.den);
		printf("%i/%i", soma.num, soma.den);
	}else
    	printf("erro!\n");
    return 0;
}
