#include <stdio.h>
#include <windows.h>
#include <conio.h>
#define ARRIBA 72
#define ABAJO  80
#define IZQUIERDA 75
#define DERECHA 77


void CursorPos(int XPos, int YPos){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwpos;
	dwpos.X=XPos;
	dwpos.Y=YPos;
	SetConsoleCursorPosition(hcon, dwpos);
	
}

void limites(){
	for(int i=2;i<78; i++){
		CursorPos(i,3); printf("%c", 205);
		CursorPos(i,22); printf("%c", 205);
	}
	
	for(int i=4;i<22; i++){
		CursorPos(2,i); printf("%c", 186);
		CursorPos(77,i); printf("%c", 186);
	}
	
	CursorPos(2,3); printf("%c", 201);
	CursorPos(2,33); printf("%c"), 200;
	CursorPos(77,3); printf("%c", 187);//esquina inferior 
	CursorPos(77 ,22); printf("%c",188); //esequna inferior derecha
}

void hiddenCursor(){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO oci;
	oci.dwSize=1;
	oci.bVisible =FALSE;
	SetConsoleCursorInfo(hcon, &oci);
}

class Nav {
	int x, y;
public:
	Nav(int _x, int _y): x(_x), y(_y){}		
	void show();
	void borrar();
	void move();
};


void Nav::show(){
	CursorPos(x,y); printf("   %c", 30);
	CursorPos(x,y); printf("  %c%c", 40, 207, 41);
	CursorPos(x,y); printf(" %c%c%c ", 30,190,190,30);
}

void Nav::borrar(){
	CursorPos(x,y); printf("      ");
	CursorPos(x,y+1); printf("      ");
	CursorPos(x,y+2); printf("      ");
}

void Nav::move(){
		if(kbhit()){
			char tecla = getch();
			borrar();
			CursorPos(x,y);
			if(tecla == IZQUIERDA && x >3) x--;
			if(tecla == DERECHA && x+6<77)  x++;
			if(tecla == ARRIBA && y>4)  y--;
			if(tecla == ABAJO && y+3<23)  y++;	
			show();
			//printf (" ");
				
		}
}

int main ()
{	
	hiddenCursor();
	limites();
	//int x=10;
	//int y=10;
 	Nav N(7, 7);
 	N.show();
	bool game_over= false;
	
	while(!game_over){
			//CursorPos(x,y);
			//printf ("*");
		N.move();	
		//Sleep(30);
	}

	
	return 0;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */




