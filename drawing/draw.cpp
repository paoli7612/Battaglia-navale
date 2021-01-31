#include "../define/stringChar.cpp"

int x,y,ys,xs,raw_log = 0;

void draw_sposta(int x,int y){xs=x;ys=y;}
void color(int value){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),value);} // Cambia il colore di scrittura su terminale
void go(int x, int y){COORD coord;coord.X=x+xs;coord.Y=y+ys;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);} // Sposta il cursore di scrittura sul terminale

void resize(int x1, int y1, int x2, int y2){HWND console = GetConsoleWindow(); // Reimposta grandezza e posizione del terminale
	RECT r;	GetWindowRect(console, &r);	MoveWindow(console, x1, y1, x2, y2, true);}

void scr(char c){printf("%c",c);}	
void sir(int v){printf("%d",v);}
void go_print(int x, int y, const char *t, int n=0){go(x,y);printf(t,n);}
void go_scr(int x, int y, char c){go(x,y);scr(c);}
void go_sir(int x, int y, int v){go(x,y);sir(v);}
void print_center(char *c, int y, int len){go_print(sX_CENTER-len/2,y,c);}

void terminal_clear(){
	system("cls");
}

void terminal_exit(){
	system("exit");
}

void draw_angoli(int x1, int y1, int x2, int y2){
	go_scr(x1,y1,AS);
	go_scr(x2,y1,AD);
	go_scr(x1,y2,BS);
	go_scr(x2,y2,BD);
}

void draw_angoli2(int x1, int y1, int x2, int y2){
	go_scr(x1,y1,as);
	go_scr(x2,y1,ad);
	go_scr(x1,y2,bs);
	go_scr(x2,y2,bd);
}

void draw_line_horizontal(int x1, int x2, int y){
	for (x=x1+1; x<x2; x++)
		go_scr(x,y,LO);
}

void draw_line_vertical(int y1, int y2, int x){
	for (y=y1+1; y<y2; y++)
		go_scr(x,y,LV);
}

void draw_line_horizontal2(int x1, int x2, int y){
	for (x=x1+1; x<x2; x++)
		go_scr(x,y,lo);
}

void draw_line_vertical2(int y1, int y2, int x){
	for (y=y1+1; y<y2; y++)
		go_scr(x,y,lv);
}

void del_line_vertical(int y1, int y2, int x){
	for (y=y1; y<=y2; y++)
		go_scr(x,y,0);
}

void del_line_horizontal(int x1, int x2, int y){
	for (x=x1; x<=x2; x++)
		go_scr(x,y,0);
}

void del_rect(int x1, int y1, int x2, int y2){
	del_line_horizontal(x1,x2,y1);
	del_line_horizontal(x1,x2,y2);
	del_line_vertical(y1,y2,x1);
	del_line_vertical(y1,y2,x2);
}


void draw_rect(int x1, int y1, int x2, int y2){
	draw_line_horizontal(x1,x2,y1);
	draw_line_horizontal(x1,x2,y2);
	draw_line_vertical(y1,y2,x1);
	draw_line_vertical(y1,y2,x2);
	draw_angoli(x1,y1,x2,y2);	
}

void draw_rect2(int x1, int y1, int x2, int y2){
	draw_line_horizontal2(x1,x2,y1);
	draw_line_horizontal2(x1,x2,y2);
	draw_line_vertical2(y1,y2,x1);
	draw_line_vertical2(y1,y2,x2);
	draw_angoli2(x1,y1,x2,y2);	
}

void draw_client(char *nickname, char *addr, int port){
	color(COLOR_RECT);
	draw_rect(2, 1, 77, 6);
	draw_rect2(2, 8, 77, 14);
	draw_rect2(2, 16 ,77, 61);
	
	color(COLOR_TITLES);
	go_print(37, 3,cCLIENT);
	go_print(32, 4,cBATTAGLIA_NAVALE);
	
	color(COLOR_CREDENTIAL);
	go_print(6, 10, cNICKNAME);
	go_print(6, 11, cINDIRIZZO_IP);
	go_print(6, 12, cPORTA);
		
	color(COLOR_SCANF);
	go_print(45, 10, nickname);
	go_print(45, 11, addr);
	go_sir(45, 12, port);	
}

void draw_loading_start(int v){
	if (v){
		color(YELLOW);
		go_print(37,57, "AVVIO  IN ");
		go_print(37,58, "  CORSO   ");
	}else{
		color(YELLOW);
		go_print(37,57, "  ATTESA  ");
		go_print(37,58, "AVVERSARIO");
	}
	
}

void draw_wait_clients(int v){
	if (v){ // Inizio
		color(PURPLE);
		go_print(37,57, cWAIT);
		go_print(37,58, cCLIENT);
	}
	else{ // Fine
		go_print(37,57,cSPAZIO_6);
		go_print(37,58,cSPAZIO_6);
		sleep(1);
		go_print(30,58,cAVVIO_IN_CORSO);
		sleep(1);
	}
}

void draw_server(char *hname, char *addr, int port){
	color(COLOR_RECT);
	draw_rect(2, 1, 77, 6);
	draw_rect2(2, 8, 77, 14);
	draw_rect2(2, 16 ,77, 61);
	
	color(COLOR_TITLES);
	go_print(37, 3,cSERVER);
	go_print(32, 4,cBATTAGLIA_NAVALE);
	
	color(COLOR_CREDENTIAL);
	go_print(6, 10,cNOME_HOST);
	go_print(6, 11,cINDIRIZZO_IP);
	go_print(6, 12,cPORTA);
	
	color(COLOR_SCANF);
	go_print(45, 10, hname);
	go_print(45, 11, addr);
	go_sir(45, 12, port);	
}

void draw_client(char *nickname, int client){
	draw_rect2(5,18+client*14,74,30+client*14);
	go_print(10,21+client*14,cGIOCATORE_N,client+1);
	go_print(10,23+client*14,cNICKNAME);
	printf("  %s",nickname);
}

void next_log(int colore){
	color(colore);
	go(2,65+raw_log);
	raw_log += 1;
}

void init_terminal(int program){
	switch(program){
		case CLIENT:
			resize(pCLIENT_START_X,pCENTER_Y,pCLIENT_X,pCLIENT_Y);
			break;
		case SERVER:
			resize(pSERVER_START_X,pCENTER_Y,pSERVER_X,pSERVER_Y);
			break;
		case LAUNCHER:
			resize(pLAUNCHER_START_X,pCENTER_Y,pLAUNCHER_X,pLAUNCHER_Y);
			break;
	}
}

void draw_launcher(){
	color(COLOR_TITLES);
	print_center(cBATTAGLIA_NAVALE,4,sizeof(cBATTAGLIA_NAVALE));
	color(COLOR_SHOT);
	print_center(cBYLINE,24,sizeof(cBYLINE));
	color(COLOR_RECT);
	draw_rect(sMRG,sMRG-1,sX_TOT-sMRG,sMRG+3);
	draw_rect2(sMRG,sMRG+5,sX_TOT-sMRG,sMRG+17);
	draw_rect2(sMRG,sMRG+19,sX_TOT-sMRG,sMRG+23);
	color(COLOR_CREDENTIAL);
	print_center(cSTART,Y_START_MENU,sizeof(cSTART));
	print_center(cSERVER,Y_START_MENU+2,sizeof(cSERVER));
	print_center(cINFO,Y_START_MENU+4,sizeof(cINFO));
	print_center(cEXIT,Y_START_MENU+6,sizeof(cEXIT));
}
