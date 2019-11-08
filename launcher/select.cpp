//launcher/select.cpp
#include "../drawing/draw.cpp"

int select_y = 0;
void draw_selector(){
	color(COLOR_SCANF);
	draw_rect(sX_CENTER-15,Y_START_MENU+select_y*2-1,sX_CENTER+15,Y_START_MENU+select_y*2+1);
}

void del_selector(){
	del_rect(sX_CENTER-15,Y_START_MENU+select_y*2-1,sX_CENTER+15,Y_START_MENU+select_y*2+1);
}


void select_menu(){
	int running = true;
	char tasto = false;
	while (running){
		draw_selector();
		tasto = getch();
		del_selector();
		switch(tasto){
			case K_UP:
				if (select_y>0)
					select_y--;
				break;
			case K_DOWN:
				if (select_y<3)
					select_y++;
				break;
			case K_ENTER:
				running = false;
				break;

		}
	}


}
