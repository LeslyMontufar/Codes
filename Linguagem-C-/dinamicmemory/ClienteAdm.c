#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define N 100
#define numCliente 10

typedef 
	struct Cliente{
		char nome[N];
		long int CPF;
	}
Cliente;


Cliente * criaCliente(){
	Cliente *clienteA;
	clienteA = (Cliente *) malloc(numCliente * sizeof(Cliente));
	return clienteA;
}

Cliente dadosClientes(){ //passagem por valor
	Cliente aux;
	printf("Dados do Cliente: \n\tNome: ");
	fflush(stdin);
	gets(aux.nome);
	printf("\tCPF: ");
	scanf("%ld", &aux.CPF);
	return aux;
}

void imprimeDados(Cliente *c, int num){
	int index=0;
	printf("Dados dos clientes:\n\n");
	for(; index<num; index++){
		printf("Nome: %s\n", c[index].nome);
		printf("CPF: %ld\n\n", c[index].CPF);
	}
}

int main(){
	Cliente *c;
	int num=0, opcao;
	c = criaCliente(numCliente);
	
	do{
		system("cls");
		printf("\n\t1 - Cadastrar novo cliente\n\t2 - Imprime dados dos clientes\n\n");
		switch(getch()){
		case '1':
			c[num] = dadosClientes(c, num);
			num++;
			if(num>=numCliente)
				c = (Cliente * ) realloc(c, sizeof(Cliente));
			getch();
			break;
		case '2':
			imprimeDados(c, num);
			getch();
			break;
		case '0':
			return 0;
		default:
			printf("Opcao invalida\n");
		}
	}while(1);
}
