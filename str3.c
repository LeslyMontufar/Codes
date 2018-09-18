#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#define n 255


int main(){
	char frase[n], crip[n], alpha[2][13], letra='A';
	int i, j, index;
	for(i=0; i<2;i++){
		for(j=0; j<13; j++){
			alpha[i][j]=letra;
			letra++;
		}
	}
	fflush(stdin);
	gets(frase);
	for(index=0; frase[index]; index++){
		if(isalpha(frase[index])){
			for(i=0; i<2;i++){
				for(j=0; j<13; j++){
					if(toupper(frase[index])==alpha[i][j]){
						if(i==1) crip[index]=alpha[0][j];
						else crip[index]=alpha[1][j];
					}
				}
			}
			if(islower(frase[index])) crip[index]=tolower(crip[index]);
		}
		else crip[index]=frase[index];
	}
	crip[index]=0;
	printf("%s\n", crip);
	
	return 0;
}
