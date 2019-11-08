//server/partita.cpp
#include "socket.cpp"


int enemy(int turno){
	return ((turno + 1)%2);
}

void partita_draw(){
	draw_griglia();
	draw_giocatori(nickname_client,colorPlayer);
	draw_contorun();
}

int partita_start(){
	system("cls"); // CANCELLA SCHERMO
	partita_draw(); // DISEGNA GRIGLIE

	for (int n=0; n<2; n++){ // RICEVI LE NAVI
		server_send(n,"2");
		server_recv(n);
		save_naval(n);
	}

	int turno = nPLAYER_1;
	server_send_char(turno,'1');
	server_send_char(enemy(turno),'2');

	while (1){// turno vale 0 o 1
		server_recv(turno);
		int x = buffer_client[turno][0];
		int y = buffer_client[turno][1];
		char result = war_attack(enemy(turno),x,y);
		if (result == cSUNK){
			navi_affondate[turno]++;
		}
		else if (result == cSHIP_1){
			navi_affondate[turno]++;
		}

		//Invio il risoltato ai giocatori
		server_send_char(turno, result);
		server_send_char(enemy(turno), result);
		if (result == cSUNK){
			server_send_aff(turno,real_x,real_y,dir,len);
			server_send_aff(enemy(turno),real_x,real_y,dir,len);
		}
		server_send_char(enemy(turno), x);
		server_send_char(enemy(turno), y);
		turno = enemy(turno);
		if (NAVI_MAX == navi_affondate[nPLAYER_1])
			return nPLAYER_1;
		else if(NAVI_MAX == navi_affondate[nPLAYER_2])
			return nPLAYER_2;
	}

}
