#ifndef LAYOUT_H
#define LAYOUT_H

#include <conio2.h>
#include "music.h"
#include <stdio.h>

#define SETA_CIMA 72
#define SETA_BAIXO 80
#define SETA_DIREITA 77
#define SETA_ESQUERDA 75

#define ENTER 13
#define ESC 27
#define ESPACE 32

#define COMPRIMENTO_TELA 120
#define COMPRIMENTO_TELA_MEDIO COMPRIMENTO_TELA/2
#define ALTURA_TELA 38
#define ALTURA_TELA_MEDIO ALTURA_TELA/2

#define GAME_X_0 16 + 1
#define GAME_Y_0 5

#define GAME_COMPRIMENTO 10
#define GAME_ALTURA 24
#define GAME_COMPRIMENTO_MEDIO GAME_COMPRIMENTO/2

#define TELINHA_X_0 GAME_X_0+ 2*GAME_COMPRIMENTO+1
#define TELINHA_Y_0 GAME_Y_0

#define TELINHA_COMPRIMENTO 11
#define TELINHA_ALTURA 9
#define TELINHA_COMPRIMENTO_MEDIO TELINHA_COMPRIMENTO/2
#define TELINHA_ALTURA_MEDIO TELINHA_ALTURA/2

#define BLOCOS 4

typedef struct {
	char *name;
	int SCORE, LINES;
}Record ;
void salvarRecord(Record *r,int numDeRecords){
	FILE *f;
	f = fopen("record.bin","wb");
	fwrite(r,sizeof(Record),numDeRecords,f);
	fclose(f);
}
void lerRecord(Record *r,int numDeRecords){
	FILE *f;
	f = fopen("record.bin","rb");
	fread(r,sizeof(Record),numDeRecords,f);
	fclose(f);
}

char tecla() {
    int aux=getch();
    return (aux == -32)? getch() : aux;
}
typedef struct {
    char novo;
    char copia;
} Buffer;

void printa_coordenadas() {
    printf("\n\twherex() = %i\twherey() = %i\n", wherex(), wherey());
}

void setCursorTipo(char aparece){
    HANDLE myHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO myCursor;
    myCursor.bVisible=aparece;
    myCursor.dwSize = 100;
    SetConsoleCursorInfo(myHandle,&myCursor);
}

typedef unsigned long long int Bytes8;
typedef struct LCG {
    Bytes8 a, c, m, rand_max, atual;
} LCG;
void semente(LCG * r, Bytes8 seed) {
    r->a = 0x5DEECE66DULL;
    r->c = 11ULL;
    r->m = (1ULL << 48);
    r->rand_max = r->m - 1;
    r->atual = seed;
}
Bytes8 lcg_rand(LCG * r) {
    r->atual = (r->a * r->atual + r->c) % r->m;
    return r->atual;
}
double lcg_rand_01(LCG * r) {
    return ((double) lcg_rand(r))/(r->rand_max);
}
void numero_aleatorio(int * numero, int min, float max, LCG * r) {
    *numero = (int) (max-min)*lcg_rand_01(r) + min;
}

void aviso(char msg[], int linha) {
    gotoxy(GAME_X_0 + GAME_COMPRIMENTO_MEDIO+1, linha+1);
    textbackground(BLACK);
    textcolor(LIGHTGRAY);
    printf("%s", msg);
    textbackground(BLACK);
    textcolor(BLACK);
}
void apaga_aviso(int linha) {
    gotoxy(GAME_X_0 + GAME_COMPRIMENTO_MEDIO -2, linha+1);
    textbackground(BLACK);
    textcolor(BLACK);
    printf("\t\t\t\t\t");
}
void thickBorders(int x_0, int xRight, int yUp, int yDown, char textura[], int color, int back_color) {
    int x,y;
    textbackground(back_color);
    textcolor(color);
    for(x=x_0; x<=xRight; x++) {
        for(y=yUp; y<=yDown; y++) {
            gotoxy(x,y);
            if((x==x_0 || x==xRight) && (y==yUp || y==yDown))
                printf("%s", textura);
            else if(y==yUp)
                printf("%s", textura);
            //printf("\xDF");
            else if(y==yDown) {
                printf("%s", textura);
                //printf("\xDC");
            } else if(x==x_0 || x==xRight)
                printf("%s", textura);
            else {
                textcolor(BLACK);
                printf("\xDB");
                textcolor(color);
            }

        }
    }
    textbackground(BLACK);
}
void thinBorders(int x_i, int x_f, int y_i, int y_f, int color, int back_color) {
    int x,y;
    textbackground(back_color);
    textcolor(color);
    for(x = x_i; x<=x_f; x++) {
        for(y=y_i; y <=y_f; y++) {
            gotoxy(x,y);
            if(x==x_i) {
                if(y==y_i)
                    printf("\xDA");
                else if(y==y_f)
                    printf("\xC0");
                else
                    printf("\xB3");
            } else if(x==x_f) {
                if(y==y_i)
                    printf("\xBF");
                else if(y==y_f)
                    printf("\xD9");
                else
                    printf("\xB3");
            } else if(y==y_i || y==y_f)
                printf("\xC4");
            else {
                textcolor(back_color);
                printf("\xDB");
                textcolor(color);
            }
        }
    }
}

