#include<stdio.h>

int main(){
	int num[10], i, aux;
	for(i=0; i<10; i++){
		scanf("%i", &num[i]);
	}
	for(i=0; i<6; i++){
		aux=num[i];
		num[i]=num[9-i];
		num[9-i]=aux;
	}
	for(i=0; i<10; i++){
		printf("%i ", num[i]);
	}
	printf("\n");
	return 0;
}
