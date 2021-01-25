#include <stdio.h>
#define n 8

char simbolo[]= {'\xFA','\xDB','\xF8','\xAF',0}; //0-LIVRE , 1-PAREDE , 2-PASSOU, 3-CAMINHO;
int lab[][n] = {{0,1,0,1,0,1,0,1},
    {0,1,1,1,0,1,0,0},
    {0,0,0,0,0,1,0,1},
    {1,0,0,1,1,1,0,0},
    {0,0,1,0,0,0,0,1},
    {0,1,0,0,0,1,0,1},
    {0,0,0,1,1,1,0,1},
    {0,0,1,1,1,0,0,0}
};
int inicio[]= {0,0}, fim[]= {n-1,n-1};

void printa();
int caminho(int, int );

int main() {
    printf("\t    --Labirinto--\n\n");
    printa();
    if(caminho(inicio[0],inicio[1])) { //ou igual a 1 ou diferente de 0
        printf("\n\n\t--Labirinto: Solucao--\n\n");
        printa();
    } else {
        printf("\n\nImpossivel chegar no final do labirinto :(\nVoce esta perdido!\n\n");
        /* meu debug */
        printf("\n\n\t--Labirinto: Solucao--\n\n");
        printa();
    }
    return 0;
}

int caminho(int x, int y) {
    if(x==-1 || y==-1||x==n||y==n) //limites do tabuleiro
        return 0;//nao pode ser fim + 1
    else if(x==fim[0] && y==fim[1]) {
        lab[x][y]=simbolo[3];
        return 1;

    } else if(lab[x][y]==0) {
        lab[x][y]=simbolo[2];
        if(caminho(x+1,y)==1||caminho(x-1,y)==1||caminho(x,y+1)==1||caminho(x,y-1)==1) {
            lab[x][y]=simbolo[3];
            return 1;
        }
    } else
        return 0;
}
void printa() {
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            printf("%c    ", (lab[i][j]==0 || lab[i][j]==1)? simbolo[lab[i][j]]:(char) lab[i][j]);
        }
        printf("\n\n");
    }
}
