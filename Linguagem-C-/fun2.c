#include <stdio.h>//instrução para o pré-compilador
void restoQuociente(int num1, int num2, int *resto, double *quociente);

int main(){
	double quociente;
	int resto, num1, num2;
	scanf("%i, %i", &num1, &num2);
	restoQuociente(num1, num2, &resto, &quociente);
	printf("%g, %i", quociente, resto);
	return 0;
}


void restoQuociente(int num1, int num2, int *resto, double *quociente){
	*resto= num1 % num2;
	*quociente=num1/num2;
}