int _T[][5]= {
    {1, 1, 1, 1, 1},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0}
};
int _E[][5]= {
    0, 1, 1, 1, 0,
    0, 1, 0, 0, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 0, 0,
    0, 1, 1, 1, 0
};
int _R[][5]= {
    0, 1, 1, 1, 0,
    0, 1, 0, 0, 1,
    0, 1, 1, 1, 1,
    0, 1, 0, 1, 0,
    0, 1, 0, 0, 1
};
int _I[][5]= {
    0, 1, 1, 1, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 1, 1, 1, 0
};
int _S[][5]= {
    0, 0, 1, 1, 1,
    0, 1, 0, 0, 0,
    0, 1, 1, 1, 1,
    0, 0, 0, 1, 0,
    1, 1, 1, 0, 0
};
int _X[][5]= {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};
void printaPalavra(char palavra[], int x_0, int y_0, int color) {
    int i, j, letra_palavra, **letra, x, y;
    for(letra_palavra=0; palavra[letra_palavra]; letra_palavra++) {
        switch(palavra[letra_palavra]) {
        case 'T':
        case 't':
            letra = _T;
            break;
        case 'E':
        case 'e':
            letra = _E;
            break;
        case 'R':
        case 'r':
            letra = _R;
            break;
        case 'I':
        case 'i':
            letra = _I;
            break;
        case 'S':
        case 's':
            letra = _S;
            break;
        case 'X':
        case 'x':
            letra = _X;
            break;
        }

        for(i=0; i<5; i++) {
            for(j=0; j<5; j++) {
                x=x_0+3*j+1;
                y=y_0+2*i+1;
                gotoxy(x, y);
                if(*(letra + 5*i +j)) {
                    thinBorders(x, x+2, y, y+1, color, BLACK);
                }
            }
        }
        x_0+=5*3+1;
    }
}

void inicioTETRIS() {
    clrscr();
    printaPalavra("TETRIS", COMPRIMENTO_TELA_MEDIO-50, 5, LIGHTCYAN);
    gotoxy(COMPRIMENTO_TELA_MEDIO-10, ALTURA_TELA-2);
    textcolor(LIGHTGRAY);
    printf("Press any key to continue");
    Beep(NOTE_C8, 100);
    Beep(NOTE_D8, 100);
    beep(5, 6, 0.8, 0, 0);
    clrscr();
}
void scanName(char *name) {

    clrscr();
    textcolor(LIGHTCYAN);
    gotoxy(COMPRIMENTO_TELA_MEDIO-9, ALTURA_TELA_MEDIO-2);
    printf("Digite seu nome: ");
    thinBorders(COMPRIMENTO_TELA_MEDIO-10, COMPRIMENTO_TELA_MEDIO+10, ALTURA_TELA_MEDIO-1, ALTURA_TELA_MEDIO+1, LIGHTCYAN, BLACK);
    beep(4, 6, 0.9, 0, 0);
    setCursorTipo(1);
    gotoxy(COMPRIMENTO_TELA_MEDIO-8, ALTURA_TELA_MEDIO);
    textcolor(LIGHTGRAY);
    fflush(stdin);
    fgets(name+1, 98, stdin);
    name[0]='*';
    clrscr();
    setCursorTipo(0);
}
void fimTETRIS(int interval) {
    textbackground(BLACK);
    clrscr();
    int line=0, espaco=6, altura_ideal = ALTURA_TELA_MEDIO-3, centraliza = 13;
    textcolor(LIGHTCYAN);
    line++;
    gotoxy(COMPRIMENTO_TELA_MEDIO-espaco+1, altura_ideal+line);
    printf("TETRIS");

    textcolor(LIGHTGRAY);
    line+=3;
    gotoxy(COMPRIMENTO_TELA_MEDIO-centraliza, altura_ideal+line);
    printf("Lesly Montufar");
    line++;
    gotoxy(COMPRIMENTO_TELA_MEDIO-centraliza, altura_ideal+line);
    printf("Ana Laura");
    line++;
    gotoxy(COMPRIMENTO_TELA_MEDIO-centraliza, altura_ideal+line);
    printf("UFU - Metodos e Tecnicas de Programacao");
    line++;
    gotoxy(COMPRIMENTO_TELA_MEDIO-centraliza, altura_ideal+line);
    printf("Professor: Luciano Xavier");

    Beep(NOTE_D8, 100);
    Beep(NOTE_C8, 100);

    delay(interval);
    clrscr();
}
#endif
