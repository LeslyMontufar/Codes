#ifndef MUSIC_H
#define MUSIC_H

#include <windows.h>
#include <conio2.h>
#include "layout.h"

#define COMPRIMENTO_TELA 120
#define ALTURA_TELA 38

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int B[]= {NOTE_B0, NOTE_B1, NOTE_B2, NOTE_B3, NOTE_B4, NOTE_B5, NOTE_B6, NOTE_B7, 0};
int C[]= {0, NOTE_C1, NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5, NOTE_C6, NOTE_C7, NOTE_C8};
int CS[]= { 0,  NOTE_CS1, NOTE_CS2, NOTE_CS3, NOTE_CS4, NOTE_CS5, NOTE_CS6, NOTE_CS7, NOTE_CS8};
int D[]= {  0,  NOTE_D1, NOTE_D2, NOTE_D3, NOTE_D4, NOTE_D5, NOTE_D6, NOTE_D7,       NOTE_D8};
int DS[]= {  0,  NOTE_DS1, NOTE_DS2, NOTE_DS3, NOTE_DS4, NOTE_DS5, NOTE_DS6, NOTE_DS7, NOTE_DS8};
int E[]= {  0,  NOTE_E1, NOTE_E2, NOTE_E3, NOTE_E4, NOTE_E5, NOTE_E6, NOTE_E7, 0};
int F[]= {  0,  NOTE_F1, NOTE_F2, NOTE_F3, NOTE_F4, NOTE_F5, NOTE_F6, NOTE_F7, 0};
int FS[]= {  0,  NOTE_FS1, NOTE_FS2, NOTE_FS3, NOTE_FS4, NOTE_FS5, NOTE_FS6, NOTE_FS7, 0};
int G[]= {  0,  NOTE_G1, NOTE_G2, NOTE_G3, NOTE_G4, NOTE_G5, NOTE_G6, NOTE_G7, 0};
int GS[]= {  0,  NOTE_GS1, NOTE_GS2, NOTE_GS3, NOTE_GS4, NOTE_GS5, NOTE_GS6, NOTE_GS7, 0};
int A[]= {  0,  NOTE_A1, NOTE_A2, NOTE_A3, NOTE_A4, NOTE_A5, NOTE_A6, NOTE_A7, 0};
int AS[]= {  0,  NOTE_AS1, NOTE_AS2, NOTE_AS3, NOTE_AS4, NOTE_AS5, NOTE_AS6, NOTE_AS7, 0};

typedef struct {
    int *som, *tempo, tamanho;
} Musica;

