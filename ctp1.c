#include <stdio.h>
#include <ctype.h>

#define n 100
int main(){
	int i;
	char frase[n];
	fflush(stdin);
	gets(frase);
	for(i=0;frase[i]; frase[i]=toupper(frase[i]), i++);
	printf("%s\n", frase);
	return 0;
}
