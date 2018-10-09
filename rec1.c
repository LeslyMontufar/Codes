#include <stdio.h>
int somaRecursiva(int A[], int N); //é a mesma coisa que: int *vet

int main(){
	int A[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
	int N = sizeof(A)/sizeof(int); //modo bem interessante de saber o tamanho do vetor
	printf("%i", somaRecursiva(&A[0], N-1)); //vetor é um ponteiro
											//envia N-1 porque o sizeof não considera 0
											//nesse caso deu 16*4bytes/4bytes 
	return 0;
}

int somaRecursiva(int A[], int N){//aritmética de vetores
	if(N>=0)
		return A[N]+somaRecursiva(&A[0], N-1);
	else
		return 0; //elemento neutro da soma e para a recursão
}
