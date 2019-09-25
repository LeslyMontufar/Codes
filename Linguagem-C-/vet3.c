#include<stdio.h>

int main(){
	int num[10], i, soma=0, produto=1;
	for(i=0; i<10; i++){
		scanf("%i", &num[i]);
		soma+=num[i];
		produto*=num[i];
	}
	printf("%i; %i\n", soma, produto);
	return 0;
}
