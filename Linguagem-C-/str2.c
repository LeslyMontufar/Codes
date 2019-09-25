#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#define n 255


int main(){
	int v=0,c=0,d=0,e=0;
	char frase[n], i;
	fflush(stdin);
	gets(frase);
	for(i=0; frase[i]; i++){
		frase[i]=toupper(frase[i]);
		if(frase[i]=='A' || frase[i]=='E' || frase[i]=='I' || frase[i]=='O' || frase[i]=='U') v++;
		else if(isalpha(frase[i])) c++;
		if(isdigit(frase[i])) d++;
		if(isspace(frase[i])) e++;
	}
	
	printf("V:%i;C:%i;D:%i;E:%i\n", v, c, d, e);
	
	return 0;
}
