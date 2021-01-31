//client/main.cpp
#include "select.cpp"

#define DRAW 0
#define HIDE 1

int Xs,Ys,dir,len;
void init();
void gotoxy(int, int, int);
int get_pos_mat(int, int, int, int);
void set_pos_mat(int, int, int, int, int);
int allow_place();
void draw_ship();
void del_ship();
void save_ship();
int cross_dir(int);
void next_ship_rand();
void draw_mat(int slot);
int mat[2][2][10][10];
int pos_ships();
void set_sunk(int, int, int, int, int);
void set_sunk1(int, int, int);

void init()
{
	for (int slot=0; slot<2; slot++)
		for (int level; level<2; level++)
			for (int y=0; y<10; y++)
				for (int x=0; x<10; x++)
					mat[slot][level][x][y] = EMPTY;
					
	Xs = 0;
	Ys = 0;
	
	dir = HORIZONTAL;
	srand(time(NULL));
}

int get_pos_mat(int slot, int level, int x, int y){
	if (0 <= x && x <= 9)
		if (0 <= y && y <= 9)
			return mat[slot][level][x][y];
	return BORDER;
}

void set_pos_mat(int slot, int level, int x, int y, int value){
	if (0 <= x && x <= 9)
		if (0 <= y && y <= 9)
			mat[slot][level][x][y] = value;
}

void gotoxy(int slot, int x, int y){
	go(x + slot*28 + 8, y + 6);
}

int allow_place(){
	for (int n=0; n<len; n++)
	{
		if (dir && get_pos_mat(nPLAYER_1, HIDE, Xs+n, Ys) != EMPTY)
			return false;
		else if (get_pos_mat(nPLAYER_1, HIDE, Xs, Ys+n) != EMPTY)
			return false;
	}
	return true;
}

void draw_mat(int slot)
{
	for (int y=0; y<10; y++)
		for (int x=0; x<10; x++)
		{
			gotoxy(slot,x*2,y*2);
			int h = get_pos_mat(slot,HIDE,x,y);
			int d = get_pos_mat(slot,DRAW,x,y);
			if (h == SHOT)
				color(COLOR_SHOT);		//COLPITO
			if (h == SUNK)
				color(COLOR_SUNK);		//AFFONDATO
			if (h == NIGH)
				color(RED);				//ACQUA
			if (h == EMPTY)
				color(COLOR_EMPTY); 	//nave posizionabile
			if (h == TAKEN)
				color(COLOR_SHIP); 		//NAVE pulita
			if (d == WATER)
				color(COLOR_WATER);		//
			if (d == SUNK)
				color(COLOR_SUNK);
			if (d == SHOT)
				color(COLOR_SHOT);
			scr(get_pos_mat(slot,DRAW,x,y));
		}
}

void draw_ship()
{
	for (int n=0; n<len; n++)
	{
		if (dir == HORIZONTAL)
			set_pos_mat(nPLAYER_1,DRAW,Xs+n,Ys,SHIP);
		else
			set_pos_mat(nPLAYER_1,DRAW,Xs,Ys+n,SHIP);
	}
}

void del_ship(){
	for (int n=0; n<len; n++)
	{
		if (dir == HORIZONTAL)
			if (get_pos_mat(nPLAYER_1,HIDE,Xs+n,Ys) != TAKEN)
				set_pos_mat(nPLAYER_1,DRAW,Xs+n,Ys,EMPTY);
		else
			if (get_pos_mat(nPLAYER_1,HIDE,Xs,Ys+n) != TAKEN)
				set_pos_mat(nPLAYER_1,DRAW,Xs,Ys+n,EMPTY);
	}
}

void save_ship(){
	if (dir)
	{
		for (int n=0; n<len; n++)
		{
			set_pos_mat(nPLAYER_1, DRAW, Xs+n , Ys, SHIP);
			set_pos_mat(nPLAYER_1, HIDE, Xs+n , Ys, TAKEN);
			set_pos_mat(nPLAYER_1, HIDE, Xs+n, Ys+1, NIGH);
			set_pos_mat(nPLAYER_1, HIDE, Xs+n, Ys-1, NIGH);
		}
		set_pos_mat(nPLAYER_1, HIDE, Xs-1, Ys, NIGH);
		set_pos_mat(nPLAYER_1, HIDE, Xs+len, Ys, NIGH);
		set_pos_mat(nPLAYER_1, HIDE, Xs-1, Ys-1, NIGH);
		set_pos_mat(nPLAYER_1, HIDE, Xs+len, Ys-1, NIGH);
		set_pos_mat(nPLAYER_1, HIDE, Xs-1, Ys+1, NIGH);
		set_pos_mat(nPLAYER_1, HIDE, Xs+len, Ys+1, NIGH);

	}
	else
	{
		for (int n=0; n<len; n++)
		{
			set_pos_mat(nPLAYER_1, DRAW, Xs, Ys+n, SHIP);
			set_pos_mat(nPLAYER_1, HIDE, Xs, Ys+n, TAKEN);
			set_pos_mat(nPLAYER_1, HIDE, Xs+1, Ys+n, NIGH);
			set_pos_mat(nPLAYER_1, HIDE, Xs-1, Ys+n, NIGH);
		}
		set_pos_mat(nPLAYER_1, HIDE, Xs, Ys-1, NIGH);
		set_pos_mat(nPLAYER_1, HIDE, Xs, Ys+len, NIGH);
		set_pos_mat(nPLAYER_1, HIDE, Xs+1, Ys-1, NIGH);
		set_pos_mat(nPLAYER_1, HIDE, Xs+1, Ys+len, NIGH);
		set_pos_mat(nPLAYER_1, HIDE, Xs-1, Ys-1, NIGH);
		set_pos_mat(nPLAYER_1, HIDE, Xs-1, Ys+len, NIGH);
	}
}

