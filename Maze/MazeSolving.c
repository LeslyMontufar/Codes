#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define n 8
void printa(char lab[][n]);
void geraLabirinto(char lab[][n], int inicio[], int fim[], char simbolo[]);
int caminho(int x, int y, int inicio[], int fim[], char lab[][n], char simbolo[]);

int main() {
    char labirinto[n][n];
    int inicio[]= {0,0}, fim[]= {n-1,n-1};
    char simbolo[]= {'\xFA','\xDB','\xF8','\xAF',0}; //0-LIVRE , 1-PAREDE , 2-PASSOU, 3-CAMINHO;
    geraLabirinto(labirinto, inicio, fim, simbolo);
    printf("\t    --Labirinto--\n\n");
    printa(labirinto);

    if(caminho(inicio[0],inicio[1], inicio, fim, labirinto, simbolo)) { //ou igual a 1 ou diferente de 0
        printf("\n\n\t--Labirinto: Solucao--\n\n");
        printa(labirinto);
    } else {
        printf("\n\nImpossivel chegar no final do labirinto :(\nVoce esta perdido!\n\n");
        /* meu debug */
        printf("\n\n\t--Labirinto: Solucao--\n\n");
        printa(labirinto);
    }
    return 0;
}
int caminho(int x, int y, int inicio[], int fim[], char lab[][n], char simbolo[]) {
    if(x==-1 || y==-1||x==n||y==n) //limites do tabuleiro
        return 0;//nao pode ser fim + 1
    else if(x==fim[0] && y==fim[1]) {
        lab[x][y]=simbolo[3];
        return 1;

    } else if(lab[x][y]==simbolo[0]) {
        lab[x][y]=simbolo[2];
        if(caminho(x+1,y,inicio,fim,lab,simbolo)==1||caminho(x-1,y,inicio,fim,lab,simbolo)==1||caminho(x,y+1,inicio,fim,lab,simbolo)==1||caminho(x,y-1,inicio,fim,lab,simbolo)==1) {
            lab[x][y]=simbolo[3];
            return 1;
        }
    } else 
        return 0;
}
void geraLabirinto(char lab[][n], int inicio[], int fim[], char simbolo[]) {
    int i, j;

    /* aleatorio */
    //srand(time(NULL));
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            lab[i][j]= simbolo[rand()%2];
        }
    }
    lab[inicio[0]][inicio[0]]=lab[fim[0]][fim[1]]=simbolo[0];

    /* ---forcando um caminho---*/
    lab[5][1]=lab[5][3]=lab[5][4]=lab[5][6]=lab[6][6]=simbolo[0];
}
void printa(char lab[][n]) {
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            printf("%c    ", lab[i][j]);
        }
        printf("\n\n");
    }
}
