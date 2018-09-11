#include<stdio.h>
#include<ctype.h>

void condicoesPalavra(char palavra[]){
	int i;
	for(i=0; palavra[i];i++){
		palavra[i]=toupper(palavra[i]);
		if(palavra[i]==' '){//J ou I ?
			
		}
	}
	palavra[i]=0;
}
void outrasLetras(){
	
}

int main(){
	char letras[5][5], palavra;
	scanf("%s", palavra);
	/*----------------construindo a matriz-----------------*/
	int i,j, index=0;
	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			if(palavra[index]){
				condicoesPalavra(palavra);
				if(palavra[index]==' ') index++;
				letras[i][j]=palavra[index];
				index++;
			}
			else{
				letras[i][j] = outrasLetras();
			}
		}	
	}
	return 0;
}
