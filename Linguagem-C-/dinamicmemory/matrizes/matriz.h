#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef
	struct aMatriz {
		double ** m;
		int lin, col;
	}
Matriz; /*muito útil envio a matriz e ao mesmo tempo A.lin e A.col*/

Matriz criarMatriz(int M, int N) {
	Matriz A;
	int i;
	A.m = (double **) calloc(M, sizeof(double *)); /* A.m é endereço e A->m é o conteúdo */
	for(i = 0; i < M; i++)
		A.m[i] = (double *) calloc(N, sizeof(double));
	A.lin = M; /*por que é por referência*/
	A.col = N;
	return A;
}

void destruirMatriz(Matriz A) {
	int i;
	for(i = 0; i < A.lin; i++)
		free(A.m[i]);
	free(A.m);
}

void preencherMatriz(Matriz A) {
	int i, j;
	for(i = 0; i < A.lin; i++)
		for(j = 0; j < A.col; j++) {
			printf("Entre com o elemento [%d][%d]: ", i, j);
			scanf("%lf", A.m[i]+j);
		}
}

void imprimirMatriz(Matriz A) {
	int i, j;
	for(i = 0; i < A.lin; i++) {
		for(j = 0; j < A.col; j++)
			printf("%lg\t", A.m[i][j]);
		printf("\n");
	}
	printf("> %dx%d\n\n", A.lin, A.col);
}

Matriz transposta(Matriz A) {
	Matriz At = criarMatriz(A.col, A.lin); // ordem transposta
	int i, j;
	for(i = 0; i < A.col; i++)
		for(j = 0; j < A.lin; j++) 
			At.m[i][j] = A.m[j][i];
	return At;
}

double determinante(Matriz A);

double menor(Matriz A, int l, int c) {
	Matriz M = criarMatriz(A.lin-1,A.col-1);
	double menorA;
	int i, j, p, q;
	p = 0;
	for(i = 0; i < A.lin; i++) {
		if(i != l) {
			q = 0;
			for(j = 0; j < A.col; j++)
				if(j != c) {
					M.m[p][q] = A.m[i][j];
					q++;
				}
			p++;
		}
	}
	menorA = determinante(M);
	destruirMatriz(M);
	return menorA;
}

double cofator(Matriz A, int i, int j) {
	return ((i+j)%2) ? -1*menor(A,i,j) : menor(A,i,j);
}

/*minha edicao*/
Matriz comatriz(Matriz C){
	Matriz comatrizC;
	comatrizC = criarMatriz(C.lin, C.col); /*C não é ponteiro, pois (*C).lin == C->lin   importante!*/
	int i, j;
	for(i=0; i<comatrizC.lin; i++)
		for(j=0; j<comatrizC.col; j++)
			comatrizC.m[i][j] = cofator(C, i, j); /*comatrizC tbm é uma estrutura, para acessar a matriz double** m precisa do operador . */
	return comatrizC;
}
Matriz adjunta(Matriz C){
	Matriz adjuntaC;
	adjuntaC = criarMatriz(C.lin, C.col);
	adjuntaC = transposta(comatriz(C));
	return adjuntaC; /*retorna uma estrutura que pode ser acessada em outra funcao como na adjunta(C)*/
}

Matriz inversa(Matriz C){
	if(determinante(C)==0){
		printf("nao inversivel\n");
		getch();
		exit(0);
	}
	Matriz inversaC;
	inversaC = criarMatriz(C.lin, C.col);
	int i, j;
	for(i=0; i<inversaC.lin; i++)
		for(j=0; j<inversaC.col; j++)
			inversaC.m[i][j] = adjunta(C).m[i][j] / determinante(C); /*acessa a estrutura direto da função adjunta(C).m[i][j] */	
	return inversaC;
}
/*end minha edicao*/

double determinante(Matriz A) {
	double det = NAN;
	int i;
	if(A.lin != A.col)
		fprintf(stderr,"Matriz retangular, sem determinante!\n");
	if(A.lin == 1) det = A.m[0][0]; 
	if(A.lin == 2) det = A.m[0][0]*A.m[1][1]-A.m[0][1]*A.m[1][0]; 
	if(A.lin == 3) det = (A.m[0][0]*A.m[1][1]*A.m[2][2]+
		A.m[0][1]*A.m[1][2]*A.m[2][0]+A.m[0][2]*A.m[1][0]*A.m[2][1])-
		(A.m[0][0]*A.m[1][2]*A.m[2][1]+A.m[0][1]*A.m[1][0]*A.m[2][2]+
		A.m[0][2]*A.m[1][1]*A.m[2][0]);
	if(A.lin > 3) {
		det = 0;
		for(i = 0; i < A.col; i++)
			det += A.m[0][i]*cofator(A,0,i);
	}
	return det;
}
#endif
