#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	int n, vet[1000], min, max, i;
	scanf("%i", &n);
	srand(time(NULL));
	max=min=rand()%10;//múltipla atribuição!
	for(i=0; i<n; i++){
		vet[i]=rand()%10;
		if(min>vet[i]){
			min=vet[i];
		}
		if(max<vet[i]){
			max=vet[i];
		}
	}
	printf("min= %i\nmax= %i\n", min, max);
	return 0;
}
