#include <stdio.h>
#include <stdlib.h>
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
	//lineas horizontales
	for(int i=2;i<81; i++){
		CursorPos(i,3); printf("%c", 205);
		CursorPos(i,23); printf("%c", 205);
	}
	//linera vertical	
	for(int i=4;i<23; i++){
		CursorPos(2,i); printf("%c", 186);
		CursorPos(81,i); printf("%c", 186);
	}
	
	CursorPos(2,3); printf("%c", 201); //esquina superior derecha 
	CursorPos(2,23); printf("%c", 200);//esqui inferior derecha 
	CursorPos(81,3); printf("%c", 187);//esquina superior izquierda
	CursorPos(81 ,23); printf("%c",188); //esequna inferior izquierda
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
	int corazones;
	int vidas;

public:
	Nav(int _x, int _y, int _corazones, int _vidas): x(_x), y(_y), corazones(_corazones), vidas(_vidas) {}		
	void show();
	void borrar();
	void move();
	void dibujar_corazones();
	void dead();
};


void Nav::show(){
	CursorPos(x,y); printf("    %c", 30);
	CursorPos(x,y); printf("   %c%c", 40, 207, 41);
	CursorPos(x,y); printf(" %c%c%c%c ", 30,190,190,30);
}

void Nav::borrar(){
	CursorPos(x,y);   printf("         ");
	CursorPos(x,y+1); printf("         ");
	CursorPos(x,y+2); printf("        ");
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
			dibujar_corazones();
			//printf (" ");
				
		}
}
void Nav::dead(){
	if(corazones==0){
		borrar();
		CursorPos(x,y);    printf("   **   ");
		CursorPos(x,y+1);  printf("  ****     ");
		CursorPos(x,y+3); printf("   **     ");
		
		borrar();
		CursorPos(x,y);    printf("   * ** *   ");
		CursorPos(x,y+1);  printf("    ****     ");
		CursorPos(x,7+3); printf("   * ** * *");
		borrar();
		vidas--;
		corazones =3;
		dibujar_corazones();
		show();
		
		
	}
}
void Nav::dibujar_corazones() {
	CursorPos(50,2); printf("vidas %d", vidas );
	CursorPos(64,2); printf("Salud");
	CursorPos(70,2); printf("     ");
	for(int i=0; i< corazones; i++){
		CursorPos(70+1, 2); printf("%c",3);
	}


}

class Ast{
 	int x, y;
public:
	Ast(int _x, int _y): x(_x), y(_y){}
	void pint();
	void mover();
};
void Ast::pint(){
	CursorPos(x, y); printf("%c", 184);
}

void Ast::mover(){
	CursorPos(x, y); printf(" ");
	y++;
	if(y>22) {
		x = rand()%71 +4;
		y =4;
	}
	pint();
	

}
int main ()
{	
	hiddenCursor();
	limites();
	//int x=10;
	//int y=10;
 	Nav N(7, 7,3, 3);
 	N.show();
 	N.dibujar_corazones();
 	Ast ast(10, 4);
	bool game_over= false;
	
	while(!game_over){
			//CursorPos(x,y);
			//printf ("*");
		ast.mover();
		N.dead();
		N.move();	
		//Sleep(10);
	}

	
	return 0;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */




