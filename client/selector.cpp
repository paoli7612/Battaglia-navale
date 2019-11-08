//client/selector.cpp
#include "../drawing/drawGrill.cpp"

void selector_go_scr(int x, int y, char c){
	go_scr(x+28,y,c);
}

void selector_draw_centri(int x, int y){
	selector_go_scr(x+1,y+1,lc);
	selector_go_scr(x+1,y-1,lc);
	selector_go_scr(x-1,y+1,lc);
	selector_go_scr(x-1,y-1,lc);
}

void selector_draw_selector(int x, int y){
	selector_go_scr(x,y,as);
	selector_go_scr(x+2,y,ad);
	selector_go_scr(x,y+2,bs);
	selector_go_scr(x+2,y+2,bd);
}

void selector_draw_selector2(int x, int y){
	selector_go_scr(x,y,as);
	selector_go_scr(x+3,y,ad);
	selector_go_scr(x,y+2,bs);
	selector_go_scr(x+3,y+2,bd);
}

void selector_del_selector(int x, int y){
	selector_go_scr(x,y,0);
	selector_go_scr(x+2,y,0);
	selector_go_scr(x,y+2,0);
	selector_go_scr(x+2,y+2,0);
}

void selector_del_selector2(int x, int y){
	selector_go_scr(x,y,0);
	selector_go_scr(x+3,y,0);
	selector_go_scr(x,y+2,0);
	selector_go_scr(x+3,y+2,0);
}

void selector_draw_select_vertical(int x){
	int y;
	for (y=5; y<=25; y++){
		selector_go_scr(x-1,y,lv);
		selector_go_scr(x+1,y,lv);
	}
	selector_draw_selector(x-1,1);
	selector_draw_selector(x-1,27);

}

void selector_del_select_vertical(int x){
	int y;
	for (y=5; y<=25; y++){
		selector_go_scr(x-1,y,0);
		selector_go_scr(x+1,y,0);
	}
	selector_del_selector(x-1,1);
	selector_del_selector(x-1,27);
}

void selector_draw_select_orizontal(int y){
	int x;
	for (x=7; x<=27; x++){
		selector_go_scr(x,y+1,lo);
		selector_go_scr(x,y-1,lo);
	}
	selector_draw_selector2(1,y-1);
	selector_draw_selector2(29,y-1);
}

void selector_del_select_orizontal(int y){
	int x;
	for (x=7; x<=27; x++){
		selector_go_scr(x,y+1,0);
		selector_go_scr(x,y-1,0);
	}
	selector_del_selector2(1,y-1);
	selector_del_selector2(29,y-1);
}