int cross_dir(int dir)
{
	return (dir + 1) % 2;
}

void next_ship_rand()
{
	do
	{
		dir = rand()%2;	// ORIZZONTALE(1) o VERTICALE(0)
		Xs = rand()%10-len*dir;
		Ys = rand()%10-len*(cross_dir(dir));
	} while (not allow_place());
}

int pos_ships()
{
	char key;
	init();
	for (int n=0; n<SHIPS_MAX; n++)
	{
		int placed = false;
		len = SHIPS_LENS[n];
		while (not placed)
		{
			draw_ship();
			draw_mat(nPLAYER_1);
			key = getch();
			del_ship();
			switch(key)
			{
				// FRECCE
				case K_LEFT: {
					if (Xs>0)
						Xs--;
					break;
				}
				case K_RIGHT:{
					if (Xs<9-(len-1)*dir)
						Xs++;
					break;
				}
				case K_UP:{
					if (Ys>0)
						Ys--;
					break;
				}
				case K_DOWN:{
					if (Ys<9-(len-1)*cross_dir(dir))
						Ys++;
					break;
				}
				// Q W E R
				case K_Q:{ next_ship_rand(); break;}
				case K_W:{do{next_ship_rand();save_ship();n++;len = SHIPS_LENS[n];}while(n<SHIPS_MAX);placed=true;break;}
				case K_E:{init(); n=0; break;}
				case K_R:{dir = cross_dir(dir); break;}
				// INVIO
				case K_ENTER:{if (allow_place()){save_ship(); placed=true;} break;}
			}

		}
	}
	draw_mat(nPLAYER_1);
}


void set_sunk1(int slot, int x, int y){
	/* Metti acqua intorno alla nave affondata
	if (slot == nPLAYER_2){
		set_pos_mat(slot, DRAW, x+1, y, WATER);
		set_pos_mat(slot, DRAW, x-1, y, WATER);
		set_pos_mat(slot, DRAW, x, y-1, WATER);
		set_pos_mat(slot, DRAW, x, y+1, WATER);
		set_pos_mat(slot, DRAW, x+1, y-1, WATER);
		set_pos_mat(slot, DRAW, x+1, y+1, WATER);
		set_pos_mat(slot, DRAW, x-1, y-1, WATER);
		set_pos_mat(slot, DRAW, x-1, y+1, WATER);
		}
	*/
	draw_mat(slot);
}

void set_sunk(int slot, int x, int y, int dir, int len){
	if (dir == HORIZONTAL){
		for (int l=0; l<len; l++){
			set_pos_mat(slot,DRAW,x+l,y,SUNK);}
	}else if (dir == VERTICAL){
		for (int l=0; l<len; l++){
			set_pos_mat(slot,DRAW,x,y+l,SUNK);}
	}
	/* Metti acqua intorno alla nave affondata
	if (slot == nPLAYER_2){
		if (dir == HORIZONTAL){
			for (int n=0; n<len; n++){
				set_pos_mat(slot, DRAW, x+n, y+1, WATER);
				set_pos_mat(slot, DRAW, x+n, y-1, WATER);
			}
			set_pos_mat(slot, DRAW, x-1, y, WATER);
			set_pos_mat(slot, DRAW, x+len, y, WATER);
			set_pos_mat(slot, DRAW, x-1, y-1, WATER);
			set_pos_mat(slot, DRAW, x+len, y-1, WATER);
			set_pos_mat(slot, DRAW, x-1, y+1, WATER);
			set_pos_mat(slot, DRAW, x+len, y+1, WATER);

		}else{
			for (int n=0; n<len; n++){
				set_pos_mat(slot, DRAW, x+1, y+n, WATER);
				set_pos_mat(slot, DRAW, x-1, y+n, WATER);
			}
			set_pos_mat(slot, DRAW, x, y-1, WATER);
			set_pos_mat(slot, DRAW, x, y+len, WATER);
			set_pos_mat(slot, DRAW, x+1, y-1, WATER);
			set_pos_mat(slot, DRAW, x+1, y+len, WATER);
			set_pos_mat(slot, DRAW, x-1, y-1, WATER);
			set_pos_mat(slot, DRAW, x-1, y+len, WATER);
			}
	}
	*/
	draw_mat(slot);
}
