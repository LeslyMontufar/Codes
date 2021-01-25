#ifndef GRXPHICS_H // se essa biblioteca nao existe nesse projeto ainda
#define GRXPHICS_H // define esta biblioteca como GRXPHICS_H

//nao precisei declarar a conio2 aqui

#define SETA_CIMA 72
#define SETA_BAIXO 80
#define SETA_DIREITA 77
#define SETA_ESQUERDA 75

/*somente um caractere*/
#define ENTER 13
#define ESC 27

/*atalhos para o gotoxy()*/
#define ESPACO_TAB 9

/*informacoes da tela*/
#define CENTRAL_X 33
#define COMPRIMENTO_TELA 80
#define COMPRIMENTO_TELA_MEDIO COMPRIMENTO_TELA/2
#define ALTURA_TELA 39

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

void colors() {
    clrscr();
    int text_color, text_background, line=1;
    textcolor(WHITE);

    gotoxy(ESPACO_TAB, line+=2);
    printf("COLORS:");

    gotoxy(ESPACO_TAB, line+=2);
    printf("0 - BLACK");
    gotoxy(ESPACO_TAB, ++line);
    printf("1 - BLUE");
    gotoxy(ESPACO_TAB, ++line);
    printf("2 - GREEN");
    gotoxy(ESPACO_TAB, ++line);
    printf("3 - CYAN");
    gotoxy(ESPACO_TAB, ++line);
    printf("4 - RED");
    gotoxy(ESPACO_TAB, ++line);
    printf("5 - MAGENTA");
    gotoxy(ESPACO_TAB, ++line);
    printf("6 - BROWN");
    gotoxy(ESPACO_TAB, ++line);
    printf("7 - LIGHTGRAY");
    gotoxy(ESPACO_TAB, ++line);
    printf("8 - DARKGRAY");
    gotoxy(ESPACO_TAB, ++line);
    printf("9 - LIGHTBLUE");
    gotoxy(ESPACO_TAB, ++line);
    printf("10 - LIGHTGREEN");
    gotoxy(ESPACO_TAB, ++line);
    printf("11 - LIGHTCYAN");
    gotoxy(ESPACO_TAB, ++line);
    printf("12 - LIGHTRED");
    gotoxy(ESPACO_TAB, ++line);
    printf("13 - LIGHTMAGENTA");
    gotoxy(ESPACO_TAB, ++line);
    printf("14 - YELLOW");
    gotoxy(ESPACO_TAB, ++line);
    printf("15 - WHITE");

    int color, texture, i, j;
    line=1;
    gotoxy(COMPRIMENTO_TELA_MEDIO, line+=2);
    printf("TEXTURES:");

    gotoxy(COMPRIMENTO_TELA_MEDIO, line+=2);
    printf("\xAE - AE");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xAF - AF");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xB0 - B0");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xB1 - B1");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xB2 - B2");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xDB - DB");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xDC - DC");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xDD - DD");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xDE - DE");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xDF - DF");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xF0 - F0");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xF1 - F1");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xF8 - F8");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xF9 - F9");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xFE - FE");
    gotoxy(COMPRIMENTO_TELA_MEDIO, ++line);
    printf("\xFF - FF");

    do {
        gotoxy(ESPACO_TAB, 23);
        clreol();
        printf("text_background: ");

        gotoxy(ESPACO_TAB, 25);
        clreol();
        printf("text_color: ");

        gotoxy(COMPRIMENTO_TELA_MEDIO, 23);
        clreol();
        printf("texture: ");

        gotoxy(COMPRIMENTO_TELA_MEDIO, 25);
        clreol();
        printf("color: ");

        /*COLORS*/
        gotoxy(26, 23);
        scanf("%i", &text_background);

        gotoxy(21, 25);
        scanf("%i", &text_color);

        textbackground(text_background);
        textcolor(text_color);
        gotoxy(ESPACO_TAB, 28);
        printf("Hello World!");

        /*TEXTURES*/
        gotoxy(49, 23);
        scanf("%x", &texture); // recebe como hex, mas poderia ter sido como int

        gotoxy(47, 25);
        scanf("%i", &color);

        textcolor(color);
        for(i=0; i<4; i++) {
            for(j=0; j<8; j++) {
                gotoxy(COMPRIMENTO_TELA_MEDIO+j, 28+i);
                printf("%c", texture); // na tabela asc ii: Dec Hex *Char*
            }
        }

        textbackground(BLACK);
        textcolor(WHITE);
    } while(tecla()!=ESC);

    textbackground(BLACK);
    textcolor(BLACK);
    clrscr();
}

void thickBorders(int xLeft, int xRight, int yUp, int yDown, char textura[], int color) {
    int x,y;
    textcolor(color);
    for(x=xLeft; x<=xRight; x++) {
        for(y=yUp; y<=yDown; y++) {
            gotoxy(x,y);
            if((x==xLeft || x==xRight) && (y==yUp || y==yDown))
                printf("%s", textura);
            else if(y==yUp)
                printf("%s", textura);
            //printf("\xDF");
            else if(y==yDown) {
                printf("%s", textura);
                //printf("\xDC");
            } else if(x==xRight || x==xLeft)
                printf("%s", textura);
        }
    }
}
void thinBorders(int xLeft, int xRight, int yUp, int yDown, int color) {
    int x,y;
    textcolor(color);
    for(x=xLeft; x<=xRight; x++) {
        for(y=yUp; y<=yDown; y++) {
            gotoxy(x,y);
            if(x==xLeft) {
                if(y==yUp)
                    printf("\xDA");
                else if(y==yDown)
                    printf("\xC0");
                else
                    printf("\xB3");//barras verticais
            } else if(x==xRight) {
                if(y==yUp)
                    printf("\xBF");
                else if(y==yDown)
                    printf("\xD9");
                else
                    printf("\xB3");//barras verticais
            } else if(y==yUp || y==yDown) //barras horizontais
                printf("\xC4");
        }
    }
}

void fill_display(char textura[], int _delay, int color) {
    int i, j;
    for(i=0; i<ALTURA_TELA; i++) {
        for(j=0; j<COMPRIMENTO_TELA; j++) {
            gotoxy(j+1, i+1);
            textcolor(color);
            printf("%s", textura);
            delay(_delay);
        }
    }
}
#endif // GRXPHICS_H
