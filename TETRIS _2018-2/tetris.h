#ifndef TETRIS_H
#define TETRIS_H

#include "matriz.h"
#include <stdlib.h>
#include <time.h>
#include "layout.h"
#include <windows.h>

void game();

typedef struct {
    int x;
    int y;
} Cursor;
typedef struct {
    Cursor *position;
    int peca;
    int rotacao;
} Peca;
typedef struct {
    Cursor *pos_tela, maior_y, maior_x, menor_y, menor_x;
} Peca_Atual;

void static_info(char *name) {
    int posicao=1, line=0, i;
    Record neutro;
    neutro.name = "*newplayer";
    neutro.LINES = neutro.SCORE = 0;

    Record vetor[5];

//    for(i=0; i<5; i++) {
//         vetor[i].name = neutro.name;
//         vetor[i].LINES = neutro.LINES;
//         vetor[i].SCORE = neutro.SCORE;
//     }
//     salvarRecord(vetor, 5);
//     exit(0);

    Record allRecords[5];
    lerRecord(allRecords, 5);

    textbackground(BLACK);
    textcolor(LIGHTGRAY);
    gotoxy(75, 5+line);
    printf("RECORDS:");
    for(posicao=1; posicao<=5; posicao++) {
        line++;
        gotoxy(75, 5+2*line);
        printf("%i - ", posicao);
        gotoxy(79, 5+2*line);
        printf("%s", allRecords[posicao-1].name);
        gotoxy(95, 5+2*line);
        printf("%i\t%i", allRecords[posicao-1].LINES, allRecords[posicao-1].SCORE);
    }

    gotoxy(3, 3);
    printf("%s", name);

    int altura_ideal=5;
    gotoxy(3, altura_ideal+2);
    printf("P - PAUSE");
    gotoxy(3, altura_ideal+4);
    printf("T - TETRIS");
    gotoxy(3, altura_ideal+6);
    printf("L - LEVEL");
    gotoxy(3, altura_ideal+8);
    printf("C - CONTINUE");
    gotoxy(3, altura_ideal+10);
    printf("Q - QUIT");
}

void coletaRECORD(char *name, int LINES, int SCORE) {
    int i, posicao=6;
    Record record_atual;
    record_atual.name = name;
    record_atual.LINES = LINES;
    record_atual.SCORE = SCORE;

    Record neutro;
    neutro.name = "*newplayer";
    neutro.LINES = 0;
    neutro.SCORE = 0;

    Record vetor[5];
    lerRecord(vetor, 5);

    for(i=4; i>=0; i--) {
        if(record_atual.SCORE>vetor[i].SCORE) {
            posicao = i;
        }
    }

    if(posicao!=6) {
        for(i=4; i>posicao; i--) {
            vetor[i] = vetor[i-1];
        }
        vetor[posicao] = record_atual;
    }
    salvarRecord(vetor, 5);
}
void scanLVL(int *LVL) {
    setCursorTipo(1);
    do {
        textcolor(LIGHTGRAY);
        gotoxy(45,17);
        scanf("%i", LVL);
        if(*LVL<0 || *LVL>30) {
            apaga_aviso(2);
            aviso("LVL: 0 - 30", 2);
        }
    } while(*LVL<0 || *LVL>30);
    setCursorTipo(0);
}
void info(clock_t t, int LVL, int LINES, int SCORE) {
    textbackground(BLACK);
    textcolor(LIGHTGRAY);
    gotoxy(COMPRIMENTO_TELA-20, ALTURA_TELA-1);
    printf("%f seconds", ((float)t)/CLOCKS_PER_SEC);

    gotoxy(GAME_X_0 + 2*GAME_COMPRIMENTO + 2 + 1, GAME_Y_0 + 12);
    printf("LVL: %i", LVL);

    gotoxy(GAME_X_0 + 2*GAME_COMPRIMENTO + 2 + 1, GAME_Y_0 + 15);
    printf("LINES: %i", LINES);

    gotoxy(GAME_X_0 + 2*GAME_COMPRIMENTO + 2 + 1, GAME_Y_0 + 18);
    printf("SCORE: %i", SCORE);
}

