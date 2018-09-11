#include <stdio.h>
#include <ctype.h>

#define n 100

int main(){
	int i, cont=0;
	char frase[n];
	fflush(stdin);
	gets(frase);
	for(i=0;frase[i]; i++){
		if(isalpha(frase[i])){
			cont++;
		}	
	}
	printf("%i\n", cont);
	return 0;
}
