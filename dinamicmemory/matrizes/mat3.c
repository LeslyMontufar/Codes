#include <stdio.h>
#include "matriz.h"

int main(){
	int n;
	Matriz A; /*não declarei ponteiro do tipo Matriz, então só acesso A.lin e A.col (com operador .)*/
	printf("ordem: ");
	scanf("%i", &n);
	
	A = criarMatriz(n, n);
	preencherMatriz(A);

	printf("\n");
	imprimirMatriz(inversa(A));/*nem precisa criar inversaA, porque a inversa(A) já retorna estrutura*/
	return 0;
}
