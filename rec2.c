#include  <stdio.h>
#define N 256

void fraseOrdemInversa(char frase[], int n){
	if(n>=0){
		printf("%c",frase[n]);
		fraseOrdemInversa(frase, n-1);
	}
	else return;
}

int main(){
	char frase[N];
	int n=0;
	fflush(stdin);
	gets(frase);
	for(;frase[n]; n++);
	fraseOrdemInversa(frase, n-1);
	return 0;
}