void iniciar(int seconds) {
    clrscr();
    textcolor(LIGHTCYAN);
    int i;
    for(i=seconds; i>=1; i--) {
        gotoxy(COMPRIMENTO_TELA_MEDIO, ALTURA_TELA_MEDIO);
        printf("%i\a", i);
        delay(1000);
    }
    clrscr();
}
void GAME_OVER(char *name, int LINES, int SCORE) {
    coletaRECORD(name, LINES, SCORE);
    apaga_aviso(1);
    aviso("GAME OVER!", 1);
    Beep(NOTE_E6, 100);
    Beep(NOTE_D6, 100);
    Beep(NOTE_FS5, 200);
    Beep(NOTE_GS5, 200);

    Beep(NOTE_CS6, 100);
    Beep(NOTE_B5, 100);
    Beep(NOTE_E5, 200);
    Beep(NOTE_D5, 200);

    Beep(NOTE_B5, 100);
    Beep(NOTE_A5, 100);
    Beep(NOTE_CS5, 200);
    Beep(NOTE_E5, 200);

    Beep(NOTE_CS5, 200);
    Beep(NOTE_E5, 200);
    Beep(NOTE_A5, 200);
}
void menu(char _tecla, Buffer *bf, int *LVL, char *name, int LINES, int SCORE) {
    switch(_tecla) {
    case 'i':
    case 'I':
        inicioTETRIS(5000);
        game();
        break;

    case 'T':
    case 't':
        //GAME_OVER(SCORE);
        game();
        break;

    case 'P':
    case 'p':
        apaga_aviso(1);
        Beep(NOTE_C5, 100);
        aviso("PAUSE", 1);
        menu(tecla(), bf, LVL, name, LINES, SCORE);
        break;

    case 'c':
    case 'C':
        Beep(NOTE_C5, 100);
        apaga_aviso(1);
        aviso("CONTINUE!", 1);
        break;

    case 'l':
    case 'L':
        scanLVL(LVL);
        break;

    case ESC:
    case 'Q':
    case 'q':
        bf->copia = ESC;
        break;
    case 'g':
    case 'G': // o que colocar no game over? ...
        GAME_OVER(name, LINES, SCORE);
        menu('p', bf, LVL, name, LINES, SCORE);
        break;

    default:
        aviso("Opcao invalida!", 2);
        menu('p', bf, LVL, name, LINES, SCORE);
    }
}

