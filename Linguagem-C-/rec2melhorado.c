#include <stdio.h>
#define n 256
void reverte(char *letra);
int main(){
    char frase[n];
    fflush(stdin);
    gets(frase);
    reverte(&frase[0]);
    return 0;
}

void reverte(char *letra){
    if(*letra){
        reverte(letra+1);
          //reverte(letra+1);
          
              //reverte(letra+1);//no \0 quebra a recursao e nao printa nada
                                 //depois continua com o printf(); de todos os reverte
              //printf("%c", *letra);
          
          //printf("%c", *letra);
        printf("%c", *letra);
    }
}
