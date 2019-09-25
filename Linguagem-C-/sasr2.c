#include<stdio.h>

void par(){
	int i=2;
	for(;i<21; i+=2){
		printf("%i ", i);
	}
}

void impar(){
	int i=1;
	for(;i<20; i+=2){
		printf("%i ",i);
	}

}

int main(){
	int option;
	scanf("%i", &option);
	switch(option){
		case 1:
			impar();
			break;
		case 2:
			par();
			break;
	}
	return 0;
}
