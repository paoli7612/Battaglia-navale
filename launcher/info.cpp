//launcher/info.cpp
#include "select.cpp"

void info_show(){
	system("cls");
	color(COLOR_TITLES);
	print_center("INFO",4,sizeof("INFO"));
	color(COLOR_RECT);
	draw_rect(sMRG,sMRG-1,sX_TOT-sMRG,sMRG+22);
	draw_rect2(sMRG+3,sMRG+2,sX_CENTER-4,sY_CENTER_LAUNCHER-4);
	draw_rect2(sX_CENTER+3,sMRG+2,sX_TOT-sMRG-3,sY_CENTER_LAUNCHER-4);
	color(COLOR_CREDENTIAL);
	go_print(10,5,cCOMANDI);
	go_print(57,5,cCOLLEGAMENTO);

	color(LIGHT_BLUE);
	go_print(8,7,cCOMANDI_NAVI);
	go_print(8,9,cCOMANDI_Q);
	go_print(8,11,cCOMANDI_W);
	go_print(8,13,cCOMANDI_E);
	go_print(8,15,cCOMANDI_R);
	go_print(8,17,cCOMANDI_FRECCE);
	go_print(8,19,cCOMANDI_INVIO);

	color(PURPLE);
	go_print(52,9,cCOLLEGAMENTO_1);
	go_print(57,11,cCOLLEGAMENTO_2);
	go_print(49,13,cCOLLEGAMENTO_3);
	go_print(45,15,cCOLLEGAMENTO_4);
	go_print(50,17,cCOLLEGAMENTO_5);

	color(RED);
	go_print(20,sY_CENTER_LAUNCHER-2,"Premere invio per tornare al menu...");
	getchar();
	terminal_clear();
}
