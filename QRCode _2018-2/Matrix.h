#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#define CHECK()                   \
    fprintf(stdout, "Chegou aqui\n");

#define STOP()                              \
    CHECK() exit(1);

#define Q(x, y)                             \
    fprintf(stdout, "\nSao %i %s\n", x, y);

#define LOGS(v, comandos)\
    if(v && v!=2)\
        comandos

typedef
struct {
    unsigned int R, C, E;
    unsigned char * elements;
}Matrix;


Matrix * M_create(unsigned int E, unsigned int R, unsigned int C) {
    Matrix * A = (Matrix *) malloc(sizeof(Matrix));
    A->R = R;
    A->C = C;
    A->E = E;
    A->elements = (unsigned char *) calloc(R*C*E, sizeof(unsigned char));
    return A;
}

void M_free(Matrix * A) {
    free(A->elements);
    free(A);
}

unsigned char * M_at(Matrix * A, unsigned int i, unsigned int j, unsigned int k) {
    return A->elements + (i*A->R*A->C + j*A->C +k);
}

void M_fill(Matrix * A, unsigned char * dini, unsigned char * dend) {
    unsigned int i, j, k;
    for(i = 0; i < A->E; i++)
        for(j = 0; j < A->R; j++)
            for(k = 0; k < A->C; k++)
                if(dini + i*A->R*A->C + j*A->C +k < dend)
                    *M_at(A, i, j, k) = dini[i*A->R*A->C + j*A->C +k];
}

void M_print(Matrix * A) {
    unsigned int i, j, k;
    for(i = 0; i < A->E; i++) {
        for(j = 0; j < A->R; j++) {
            for(k = 0; k < A->C; k++)
                printf("%c ", *M_at(A,i,j, k));
            printf("\n");
        }
        printf("\n");
    }
}

#endif
