#include <stdio.h>
int fatorial(int n);

int main(){
	int n = 7; 
	printf("Fatorial %d = %d", n, fatorial(n));  
	return 0;
}
int fatorial(int n){
	if(n!=0 && n!=1)
		return n *fatorial(n-1);
	else 
		return 1; //fatorial(0) e fatorial(1) n�o � 0 , � 1.
				//quando chegar no n==1 vai s� multiplicar por 1 que ser� ele mesmo
				//ent�o poder� retorna j� esse valor, sem fazer a recursividade de novo
}
