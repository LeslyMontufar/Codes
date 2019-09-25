#include <stdio.h>

struct Fracao {
    int num;
    int den;
};

int MDC(int u, int v);
void somaFracao(int a, int b, int c, int d, int *num, int *den);

int main() {
    struct Fracao a, b, soma;
    scanf("%i/%i, %i/%i", &a.num,&a.den, &b.num, &b.den);
    if(a.den!=0 && b.den!=0) {
        somaFracao(a.num, a.den, b.num, b.den, &soma.num, &soma.den);
        printf("%i/%i", soma.num, soma.den);
    } else
        printf("erro!\n");
    return 0;
}

void somaFracao(int a, int b, int c, int d, int *num, int *den) {
    *num=d*a+b*c;
    *den=b*d;

    int mdc=MDC(*num, *den);
    *num/=mdc;
    *den/=mdc;
}
int MDC(int u, int v) {
    if(u==v || v==0)
        return u;
    else if(u==0)
        return v;
    else if(u%2==0 && v%2!=0)
        return MDC(u/2, v);
    else if(u%2!=0 && v%2==0)
        return MDC(u, v/2);
    else if(u%2==0 && v%2==0)
        return 2*MDC(u/2, v/2);
    else if(u>v)
        return MDC((u-v)/2, v);
    else
        return MDC((v-u)/2, u);
}
