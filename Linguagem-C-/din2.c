#include <stdio.h>
#include <stdlib.h>

float **alocaMatrizFloat_new(int m, int n){
	float **matriz;
	
	//criando espaço na memória para a matriz:
	matriz = (float **) malloc(m*sizeof(float *)); //abrindo espaço para as linhas
	int i;
	for(i=0; i<n; i++){
		matriz[i]= (float *) malloc(n*sizeof(float)); //em cada linha haverá n espaços, já que a matriz possui n colunas
	}
	
	//retorna o endereco da matriz que alocou o espaço
	return matriz;
}

void imprime(float **matriz, int m, int n){
	int i, j;
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			printf("%.2f\t", matriz[i][j]);
		}
		printf("\n");
	}
}

void preenche(float **matriz, int m, int n){
	int i, j;
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			printf("matriz[%i][%i] = ", i, j);
			scanf("%f", &matriz[i][j]);
		}
		printf("\n");
	}
}

void transpoe(float **matriz, float **transposta, int m, int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			transposta[i][j]= matriz[j][i];
		}
	}
}

int main(){
	float **matriz, **transposta;
	int m,n;
	scanf("%i%i", &m, &n);
	
	//criando espaço na memória para a matriz:
	matriz = alocaMatrizFloat_new(m, n);
	transposta = alocaMatrizFloat_new(n, m);
	
	//agora a matriz já pode ser usada e manipulada:
	preenche(matriz, m, n);
	imprime(matriz, m, n);
	transpoe(matriz, transposta, m, n);
	printf("\n\n");
	imprime(transposta, n, m);
	return 0;
}
