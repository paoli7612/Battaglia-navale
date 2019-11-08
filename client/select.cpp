//client/select.cpp
#include "selector.cpp"

int select_x = 5;
int select_y = 5;

void select_go(int x, int y){COORD coord; coord.X=x+28; coord.Y=y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); }


int* select_pos(){
	int x=select_x,y=select_y;
	char tasto;
	while (true){
		color(COLOR_SELECTOR);
		selector_draw_select_vertical(x*2+8);
		selector_draw_select_orizontal(y*2+6);
		selector_draw_centri(x*2+8,y*2+6);
		tasto = getch();
		selector_del_select_vertical(x*2+8);
		selector_del_select_orizontal(y*2+6);
		if (tasto == 75) //sinistra
			if (x-1 >= 0)
				x--;
		if (tasto == 77) //destra
			if (x+1 < 10)
				x++;
		if (tasto == 72) //su
			if (y-1 >= 0)
				y--;
		if (tasto == 80) //giu
			if (y+1 <10)
				y++;
		if (tasto == 13){//Invio
				select_x = x;
				select_y = y;
				break;
				}
			}

}