void geraPeca(Peca p) {
    switch(p.peca) {
    case 1: //barra
        switch(p.rotacao) {
        case 0:
        case 2:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 0;
            p.position[1].y = 1;

            p.position[2].x = 0;
            p.position[2].y = 2;

            p.position[3].x = 0;
            p.position[3].y = 3;
            break;

        case 1:
        case 3:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 1;
            p.position[1].y = 0;

            p.position[2].x = 2;
            p.position[2].y = 0;

            p.position[3].x = 3;
            p.position[3].y = 0;
            break;
        }
        break;
    case 2: // quadrado
        switch(p.rotacao) {
        case 0:
        case 1:
        case 2:
        case 3:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 1;
            p.position[1].y = 0;

            p.position[2].x = 0;
            p.position[2].y = 1;

            p.position[3].x = 1;
            p.position[3].y = 1;
            break;
        }
        break;
    case 3: // escada cima
        switch(p.rotacao) {
        case 0:
        case 2: // escada cima 0
            p.position[0].x = 0;
            p.position[0].y = 2;

            p.position[1].x = 0;
            p.position[1].y = 1;

            p.position[2].x = 1;
            p.position[2].y = 0;

            p.position[3].x = 1;
            p.position[3].y = 1;
            break;

        case 1:
        case 3:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 1;
            p.position[1].y = 0;

            p.position[2].x = 1;
            p.position[2].y = 1;

            p.position[3].x = 2;
            p.position[3].y = 1;
            break;
        }
        break;
    case 4: // escada baixo
        switch(p.rotacao) {
        case 0:
        case 2:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 0;
            p.position[1].y = 1;

            p.position[2].x = 1;
            p.position[2].y = 1;

            p.position[3].x = 1;
            p.position[3].y = 2;
            break;

        case 1:
        case 3:
            p.position[0].x = 0;
            p.position[0].y = 1;

            p.position[1].x = 1;
            p.position[1].y = 1;

            p.position[2].x = 1;
            p.position[2].y = 0;

            p.position[3].x = 2;
            p.position[3].y = 0;
            break;
        }
        break;
    case 5: // L invertido
        switch(p.rotacao) {
        case 0:
            p.position[0].x = 0;
            p.position[0].y = 2;

            p.position[1].x = 1;
            p.position[1].y = 2;

            p.position[2].x = 1;
            p.position[2].y = 1;

            p.position[3].x = 1;
            p.position[3].y = 0;
            break;
        case 1:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 0;
            p.position[1].y = 1;

            p.position[2].x = 1;
            p.position[2].y = 1;

            p.position[3].x = 2;
            p.position[3].y = 1;
            break;

        case 2:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 0;
            p.position[1].y = 1;

            p.position[2].x = 0;
            p.position[2].y = 2;

            p.position[3].x = 1;
            p.position[3].y = 0;
            break;
        case 3:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 1;
            p.position[1].y = 0;

            p.position[2].x = 2;
            p.position[2].y = 0;

            p.position[3].x = 2;
            p.position[3].y = 1;
            break;
        }
        break;
    case 6: // L
        switch(p.rotacao) {
        case 0:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 0;
            p.position[1].y = 1;

            p.position[2].x = 0;
            p.position[2].y = 2;

            p.position[3].x = 1;
            p.position[3].y = 2;
            break;
        case 1:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 0;
            p.position[1].y = 1;

            p.position[2].x = 1;
            p.position[2].y = 0;

            p.position[3].x = 2;
            p.position[3].y = 0;
            break;

        case 2:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 1;
            p.position[1].y = 0;

            p.position[2].x = 1;
            p.position[2].y = 1;

            p.position[3].x = 1;
            p.position[3].y = 2;
            break;
        case 3:
            p.position[0].x = 0;
            p.position[0].y = 1;

            p.position[1].x = 1;
            p.position[1].y = 1;

            p.position[2].x = 2;
            p.position[2].y = 1;

            p.position[3].x = 2;
            p.position[3].y = 0;
            break;
        }
        break;
    case 7: // mesinha
        switch(p.rotacao) {
        case 0:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 0;
            p.position[1].y = 1;

            p.position[2].x = 0;
            p.position[2].y = 2;

            p.position[3].x = 1;
            p.position[3].y = 1;
            break;
        case 1:
            p.position[0].x = 0;
            p.position[0].y = 0;

            p.position[1].x = 1;
            p.position[1].y = 0;

            p.position[2].x = 2;
            p.position[2].y = 0;

            p.position[3].x = 1;
            p.position[3].y = 1;
            break;

        case 2:
            p.position[0].x = 1;
            p.position[0].y = 0;

            p.position[1].x = 1;
            p.position[1].y = 1;

            p.position[2].x = 1;
            p.position[2].y = 2;

            p.position[3].x = 0;
            p.position[3].y = 1;
            break;
        case 3:
            p.position[0].x = 1;
            p.position[0].y = 0;

            p.position[1].x = 0;
            p.position[1].y = 1;

            p.position[2].x = 1;
            p.position[2].y = 1;

            p.position[3].x = 2;
            p.position[3].y = 1;
            break;
        }
        break;
    }
}
void print_peca_na_tela(int peca, Cursor pos_tela[], Matriz tela) {
    int i=0;
    for(i=0; i<BLOCOS; i++) {
        tela.m[pos_tela[i].y][pos_tela[i].x] = peca;
    }
}
int mesmaPeca(Cursor pos_tela[], int y, int x) {
    int i;
    for(i=0; i<BLOCOS; i++) {
        if(x == pos_tela[i].x && y == pos_tela[i].y)
            return 1;
    }
    return 0;
}
void limpaPecaAnterior(Cursor pos_tela[], Matriz tela, char direcao) {
    int i;
    for(i=0; i<BLOCOS; i++) {
        if(direcao == 'e') {
            tela.m[pos_tela[i].y][pos_tela[i].x+1] = 0;
        } else if(direcao == 'd') {
            tela.m[pos_tela[i].y][pos_tela[i].x-1] = 0;
        } else if(direcao == 'b' && mesmaPeca(pos_tela, pos_tela[i].y-1, pos_tela[i].x)!= 1) { // ou mesmaPeca()==0 ou !mesmaPeca()
            tela.m[pos_tela[i].y-1][pos_tela[i].x] = 0;
        } else if(direcao == 'r') { // ou mesmaPeca()==0 ou !mesmaPeca()
            tela.m[pos_tela[i].y][pos_tela[i].x] = 0;
        } else if(direcao == 't') {
            tela.m[pos_tela[i].y][pos_tela[i].x] = 0;
        }
    }
}
void maior_menor(Peca_Atual p_mov, Cursor *maior_x, Cursor *maior_y, Cursor *menor_x, Cursor *menor_y) {
    maior_y->y = maior_x->x = 0;
    menor_y->y = menor_x->x = GAME_ALTURA; // numero grande aleatorio
    int i;
    for(i=0; i<BLOCOS; i++) {
        if(maior_y->y < p_mov.pos_tela[i].y) {
            maior_y->x = p_mov.pos_tela[i].x;
            maior_y->y = p_mov.pos_tela[i].y;
        }
        if(maior_x->x < p_mov.pos_tela[i].x) {
            maior_x->x = p_mov.pos_tela[i].x;
            maior_x->y = p_mov.pos_tela[i].y;
        }
        if(menor_y->y > p_mov.pos_tela[i].y) {
            menor_y->x = p_mov.pos_tela[i].x;
            menor_y->y = p_mov.pos_tela[i].y;
        }
        if(menor_x->x > p_mov.pos_tela[i].x) {
            menor_x->x = p_mov.pos_tela[i].x;
            menor_x->y = p_mov.pos_tela[i].y;
        }
    }
}
void posicionaPeca(Peca p, Peca_Atual p_mov, int pos_x, int pos_y) {
    int i;
    for(i=0; i<BLOCOS; i++) {
        p_mov.pos_tela[i].x = pos_x + p.position[i].x;
        p_mov.pos_tela[i].y = pos_y + p.position[i].y; // nao se soma 1, porque depois ela vai para 'b'
    }
}
void deslocaPeca(Cursor pos_tela[], char direcao) {
    int i;
    for(i=0; i<BLOCOS; i++) {
        if(direcao== 'e') {
            pos_tela[i].x--;
        } else if(direcao == 'd') {
            pos_tela[i].x++;
        } else if(direcao == 'b') {
            pos_tela[i].y++;
        }
    }
}
int posicoesNaDirecaoVazia(Peca_Atual p_mov, Matriz tela, char direcao) {
    int i;
    for(i=0; i<BLOCOS; i++) {
        if(direcao=='e' && !mesmaPeca(p_mov.pos_tela, p_mov.pos_tela[i].y, p_mov.pos_tela[i].x-1)) {
            if(tela.m[p_mov.pos_tela[i].y][p_mov.pos_tela[i].x-1] != 0)
                return 0;
        } else if(direcao=='d' && !mesmaPeca(p_mov.pos_tela, p_mov.pos_tela[i].y, p_mov.pos_tela[i].x+1)) {
            if(tela.m[p_mov.pos_tela[i].y][p_mov.pos_tela[i].x+1] != 0)
                return 0;
        } else if(direcao=='b'&& !mesmaPeca(p_mov.pos_tela, p_mov.pos_tela[i].y+1, p_mov.pos_tela[i].x)) {
            if(tela.m[p_mov.pos_tela[i].y+1][p_mov.pos_tela[i].x] != 0)
                return 0;
        }
    }
    return 1;
}
int espacoVazio(Peca_Atual p_mov, Matriz tela, char direcao) {
    int i;
    for(i=0; i<BLOCOS; i++) {
        if(direcao == 'e') {
            if(p_mov.menor_x.x == 0 || posicoesNaDirecaoVazia(p_mov, tela, direcao)==0) // o mais a esquera é o menor x, valor min = 0
                return 0;
        } else if(direcao == 'd') {
            //nao preciso saber o numero de linhas e colunas da tela, porque ela é do tipo Matriz
            if(p_mov.maior_x.x+1 == tela.col || posicoesNaDirecaoVazia(p_mov, tela, direcao)==0)
                return 0;
        } else if(direcao == 'b') {
            if(p_mov.maior_y.y >= tela.lin-1 || posicoesNaDirecaoVazia(p_mov, tela, direcao)==0)
                return 0;
        }
    }
    return 1;
}
int linhaCompleta(int linha, Matriz tela) {
    int i;
    for(i=0; i<tela.col; i++) {
        if(tela.m[linha][i]==0)
            return 0;
    }
    return 1;
}
void eliminaLinha(int linha, Matriz tela) { // funciona
    int i;
    if(linha>1) {
        for(i=0; i<tela.col; i++) {
            tela.m[linha][i] = tela.m[linha-1][i];
        }
        eliminaLinha(linha-1, tela);
    } else if(linha==0) {
        for(i=0; i<tela.col; i++) {
            tela.m[linha][i] = 0;
        }
    }
}
int contaPontos(int *nivel, int *linhas_completas, Peca_Atual p_mov, Matriz tela) {
    int linha=0, pontos_linha, i, score_acumulado;
    for(i=p_mov.menor_y.y; i<=p_mov.maior_y.y; i++) {
        if(linhaCompleta(i, tela)==1) {
            eliminaLinha(i, tela);
            linha++;
        }
    }
    switch(linha) {
    case 1:
        Beep(NOTE_E6, 100);
        Beep(NOTE_D6, 100);
        Beep(NOTE_FS5, 200);
        Beep(NOTE_GS5, 200);
        break;
    case 2:
        Beep(NOTE_CS6, 100);
        Beep(NOTE_B5, 100);
        Beep(NOTE_E5, 200);
        Beep(NOTE_D5, 200);
        break;
    case 3:
        Beep(NOTE_B5, 100);
        Beep(NOTE_A5, 100);
        Beep(NOTE_CS5, 200);
        Beep(NOTE_E5, 200);
        break;
    case 4:
        Beep(NOTE_CS5, 200);
        Beep(NOTE_E5, 200);
        Beep(NOTE_A5, 200);
        break;

    }
    *linhas_completas += linha;
    // a variavel pontos_linha foi criada para melhor compreensao da contagem dos pontos
    switch(linha) {
    case 0:
        pontos_linha = 0;
        break;
    case 1:
        pontos_linha=40;
        break;
    case 2:
        pontos_linha=100;
        break;
    case 3:
        pontos_linha=300;
        break;
    case 4:
        pontos_linha=1200;
    }
    score_acumulado = pontos_linha*(*nivel+1);

    if(linha>0 && *linhas_completas%10==0 && *linhas_completas!=0) {
        *nivel = *nivel + 1;
        Beep(NOTE_F7, 100);
        Beep(NOTE_A7, 100);
        Beep(NOTE_C8, 100);
    }

    return score_acumulado;
}
int defineTimer(int nivel) {
    return 1000 - nivel*33;
}
int espacoVazioRotacao(Peca_Atual p_mov, Matriz tela, Peca p) {
    Peca aux;
    aux.peca = p.peca;
    aux.rotacao = (p.rotacao==3)? 0 : p.rotacao+1;
    int i;
    Cursor c_anterior = p_mov.maior_y;
    Cursor *pos_tela = p_mov.pos_tela;
    if(c_anterior.x<2)
        c_anterior.x=2;
    else if(c_anterior.x>tela.col-3) {
        c_anterior.x-=3;
        if(aux.peca==1)
            c_anterior.x--;
    }
    aux.position = (Cursor *) calloc(BLOCOS, sizeof(Cursor));
    geraPeca(aux);
    for(i=0; i<BLOCOS; i++) {
        if(!mesmaPeca(pos_tela, c_anterior.y-2 + aux.position[i].y, c_anterior.x + aux.position[i].x)) {
            if(tela.m[c_anterior.x + aux.position[i].x][c_anterior.y-2 + aux.position[i].y] != 0 || c_anterior.x + aux.position[i].x>tela.col-1) {
                return 0;
            }
        }
    }
    free(aux.position);
    return 1;
}
void game() {
    int nivel = 0, timer = defineTimer(nivel), score=0, linhas_completas=0, timer2, G_OVER = 0;
    Buffer bf;
    char name[100];
    scanName(name);

    thinBorders(GAME_X_0, GAME_X_0 + 2*GAME_COMPRIMENTO, GAME_Y_0, GAME_Y_0 + GAME_ALTURA + 1, LIGHTCYAN, BLACK);
    thinBorders(GAME_X_0 + 2*GAME_COMPRIMENTO + 1, GAME_X_0 + 2*GAME_COMPRIMENTO + 2 +2*10+1, GAME_Y_0, GAME_Y_0 + 10, LIGHTCYAN, BLACK);
    thinBorders(GAME_X_0 + 2*GAME_COMPRIMENTO + 1, GAME_X_0 + 2*GAME_COMPRIMENTO + 2 +2*10+1, GAME_Y_0+11, GAME_Y_0 + 13, LIGHTCYAN, BLACK);
    thinBorders(GAME_X_0 + 2*GAME_COMPRIMENTO + 1, GAME_X_0 + 2*GAME_COMPRIMENTO + 2 +2*10+1, GAME_Y_0+14, GAME_Y_0 + 16, LIGHTCYAN, BLACK);
    thinBorders(GAME_X_0 + 2*GAME_COMPRIMENTO + 1, GAME_X_0 + 2*GAME_COMPRIMENTO + 2 +2*10+1, GAME_Y_0+17, GAME_Y_0 + 19, LIGHTCYAN, BLACK);

    gotoxy(GAME_X_0+GAME_COMPRIMENTO_MEDIO+3, GAME_Y_0 + GAME_ALTURA/2);
    textcolor(LIGHTGRAY);
    printf("TETRIS");

    gotoxy(GAME_X_0 + 2*GAME_COMPRIMENTO + 10, GAME_Y_0 + 5); //(10/2)==5
    textcolor(LIGHTGRAY);
    printf("TETRIS");

    info(clock(), nivel, linhas_completas, score);
    static_info(name);
    scanLVL(&nivel);

    iniciar(3);
    static_info(name);
    /* desenha o ambiente*/
    thinBorders(GAME_X_0, GAME_X_0 + 2*GAME_COMPRIMENTO, GAME_Y_0, GAME_Y_0 + GAME_ALTURA + 1, LIGHTCYAN, BLACK);
    thinBorders(GAME_X_0 + 2*GAME_COMPRIMENTO + 1, GAME_X_0 + 2*GAME_COMPRIMENTO + 2 +2*10+1, GAME_Y_0, GAME_Y_0 + 10, LIGHTCYAN, BLACK);
    thinBorders(GAME_X_0 + 2*GAME_COMPRIMENTO + 1, GAME_X_0 + 2*GAME_COMPRIMENTO + 2 +2*10+1, GAME_Y_0+11, GAME_Y_0 + 13, LIGHTCYAN, BLACK);
    thinBorders(GAME_X_0 + 2*GAME_COMPRIMENTO + 1, GAME_X_0 + 2*GAME_COMPRIMENTO + 2 +2*10+1, GAME_Y_0+14, GAME_Y_0 + 16, LIGHTCYAN, BLACK);
    thinBorders(GAME_X_0 + 2*GAME_COMPRIMENTO + 1, GAME_X_0 + 2*GAME_COMPRIMENTO + 2 +2*10+1, GAME_Y_0+17, GAME_Y_0 + 19, LIGHTCYAN, BLACK);
    info(clock(), nivel, linhas_completas, score);


    clock_t t = clock(), t2 = clock();
    srand(time(0));
    LCG random;
    semente(&random, rand()); // bem aleatório

    Matriz tela = criarMatriz(GAME_ALTURA, GAME_COMPRIMENTO);
    Matriz telinha = criarMatriz(TELINHA_ALTURA, TELINHA_COMPRIMENTO);
    Cursor c_anterior;

    Peca_Atual p_mov, posicoes_proxima_peca;
    Peca p, proxima_peca;
    posicoes_proxima_peca.pos_tela = proxima_peca.position = (Cursor *) calloc(BLOCOS, sizeof(Cursor));
    p_mov.pos_tela = p.position = (Cursor *) calloc(BLOCOS, sizeof(Cursor));

    /* primeira peca */
    numero_aleatorio(&p.peca, 1, 8, &random);
    p.rotacao = 0;
    geraPeca(p);
    posicionaPeca(p, p_mov, GAME_COMPRIMENTO_MEDIO - 1, 0);
    maior_menor(p_mov, &p_mov.maior_x, &p_mov.maior_y, &p_mov.menor_x, &p_mov.menor_y); /*tira o lixo de memoria do maior e do menor*/

    /* proxima peca aleatoria */
    numero_aleatorio(&proxima_peca.peca, 1, 7, &random);
    proxima_peca.rotacao = 0;
    geraPeca(proxima_peca); // altero o p.position
    posicionaPeca(proxima_peca, posicoes_proxima_peca, TELINHA_COMPRIMENTO_MEDIO, TELINHA_ALTURA_MEDIO);
    maior_menor(posicoes_proxima_peca, &posicoes_proxima_peca.maior_x, &posicoes_proxima_peca.menor_y, &posicoes_proxima_peca.menor_x, &posicoes_proxima_peca.menor_y);

    print_peca_na_tela(proxima_peca.peca, posicoes_proxima_peca.pos_tela, telinha);
    imprimirMatriz(telinha, TELINHA_X_0, TELINHA_Y_0);

    do {
        timer = defineTimer(nivel); // defino timer do nivel
        timer2 = 24*defineTimer(nivel)*0.3;
        info(clock(), nivel, linhas_completas, score); // printo clock() deve ser printado com frequencia
        maior_menor(p_mov, &p_mov.maior_x, &p_mov.maior_y, &p_mov.menor_x, &p_mov.menor_y); /*modifica as coord do maior e do menor*/

        if(kbhit()) {
            bf.novo=tecla();
            bf.copia=bf.novo;
            //if(bf.copia == SETA_CIMA && espacoVazioRotacao(p_mov, tela, p)) { // descomentar
            if(bf.copia == SETA_CIMA) {
                limpaPecaAnterior(p_mov.pos_tela, tela, 'r'); // a rotacao mudou mas o limpa nao sabe porque inda nao foi gerado
                p.rotacao = (p.rotacao==3)? 0 : p.rotacao+1;
                c_anterior = p_mov.maior_y; //mudei para maior

                geraPeca(p); // coloco as coordenadas da peca de acordo com sua rotacao;

                if(c_anterior.x<2) // evita que ultrapasse os limites da tela.m
                    c_anterior.x=2;
                else if(c_anterior.x>tela.col-3) {
                    c_anterior.x-=3;
                    if(p.peca==1) // se for barra vai mais um para o lado
                        c_anterior.x--;
                }
                posicionaPeca(p, p_mov, c_anterior.x, c_anterior.y-2); // posiciono
                timer = 0; // para fazer a peca descer

            } else if(bf.copia=='p') {
                menu('p',&bf, &nivel, name, linhas_completas, score);
            } else if(bf.copia==SETA_DIREITA && espacoVazio(p_mov, tela, 'd') == 1) {
                deslocaPeca(p_mov.pos_tela, 'd');
                limpaPecaAnterior(p_mov.pos_tela, tela, 'd');
            } else if(bf.copia==SETA_ESQUERDA && espacoVazio(p_mov, tela, 'e') == 1) {
                deslocaPeca(p_mov.pos_tela, 'e');
                limpaPecaAnterior(p_mov.pos_tela, tela, 'e');
            } else if(bf.copia==SETA_BAIXO && espacoVazio(p_mov, tela, 'b') == 1) {
                timer=0;
            }
        }
        print_peca_na_tela(p.peca, p_mov.pos_tela, tela); // printo a peca na tela _ modificando a tela
        imprimirMatriz(tela, GAME_X_0, GAME_Y_0); // printa o game_over se for preciso


        if(!espacoVazio(p_mov, tela, 'b')) { // tem que verificar primeiro se para baixo está vazio
            if(!espacoVazio(p_mov, tela, 'e') && !espacoVazio(p_mov, tela, 'd'))
                timer2 = 0;
            if(clock()-t2>=timer2) {
                t2 = clock();
                score += contaPontos(&nivel, &linhas_completas, p_mov, tela); // elimina linha antes de verificar Game_Over
                info(clock(), nivel, linhas_completas, score);

                if(p_mov.menor_y.y==0) { // GAME_OVER
                    G_OVER = 1;
                    menu('g', &bf, &nivel, name, linhas_completas, score);
                } else {
                    limpaPecaAnterior(posicoes_proxima_peca.pos_tela, telinha, 't');
                    p.peca=proxima_peca.peca;
                    p.rotacao=proxima_peca.rotacao;
                    geraPeca(p);
                    posicionaPeca(p, p_mov, GAME_COMPRIMENTO_MEDIO - 1, 0); // soma com as coordenadas informadas

                    numero_aleatorio(&proxima_peca.peca, 1, 8, &random);
                    proxima_peca.rotacao = 0;
                    geraPeca(proxima_peca);
                    posicionaPeca(proxima_peca, posicoes_proxima_peca, TELINHA_COMPRIMENTO_MEDIO, TELINHA_ALTURA_MEDIO-2);
                    //maior_menor(posicoes_proxima_peca, &posicoes_proxima_peca.maior_x, &posicoes_proxima_peca.menor_y, &posicoes_proxima_peca.menor_x, &posicoes_proxima_peca.menor_y);
                    print_peca_na_tela(proxima_peca.peca, posicoes_proxima_peca.pos_tela, telinha);
                    imprimirMatriz(telinha, TELINHA_X_0, TELINHA_Y_0);
                }
                timer2 = 24*defineTimer(nivel)*0.3;
            }
        } else if(clock()-t >= timer) { // só precisa da pausa para descer e o clock permite que execuçao dos códigos anteriores
            t=clock();
            deslocaPeca(p_mov.pos_tela, 'b'); // envio o pos_tela da Peca_Atual p_mov
            limpaPecaAnterior(p_mov.pos_tela, tela, 'b'); // tela.m já é ponteiro
        }

        if(bf.copia==ESC) { // tem que destruir aqui!
            if(!G_OVER)
                coletaRECORD(name, linhas_completas, score);
            destruirMatriz(tela);
            free(p.position);
            free(p_mov.pos_tela);

            destruirMatriz(telinha);
            free(proxima_peca.position);
            free(posicoes_proxima_peca.pos_tela);

            fimTETRIS(3000);
            exit(0);
        }
    } while(bf.copia!=ESC);
}
#endif
