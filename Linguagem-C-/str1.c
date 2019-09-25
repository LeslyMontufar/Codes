#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#define n 255

int cmp(char frase[], char palavra[]){
	int i, index;
	for(i=0, index=0; palavra[i]; i++, index++){
		while(isspace(frase[index])) index++;
		if(frase[index]!=palavra[i]){
			return 1;
		}
	}
	return 0;
}
int main(){
	char frase[n], i;
	fflush(stdin);
	gets(frase);
	for(i=0; frase[i]; i++){
		frase[i]=toupper(frase[i]);
	}
	printf("%i; ", strlen(frase));
	if(strcmp(frase, "BOM DIA")==0) printf("Bom dia pra voce tambem\n");
	else if(cmp(frase, "TCHAU")==0) printf("Saindo? Que pena...\n");
	else printf("Voce quis dizer: %s?\n", frase);
	
	return 0;
}
