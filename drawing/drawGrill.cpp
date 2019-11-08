#include "draw.cpp"

void draw_griglia(){
	draw_sposta(8,5);
	int x,y;
	color(COLOR_GRILL);
	for (x=0; x<=62; x++){
		go_scr(x,4,LO);
		go_scr(x,26,LO);
	}	
	for (x=6; x<=28; x++){
		go_scr(x,0,LO);
		go_scr(x,30,LO);
	}	
	for (x=34; x<=56; x++){
		go_scr(x,0,LO);
		go_scr(x,30,LO);
	}	
	for (y=0; y<=30; y++){
		go_scr(6,y,LV);
		go_scr(28,y,LV);
		go_scr(34,y,LV);
		go_scr(56,y,LV);
	}
	for (y=4; y<=26; y++){
		go_scr(0,y,LV);
		go_scr(62,y,LV);
	}
	go_scr(6,4,LC);
	go_scr(28,4,LC);
	go_scr(34,4,LC);
	go_scr(56,4,LC);
	go_scr(6,26,LC);
	go_scr(28,26,LC);
	go_scr(34,26,LC);
	go_scr(56,26,LC);
	
	go_scr(6,0,AS);
	go_scr(34,0,AS);
	go_scr(0,4,AS);
	
	go_scr(28,0,AD);
	go_scr(56,0,AD);
	go_scr(62,4,AD);
	
	go_scr(0,26,BS);
	go_scr(6,30,BS);
	go_scr(34,30,BS);
	
	go_scr(28,30,BD);
	go_scr(56,30,BD);
	go_scr(62,26,BD);
	
	color(COLOR_COORD);
	int n;
	for (n=6; n<26; n+=2){
		go_sir(2,n,(n-4)/2);
		go_sir(30,n,(n-4)/2);
		go_sir(58,n,(n-4)/2);
	}
	for (n=8; n<28; n+=2){
		go_scr(n,2,61+n/2);
		go_scr(n,28,61+n/2);
		go_scr(n+28,2,61+n/2);
		go_scr(n+28,28,61+n/2);
	}	
}

void draw_giocatori(char *nickname[2],int color_g[2]){
	color(color_g[0]);
	draw_rect2(0,-3,30,-1);
	go_print(8,-2,nickname[0]);
	
	color(color_g[1]);
	draw_rect2(32,-3,62,-1);
	go_print(38,-2,nickname[1]);	
}

void draw_istruzioni(){
	cISTRUZIONI_FRECCE[4] = 24;
	cISTRUZIONI_FRECCE[7] = 25;
	cISTRUZIONI_FRECCE[10] = 26;
	cISTRUZIONI_FRECCE[13] = 27;
	color(COLOR_ISTRUCTION);
	go_print(sX_CENTER-sizeof(cISTRUZIONI_LETTERE)/2, 38, cISTRUZIONI_LETTERE);
	go_print(sX_CENTER-sizeof(cISTRUZIONI_FRECCE)/2, 36, cISTRUZIONI_FRECCE);
}

void draw_contorun(){
	color(COLOR_RECT);
	draw_rect2(-4,-4,67,42);
}

void draw_ask_question(){
	color(COLOR_RECT);
	draw_rect(3,1,75,5);
	go(7,3);
	color(COLOR_TELLER);
	printf(cTITLE_ASK_CREDENTIAL);
	color(COLOR_RECT);
	draw_rect2(3,7,75,15);
}

void draw_command(int command, int client, char *nickname[2]){
	go_print(3,34,cSPAZIO_61);
	go_print(3,36,cSPAZIO_61);
	go_print(3,38,cSPAZIO_61);
	switch(command){
		case nTURNO_GIOCATORE:{ // TOCCA A GIOCATORE
			color(COLOR_TELLER);
			go_print(31-sizeof(cTURNO_GIOCATORE)/2, 34, cTURNO_GIOCATORE);
			color(colorPlayer[client]);
			go_print(31-sizeof(nickname[client])/2, 36, nickname[client]);
			break;
		}
		case nVITTORIA_GIOCATORE:{ // VINCE IL GIOCATORE
			color(COLOR_TELLER);
			go_print(31-sizeof(cVITTORIA_GIOCATORE)/2, 34, cVITTORIA_GIOCATORE);
			color(colorPlayer[client]);
			go_print(31-sizeof(nickname[client])/2, 36, nickname[client]);
			color(COLOR_TELLER);
			go_print(31-sizeof(cPRESS_ENTER)/2, 38, cPRESS_ENTER);
			break;
		}
		case nGIOCATORE_COLPISCE_GIOCATORE:{ // IL GIOCATORE COLPISCE IL GIOCATORE
			color(colorPlayer[client]);
			go_print(31-sizeof(nickname[client])/2, 34, nickname[client]);
			color(COLOR_TELLER);
			go_print(31-sizeof(cGIOCATORE_COLPISCE_GIOCATORE)/2, 36, cGIOCATORE_COLPISCE_GIOCATORE);
			color(colorPlayer[(client+1)%2]);
			go_print(31-sizeof(nickname[(client+1)%2])/2, 38, nickname[(client+1)%2]);
			break;
		}
		case nGIOCATORE_AFFONDA_GIOCATORE:{ // IL GIOCATORE AFFONDA AL GIOCATORE
			color(colorPlayer[client]);
			go_print(31-sizeof(nickname[client])/2, 34, nickname[client]);
			color(COLOR_TELLER);
			go_print(31-sizeof(cGIOCATORE_AFFONDA_GIOCATORE)/2, 36, cGIOCATORE_AFFONDA_GIOCATORE);
			color(colorPlayer[(client+1)%2]);
			go_print(31-sizeof(nickname[(client+1)%2])/2, 38, nickname[(client+1)%2]);
			break;
		}
		case nGIOCATORE_ACQUA:{// IL GIOCATORE SPARA IN ACQUA
			color(colorPlayer[client]);
			go_print(31-sizeof(nickname[client])/2, 34, nickname[client]);
			color(COLOR_TELLER);
			go_print(31-sizeof(cGIOCATORE_ACQUA)/2, 36, cGIOCATORE_ACQUA);
			break;
		}
		case nGIOCATORE_AFFONDA1_GIOCATORE:{
			color(colorPlayer[client]);
			go_print(31-sizeof(nickname[client])/2, 34, nickname[client]);
			color(COLOR_TELLER);
			go_print(31-sizeof(cGIOCATORE_AFFONDA1_GIOCATORE)/2, 36, cGIOCATORE_AFFONDA1_GIOCATORE);
			color(colorPlayer[(client+1)%2]);
			go_print(31-sizeof(nickname[(client+1)%2])/2, 38, nickname[(client+1)%2]);
			break;
		}
		case nGIOCATORE_RISPARA:{ // IL GIOCATORE RISPARA DOVE AVEVA GIA SPARATO
			color(colorPlayer[client]);
			go_print(31-sizeof(nickname[client])/2, 34, nickname[client]);
			color(COLOR_TELLER);
			go_print(31-sizeof(cGIOCATORE_RISPARA)/2, 36, cGIOCATORE_RISPARA);
			break;
		}
	}	
}


