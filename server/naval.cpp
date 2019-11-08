// server/naval.cpp
#include "../drawing/drawGrill.cpp"
int NAVI_MAX = 10;

int mat[2][10][10];
int naval_SLOT = 0;

int naval_mat_pos(int client, int x, int y){
	if (0 <= x && x <= 9)
		if (0 <= y && y <= 9)
			return mat[client][x][y];
	return BORDER;
}

void naval_mat_set(int client, int x, int y, int value){
	if (0 <= x && x <= 10)
		if (0 <= y && y <= 10)
			mat[client][x][y] = value;
}


void naval_change_slot(int new_slot){
	naval_SLOT = new_slot;
}

void naval_go(int x, int y){
	COORD coord;
	coord.X=x+8+naval_SLOT*28+8;
	coord.Y=y+6+5;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void naval_draw_mat(int mat[10][10],int pos){
	naval_change_slot(pos);
	for (int y=0; y<10; y++){
		for (int x=0; x<10; x++){
			naval_go(x*2,y*2);
			if (mat[x][y] == TAKEN){
				color(COLOR_SHIP);
				scr(SHIP);
			}
			if (mat[x][y] == SHOT){
				color(COLOR_SHOT);
				scr(SHOT);
			}
			if (mat[x][y] == WATER){
				color(COLOR_WATER);
				scr(WATER);
			}
			if (mat[x][y] == SUNK){
				color(COLOR_SUNK);
				scr(SUNK);
			}
		}
	}
}

int dir = 0;
int len = 0;
int real_x = 0;
int real_y = 0;


int naval_get_dir(int client,int x, int y){
	int dir;
	int up = naval_mat_pos(client,x,y-1);
	int down = naval_mat_pos(client,x,y+1);

	int left = naval_mat_pos(client,x-1,y);
	int right = naval_mat_pos(client,x+1,y);
	if (up == TAKEN || up == SHOT || down == TAKEN || down == SHOT)
		dir = VERTICAL;
	else if (left == TAKEN || left == SHOT || right == TAKEN || right == SHOT)
		dir = HORIZONTAL;
	else
		dir = NONE;
	return dir;
}

int naval_get_len(int client, int x, int y, int dir){
	len = 1;
	switch(dir){
		case VERTICAL:
			for (int p=1; p<4; p++){
				int nextPos = naval_mat_pos(client,x,y+p);
				if (nextPos == TAKEN || nextPos == SHOT)
					len++;
				else
					break;
			}
			return len;
			break;
		case HORIZONTAL:
			for (int p=1; p<4; p++){
				int nextPos = naval_mat_pos(client,x+p,y);
				if (nextPos == TAKEN || nextPos == SHOT)
					len++;
				else
					break;
			}
			return len;
			break;
		case NONE:
			return 1;
			break;
	}
}

int naval_get_life(int client, int x, int y, int dir, int len){
	if (dir == HORIZONTAL){
		int aff = true;
		for (int l=0; l<len+1; l++){
			int nextPos = naval_mat_pos(client,x+l,y);
			if (nextPos == TAKEN){
				aff = false;
			}
		}
		if (aff){
			for (int l=0; l<len; l++){
				mat[client][x+l][y] = SUNK;
			}
			return true;
		}
	}
	else if (dir == VERTICAL){
		int aff = true;
		for (int l=0; l<len+1; l++){
			int nextPos = naval_mat_pos(client,x,y+l);
			if (nextPos == TAKEN){
				aff = false;
			}
		}

		if (aff){
			for (int l=0; l<len; l++){
				mat[client][x][y+l] = SUNK;
			}
			return true;
		}
	}
	return false;
}


char war_attack(int client, int x, int y){
	if (mat[client][x][y]==SUNK) return cFAKE;
	if (mat[client][x][y] == EMPTY || mat[client][x][y] == NIGH || mat[client][x][y] == WATER){
		mat[client][x][y] = WATER;
		naval_draw_mat(mat[client],client);
		return cWATER;
	}
	else{
		mat[client][x][y] = SHOT;
		naval_draw_mat(mat[client],client);
		dir = naval_get_dir(client,x,y);
		if (dir == NONE){
			naval_draw_mat(mat[client],client);
			return cSHIP_1;
		}
		else if (dir == VERTICAL){
			for(int y1=0; y1<4; y1++){
				int nextPos = naval_mat_pos(client,x,y-1);
				if (nextPos == TAKEN || nextPos == SHOT)
					y--;
				else {
					break;
				}
			}
		}
		else if (dir == HORIZONTAL){
			for(int x1=0; x1<4; x1++){
				int nextPos = naval_mat_pos(client,x-1,y);
				if (nextPos == TAKEN || nextPos == SHOT)
					x--;
				else {
					break;
				}
			}
		}
		len = naval_get_len(client,x,y,dir);
		real_x = x;
		real_y = y;
		if (naval_get_life(client,x,y,dir,len)){
			naval_draw_mat(mat[client],client);
			return cSUNK;
		}
		else{
			naval_draw_mat(mat[client],client);
			return cSHOT;
		}
	}
	return cWATER;
}
