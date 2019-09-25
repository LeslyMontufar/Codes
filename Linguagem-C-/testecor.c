#include <stdio.h>
#include <conio2.h>

/*enum  	COLORS { 
  BLACK, BLUE, GREEN, CYAN, 
  RED, MAGENTA, BROWN, LIGHTGRAY, 
  DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, 
  LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE 
}*/

int main(){
	
	textbackground(DARKGRAY);
	clrscr();
	
	textcolor(WHITE);
	
	printf("Hello World!\n");
	
	
	cputsxy (25, 8, "\xDB\xDB");
	
	gotoxy(1,25);
	printf("\xDB");

	gotoxy(8,25);
	printf("\xDB\xDB");
	
//	int y;
	//for(y=2; y<20; y++){
		//clrscr();
	//	textbackground(WHITE);
	//	textcolor(MAGENTA);
	//	gotoxy(10, y);
	//	printf("\xDC");
	//	sleep(1);
	//}
	int i,j;
	clrscr();
	_setcursortype(0);
	for(j=5; j<15;j++){
		for(i=5;i<100; i++){
			gotoxy(i,j);
			if(i<=j){
				textcolor(MAGENTA);
				printf("\xDB");
				sleep(0.001);
			}
		}
	}
	
	return 0;
}
