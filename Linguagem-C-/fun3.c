#include <stdio.h>
void detectaValoresIguais(int A[], int B[], int n, int m);

int main(){
	int A[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
	int n = sizeof(A)/sizeof(int); //em java seria simplesmente int n = A.length;
	int B[] = {1, 2, 3, 4, 5, 6, 8, 10, 12, 7, 29};
	int m = sizeof(B)/sizeof(int);
	
	detectaValoresIguais(&A[0], &B[0], n, m);
	
	return 0;
}

void detectaValoresIguais(int A[], int B[], int n, int m){
	int i=0, j;
	for(; i<n; i++){ //aqui nao vou precisar zerar o i de novo
		for(j=0; j<m; j++){ //aqui sim, porque tem um for mais externo
			if(A[i]==B[j])
				printf("%i, ", A[i]);
		}
	}
}
