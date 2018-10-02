#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

int main(){
	int i,j, line=0, colune=0;
	scanf("%i%i", &i, &j);
	char caracteres[] = ": $ # $ : 4 b . ' :. : $ # $: 4b. ':.";
	srand(time(0));
	for(;line<i; line++){
		for(;colune<i; colune++){
			printf("%c ", caracteres[rand()%(strlen(caracteres)+1)]);
		}
		printf("\n");
	}
	return 0;
}
