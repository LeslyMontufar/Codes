#include<stdio.h>
#include<ctype.h>
#include<conio2.h>
#define n 256
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
            printf("\t%c", matriz[i][j]);
        }
        printf("\n\n");
    }
}
void apresentacao(int *opcao) { 
    gotoxy(12,4);
    textbackground(LIGHTMAGENTA);
    textcolor(WHITE);
    printf("--PLAYFAIR CODE--\n\n");
    textbackground(BLACK);
    printf("\t0- Finalizar o programa\n");
    printf("\t1- Insira a chave\n");
    printf("\t2- Frase\n");
    printf("\t3- Criptografar\n");
    printf("\t4- Deografar\n");
    printf("\t5- Limpa tudo\n\n\n");
    printf("\tOpcao: ");
    textcolor(YELLOW);
    scanf("%i", opcao);
    textcolor(WHITE);
}
int agrupaLetrasDeDoisEmDois(char frase[], char grupos[][2]) {
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
            } else if (j==1) {
                grupos[i][j]='X';
            } else
                return i;
        }
    }
    return i;
}
void criptografar(char letras[][5], char frase[], char crip[], char escolha) {
    char grupos[n][2];
    int i, line, letra1i, letra1j, letra2i, letra2j, ii, jj, index=0;
    i=agrupaLetrasDeDoisEmDois(frase, grupos);
    for(line=0; line<=i-1; line++) { 
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
        if(letra1i==letra2i) {
            if(escolha=='c') {
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
            if(escolha=='d') {
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
        }
        else if(letra1j==letra2j) {
            if(escolha=='c') {
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
            if(escolha=='d') {
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
        }
        else {
            if(escolha=='c') {
                crip[index]=letras[letra1i][letra2j];
                index++;
                crip[index]=letras[letra2i][letra1j];
                index++;
            }
            if(escolha=='d') {
                crip[index]=letras[letra1i][letra2j];
                index++;
                crip[index]=letras[letra2i][letra1j];
                index++;
            }
        }
    }
    crip[index]=0;
}
 int main() {
    int opcao, existeChave=0;
    char letras[5][5], palavra[n], frase[n], crip[n];
    frase[0]=0;
    do {
        clrscr(); 
        apresentacao(&opcao);
        switch(opcao) {
        case 1:
            printf("\n\tChave: ");
            textcolor(YELLOW);
            fflush(stdin);
            gets(palavra);
            printf("\n\n");
            condicoesPalavra(palavra);
            constroiMatriz(letras,palavra);
            textcolor(WHITE);
            printaMatriz(letras);
            getch();
            existeChave=1;
            break;
        case 2:
            printf("\n\tFrase: ");
            textcolor(YELLOW);
            fflush(stdin);
            gets(frase);
            condicoesPalavra(frase);
            getch();
            break;
        case 3:
            if(existeChave && frase[0]) {
                printf("\n");
                printaMatriz(letras);
                criptografar(letras, frase, crip, 'c');
                printf("\n\tFrase original: %s", frase);
                printf("\n\tFrase criptografada: %s\n", crip);
            } else {
                textcolor(RED);
                printf("\n\n\n\t\tErro: chave ou frase nao inserida\n");
            }
            getch();
            break;
        case 4:
            if(existeChave && frase[0]) {
                printf("\n");
                printaMatriz(letras);
                criptografar(letras, frase, crip, 'd');
                printf("\n\tFrase original: %s", frase);
                printf("\n\tFrase deografada: %s\n", crip);
            } else {
                textcolor(RED);
                printf("\n\n\n\t\tErro: chave ou frase nao inserida\n");
            }
            getch();
            break;
        case 5:
            existeChave=0;
            frase[0]=0;
            break;
        default:
            if(opcao) {
                textcolor(RED);
                printf("\n\n\t\tOpcao invalida!\n");
                getch();
            }
        }   } while(opcao);
    return 0;
}