void beep(int track, const int i, float duracao, int primeira_nota, int n) {
    int nota;

    int ode[] = {E[i], E[i], F[i], G[i], G[i], F[i], E[i], D[i], C[i], C[i], D[i], E[i], E[i], D[i], D[i]};
    int ode_delay[] = {250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 100, 300};

    int nokia[] = {E[i], D[i], FS[i-1], GS[i-1],
                   CS[i], B[i-1], E[i-1], D[i-1],
                   B[i-1], A[i-1], CS[i-1], E[i-1],
                   CS[i], E[i-1], A[i-1]
                  };
    int nokia_delay[] = {8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4, 4, 4};

    int korobeiniki[] = {E[i], B[i-1], C[i], D[i], C[i], B[i-1], A[i-1], A[i-1], C[i], E[i]};
    int korobeiniki_delay[] = {300, 150, 150, 250, 150, 150, 250, 150, 150, 250};

    int allStar[] = {FS[i], CS[i+1], AS[i], AS[i], GS[i], FS[i], FS[i], B[i],
                     AS[i], AS[i], GS[i], GS[i], FS[i], FS[i], CS[i+1], AS[i], AS[i], GS[i],
                     FS[i], FS[i], DS[i], CS[i]
                    };
    int allStar_delay[] = {400, 200, 200, 300, 200, 200, 200, 400,
                           200, 200, 300, 200, 200, 200, 300, 150,
                           200, 200, 200, 200
                          };

    int mimi1[] = {E[i], B[i-1], C[i], D[i], C[i], B[i-1], A[i-1], A[i-1], C[i], E[i],
                   D[i], C[i], B[i-1],B[i-1], C[i], D[i], E[i], C[i], A[i-1], A[i-1], D[i], F[i], A[i],
                   G[i], F[i], E[i], C[i], E[i], D[i], C[i], B[i-1], B[i-1], C[i],
                   D[i], E[i], C[i], A[i-1], A[i-1], E[i], B[i-1], C[i], D[i], E[i],
                   C[i], A[i-1], C[i], E[i], A[i], GS[i], F[i], E[i], D[i], C[i],
                   E[i], DS[i], D[i], CS[i], C[i], A[i-1], B[i-1], C[i], A[i-1], B[i-1],
                   GS[i-1], A[i-1], B[i-1], GS[i-1], A[i-1], G[i-1], F[i-1], D[i-1], A[i-1], G[i-1],
                   F[i-1], D[i-1], E[i-1],F[i-1],G[i-1],A[i-1],B[i-1],C[i],D[i],E[i],
                   F[i], G[i], A[i], B[i], C[i+1], D[i+1], E[i+1], E[i],  B[i-1], C[i],
                   D[i], C[i], B[i-1], A[i-1], A[i-1], C[i], E[i],D[i], C[i], B[i-1],
                   B[i-1], C[i], D[i], E[i], C[i], A[i-1], A[i-1],E[i],C[i],D[i],
                   B[i-1], C[i], A[i-1], GS[i-1], B[i-1], E[i],C[i],D[i],
                   A[i-1],C[i],F[i],F[i],E[i]
                  }; // 80 notas!
    int mimi1_delay[] = {2, 4, 4, 3, 4, 4, 3, 4, 4, 3,
                         4, 4, 3, 4, 4, 3, 3, 3, 3, 1, 3, 4, 3,
                         4, 3, 3, 4, 3, 4, 4, 3, 4, 4,
                         3, 3, 3, 3, 1, 3, 4, 4, 3, 3,
                         3, 4, 4, 3, 3, 3, 4, 4, 3, 3,
                         3, 3, 3, 3, 3, 4, 4, 3, 3, 3,
                         4, 4, 3, 3, 3, 3, 3, 3, 3, 3,
                         3, 3, 8, 8, 8, 8, 8, 8, 8, 8,
                         8, 8, 8, 8, 8, 8, 8, 3, 4, 4,
                         3, 4, 4, 3, 4, 4, 3, 4, 4, 3,
                         4, 4, 3, 3, 3, 3, 1, 2, 2, 2,
                         2, 2, 2, 2, 2    , 2, 2, 2, 4,
                         4, 4, 4, 1
                        };

    int mimi2[] = {NOTE_E3, NOTE_FS3, NOTE_G3, NOTE_C2, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_E3, NOTE_FS3,
                   NOTE_D3, NOTE_E3, NOTE_FS3, NOTE_A3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_FS3, NOTE_E3, NOTE_FS3,
                   NOTE_E3, NOTE_FS3, NOTE_G3, NOTE_C2, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_E3, NOTE_FS3,
                   NOTE_D3, NOTE_E3, NOTE_FS3, NOTE_A3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_FS3, NOTE_E3, NOTE_B3,
                   NOTE_A3, NOTE_A3, NOTE_B3, NOTE_C4, NOTE_C4, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_FS3, NOTE_FS3,
                   NOTE_G3, NOTE_A3, NOTE_B3, NOTE_B3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_E3, NOTE_FS3, NOTE_G3,
                   NOTE_A3, NOTE_A3, NOTE_A3, NOTE_FS3, NOTE_G3, NOTE_A3, NOTE_D3, NOTE_E3, NOTE_FS3, NOTE_G3,
                   NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_D2, NOTE_C2, NOTE_C2, NOTE_D2, NOTE_C2, NOTE_C2,
                   NOTE_A3, NOTE_A3, NOTE_B3, NOTE_C2, NOTE_B3, NOTE_A3, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_B3,
                   NOTE_A3, NOTE_A3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_D2, NOTE_B3, NOTE_A3, NOTE_G3,
                   NOTE_DS3, NOTE_E3, NOTE_D2, NOTE_C2, NOTE_C2, NOTE_D2, NOTE_C2, NOTE_C2, NOTE_A3, NOTE_A3,
                   NOTE_B3, NOTE_C2, NOTE_B3, NOTE_A3, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_B3, NOTE_A3, NOTE_A3,
                   NOTE_B3, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_D2, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_DS3, NOTE_E3
                  };
    int mimi2_delay[] = {1, 1, 1, 1};

    int sugarPlum[] = {E[i], E[i+1], E[i], F[i+1], E[i], G[i+1], E[i], DS[i+1],
                       E[i], E[i+1], E[i], E[i+1], E[i], G[i+1], E[i], DS[i+1]
                      };
    int sugarPlum_delay[] = {4, 4, 4, 4,
                             4, 4, 4, 4,
                             4, 4, 4,4,
                             4, 4, 4, 2
                            };

    Musica m;
    switch(track) {
    case 1:
        m.tamanho = sizeof(ode)/sizeof(int);
        m.som = ode;
        m.tempo = ode_delay;
        break;

    case 2:
        m.som = nokia;
        m.tempo = nokia_delay;
        m.tamanho = sizeof(nokia)/sizeof(int);
        break;

    case 3:
        m.som = korobeiniki;
        m.tempo = korobeiniki_delay;
        m.tamanho = sizeof(korobeiniki)/sizeof(int);
        break;

    case 4:
        m.som = allStar;
        m.tempo = allStar_delay;
        m.tamanho = sizeof(allStar)/sizeof(int);
        break;
    case 5:
        m.som = mimi1;
        m.tempo = mimi1_delay;
        m.tamanho = sizeof(mimi1)/sizeof(int);
        break;
    case 6:
        m.som = mimi2;
        m.tempo = mimi2_delay;
        m.tamanho = sizeof(mimi2)/sizeof(int);
        break;
    case 7:
        m.som = sugarPlum;
        m.tempo = sugarPlum_delay;
        m.tamanho = sizeof(sugarPlum)/sizeof(int);
    }


    if(n!=0)
        m.tamanho=n;

    if(sizeof(m.som)!=sizeof(m.tempo)||sizeof(m.som)==0)
        aviso("Os vetores estão com tamanhos diferentes", 1);
    else {
        for(nota=primeira_nota; nota<m.tamanho && !kbhit(); nota++) {
            switch(m.tempo[nota]) {
            case 1:
                m.tempo[nota] = 800;
                break;
            case 2:
                m.tempo[nota] = 400;
                break;
            case 3:
                m.tempo[nota] = 300;
                break;
            case 4:
                m.tempo[nota] = 200;
                break;
            case 8:
                m.tempo[nota] = 100;
                break;
            case 16:
                m.tempo[nota] = 50;
                break;
            case 32:
                m.tempo[nota] = 25;
                break;
            case 64:
                m.tempo[nota] = 15;
                break;
            }

            Beep(*(m.som+nota), duracao* *(m.tempo+nota));

            if(track==5)
                printaPalavra("X", m.som[nota]%(COMPRIMENTO_TELA-6)-3, m.tempo[nota]%(ALTURA_TELA-20)+15, rand()%15+1);

            if(nota == m.tamanho-1 && track==5) {
                if(i<6)
                    beep(5, i+1, duracao, 0, 0);
                else
                    beep(5, 5, duracao, 0, 0);
            }
        }
    }
}

#endif
