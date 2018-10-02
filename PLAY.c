/*Meu c�digo playfair
	-com espa�o no final n�o funciona ainda

	- est� dando erro na deografar, que � a mesma coisa que tem em criptografar (acho que � porque n�o sei usar ponteiros direito) 
	- tanto faz a ordem em que se declara as fun��es?
	- como configurar o Android Studio para ver o aplicativo no meu celular?
	- MIT app inventor 2: n�o d� pra aumentar o tempo em que o sound vai tocar? 
	- conio2.h: tenho que aprender as fun��es ainda :(
*/

#include<stdio.h>
#include<ctype.h>
#include<conio2.h>
#include<stdlib.h>

#define n 256

//enum COLORS {
//	BLACK, BLUE, GREEN, CYAN,
//	RED, MAGENTA, BROWN, LIGHTGRAY,
//	DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
//	LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
//}

int comparaComOutrasLetras(char vetor[], char letra, int pos) {
    int i;
    for(i=0; i<pos; i++) {
        if(vetor[i]==letra)
            return 1;
    }
    return 0;
}
void condicoesPalavra(char palavra[]) {
    int i;
    for(i=0; palavra[i]; i++) {
        palavra[i]=toupper(palavra[i]);
        if(palavra[i]=='J') {
            palavra[i]='I';
        }
    }
    palavra[i]=0;
}

void constroiMatriz(char letras[][5], char palavra[]) {
    int i,j, index=0;
    char alfabeto= 'A';
    for(i=0; i<5; i++) {
        for(j=0; j<5; j++) {
            while((palavra[index]==' ') || comparaComOutrasLetras(palavra, palavra[index], index)==1)
                index++;
            if(palavra[index]) {
                letras[i][j]=palavra[index];
                index++;
            } else {
                while(comparaComOutrasLetras(palavra, alfabeto, index)==1 || alfabeto=='J')
                    alfabeto++;
                letras[i][j]=alfabeto;
                alfabeto++;
            }
        }
    }
}
void printaMatriz(char matriz[][5]) {
    int i, j;
    for(i=0; i<5; i++) {
        for(j=0; j<5; j++) {
            printf("%c\t", matriz[i][j]);
        }
        printf("\n\n");
    }
}
void apresentacao(int *opcao) { //quando recebe sem ser como ponteiro == recebe uma c�pia da variavel a ser modificada
    //como ponteiro, vai mudar a variavel cujo *ponteiro aponta
    gotoxy(12,4);
    textbackground(LIGHTMAGENTA);
    textcolor(WHITE);
    printf("--PLAYFAIR CODE--\n\n");
    textbackground(BLACK);
    printf("\t0- Finalizar o programa\n");
    printf("\t1- Insira a chave\n");
    printf("\t2- Frase\n");
    printf("\t3- Criptografar\n");
    printf("\t4- Descriptografar\n");
    printf("\t5- Limpa tudo\n\n\n");
    printf("\tOpcao: ");
    textcolor(YELLOW);
    scanf("%i", opcao);
	textcolor(WHITE);
	//*opcao , tudo isso � a vari�vel agora entao opcao!= *opcao, em toda a fun�ao s� existe *opcao
    //*opcao � o valor      valor
    //opcao � o endereco    &valor
}

