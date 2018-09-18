#include<stdio.h>
#include<time.h>
#include<stdlib.h>
//#include<conio2.h>

#define n 10000

int main(){
    int i, vet[n], num; 
	double media=0;
    scanf("%i", &num);
    srand(time(NULL));
    for(i=0; i<n; i++){
        vet[i]=rand()%(num+1);
        media+=vet[i];
    }
    media/=(double)n;
    printf("%lf\n", media);
    return 0;
}

//textcolor(), backgroundcolor(), gotoxy(), clrscr()
