#include <stdio.h>
#include "matriz.h"

int main(){
	int n;
	Matriz A, adjuntaA; /*não declarei ponteiro do tipo Matriz, então só acesso A.lin e A.col*/
	printf("ordem: ");
	scanf("%i", &n);
	
	adjuntaA = A = criarMatriz(n, n);
	preencherMatriz(A);
	adjuntaA = adjunta(A);
	
	imprimirMatriz(adjuntaA);
	
	return 0;
}