void criptografar(char letras[][5], char frase[], char crip[]) {
    char grupos[n][2];
    int i, j, index=0;
    for(i=0; frase[index]; i++) {
        for(j=0; j<2; j++) {
            while(frase[index]==' ')
                index++;
            if(frase[index]) {
                if(j==1 && frase[index]==grupos[i][0])
                    grupos[i][j]='X';
                else {
                    grupos[i][j]=frase[index];
                    index++;
                }
            } else {
                grupos[i][j]='X';
                //break;//nao precisa, por que depois de fazer i++ faz o break, a� em baixo s� precisaria colocar i-1;
                //quando entrar na condi��o do frase[index], vai somar i++, entao do mesmo jeito precisa ser i-1 l� embaixo;
            }
        }
        //aqui o i vai somar 1 e s� depois disso vai verificar se frase[index] � verdadeiro(existe)
        //(e n�o vai existir- nao vai ser veradeiro);
    }
    int line, letra1i, letra1j, letra2i, letra2j, ii, jj;//ii e jj s� s�o auxiliares para percorer a matriz;
    index=0;
    for(line=0; line<=i-1; line++) { //line<i seria a mesma coisa, mas do jeito que est� d� pra entender melhor a l�gica;

        for(ii=0; ii<5; ii++) {
            for(jj=0; jj<5; jj++) {
                if(grupos[line][0]==letras[ii][jj]) {
                    letra1i=ii;
                    letra1j=jj;
                }
                if(grupos[line][1]==letras[ii][jj]) {
                    letra2i=ii;
                    letra2j=jj;
                }
            }
        }
        /*caso 1 - letras na mesma linha*/
        if(letra1i==letra2i) {
            if(letra1j==4) {
                crip[index]=letras[letra1i][0];
                index++;
            } else {
                crip[index]=letras[letra1i][letra1j+1];
                index++;
            }
            if(letra2j==4) {
                crip[index]=letras[letra2i][0];
                index++;
            } else {
                crip[index]=letras[letra2i][letra2j+1];
                index++;
            }
        }
        /*caso 2 - letras na mesma coluna*/
        else if(letra1j==letra2j) {
            if(letra1i==4) {
                crip[index]=letras[0][letra1j];
                index++;
            } else {
                crip[index]=letras[letra1i+1][letra1j];
                index++;
            }
            if(letra2i==4) {
                crip[index]=letras[0][letra2j];
                index++;
            } else {
                crip[index]=letras[letra2i+1][letra2j];
                index++;
            }
        }
        /*caso 3 - letras em linhas e colunas diferentes*/
        else {
            crip[index]=letras[letra1i][letra2j];
            index++;
            crip[index]=letras[letra2i][letra1j];
            index++;
        }
    }
    crip[index]=0;
}
//int agrupaLetrasDeDoisEmDois(char frase[], char grupos[][5]) {
//    int j,index=0, i=0;
//    for(; frase[index]; i++) {
//        for(j=0; j<2; j++) {
//            while(frase[index]==' ')
//                index++;
//            if(frase[index]) {
//                if(j==1 && frase[index]==grupos[i][0])
//                    grupos[i][j]='X';
//                else {
//                    grupos[i][j]=frase[index];
//                    index++;
//                }
//            } else {
//                grupos[i][j]='X';
//            }
//        }
//    }
//    return i;
//}
void deografar(char letras[][5], char frase[], char crip[]) {
    char grupos[n][2];
    int i, j, index=0;
    for(i=0; frase[index]; i++) {
        for(j=0; j<2; j++) {
            while(!isalpha(frase[index])&& frase[index]) index++;
            if(frase[index]) {
                if(j==1 && frase[index]==grupos[i][0])
                    grupos[i][j]='X';
                else {
                    grupos[i][j]=frase[index];
                    index++;
                }
            } else if(j!=0){
                grupos[i][j]='X';
            }else break;
        }
        printf("%c%c |", grupos[i][0], grupos[i][1]);
    }
    int line, letra1i, letra1j, letra2i, letra2j, ii, jj;//ii e jj s� s�o auxiliares para percorer a matriz;
    index=0;
    for(line=0; line<=i-1; line++) { //line<i seria a mesma coisa, mas do jeito que est� d� pra entender melhor a l�gica;

        for(ii=0; ii<5; ii++) {
            for(jj=0; jj<5; jj++) {
                if(grupos[line][0]==letras[ii][jj]) {
                    letra1i=ii;
                    letra1j=jj;
                }
                if(grupos[line][1]==letras[ii][jj]) {
                    letra2i=ii;
                    letra2j=jj;
                }
            }
        }

        /*caso 1 - letras na mesma linha*/
        if(letra1i==letra2i) {
            if(letra1j==0) {
                crip[index]=letras[letra1i][4];
                index++;
            } else {
                crip[index]=letras[letra1i][letra1j-1];
                index++;
            }
            if(letra2j==0) {
                crip[index]=letras[letra2i][4];
                index++;
            } else {
                crip[index]=letras[letra2i][letra2j-1];
                index++;
            }
        }
        /*caso 2 - letras na mesma coluna*/
        else if(letra1j==letra2j) {
            if(letra1i==0) {
                crip[index]=letras[4][letra1j];
                index++;
            } else {
                crip[index]=letras[letra1i-1][letra1j];
                index++;
            }
            if(letra2i==0) {
                crip[index]=letras[4][letra2j];
                index++;
            } else {
                crip[index]=letras[letra2i-1][letra2j];
                index++;
            }
        }
        /*caso 3 - letras em linhas e colunas diferentes*/
        else {
            crip[index]=letras[letra1i][letra2j];
            index++;
            crip[index]=letras[letra2i][letra1j];
            index++;
        }
    }
    crip[index]=0;
}
int main() {
    int opcao, existeChave=0;
    char letras[5][5], palavra[n], frase[n], crip[n];
    frase[0]=0;
    do {
        system("cls"); //passar como ponteiro, ao inves de uma copia da variavel, economiza espaco na memoria!
        apresentacao(&opcao);//ou podia gerar outra variavel : *pOpcao = &opcao
        //nesse caso teria que enviar s� pOpcao, que � o endere�o do ponteiro (uma vers�o modificavel da vari�vel);
        //d� pra pensar que se  *pTeste= &teste =>  pTeste= teste,    assim * pode cortar com &
        //o ponteiro serve para passar a variavel por referencia, como j� ocorre com matrizes e vetores.
        switch(opcao) {
        case 1:
            printf("\nChave: ");
            fflush(stdin);
            gets(palavra);
            printf("\n\n");
            condicoesPalavra(palavra);
            constroiMatriz(letras,palavra);
            printaMatriz(letras);
            getch();
            existeChave=1;
            break;

        case 2:
            printf("\nFrase: ");
            fflush(stdin);
            gets(frase);
            condicoesPalavra(frase);
            getch();
            break;

        case 3:
            if(existeChave && frase[0]) {
                printf("\n");
                printaMatriz(letras);
                criptografar(letras, frase, crip);
                printf("\nFrase original: %s", frase);
                printf("\nFrase criptografada: %s\n", crip);
            } else
                printf("\n\n\n\tErro: chave ou frase nao inserida\n");
            getch();
            break;

        case 4:
            if(existeChave && frase[0]) {
                printaMatriz(letras);
                deografar(letras, frase, crip);
                printf("\nFrase original: %s", frase);
                printf("\nFrase deografada: %s\n", crip);
            } else
                printf("\n\n\n\tErro: chave ou frase nao inserida\n");
            getch();
            break;

        case 5:
            existeChave=0;
            frase[0]=0;//limpa o vetor de char adicionando \0 � primeira posi��o do vetor;
            break;

        default:
            if(opcao)
                printf("Opcao invalida!\n");
        }
    } while(opcao);
    return 0;
}
/*lembrar de no final passar de Java para norma ANSI*/
/*settings > editor > source formater > pronto! mudar para ANSI*/

