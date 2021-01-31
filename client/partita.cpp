// client/partita.cpp
#include "socket.cpp"

char *nickname_client[2] = {nickname,cNAME_ENEMY};

int enemy(int turno)
{
	return (turno + 1) % 2;
}

void send_navi()
{
	client_recv();
	char navi[100];
	int p=0;
	
	for (int y=0; y<10; y++)
	{
		for (int x=0; x<10; x++)
		{
			navi[p] = mat[nPLAYER_1][HIDE][x][y];
			p++;
		}
	}
	send(sock, navi, 100, 0);
}

int partita_start()
{
	draw_griglia();
	draw_giocatori(nickname_client,colorPlayer);
	draw_contorun();
	
	pos_ships();
	send_navi();
	client_recv();
	
	int turno;
	if (buffer[0] == '1')
	{
		turno = 0;
	}
	else{
		turno = 1;
	}

	int dir;
	int len;
	int real_x;
	int real_y;
	
	while(1){
		draw_command(nTURNO_GIOCATORE,turno,nickname_client);
		if (turno == 0)
		{	// proprio turno
			select_pos();
			client_send_coord(select_x,select_y);
			client_recv();
			int result = buffer[0];
			if (result == cSUNK){
				client_recv();
				dir = buffer[2];
				len = buffer[3];
				real_x = buffer[0];
				real_y = buffer[1];
			}
			if (result == cFAKE)
			{	// GIA SPARATO
				draw_command(nGIOCATORE_RISPARA,turno,nickname_client);
			}
			if (result == cWATER)
			{	// ACQUA
				mat[nPLAYER_2][DRAW][select_x][select_y] = WATER;
				draw_command(nGIOCATORE_ACQUA,turno,nickname_client);
			}
			else if (result == cSHOT)
			{  // COLPITO
				mat[nPLAYER_2][DRAW][select_x][select_y] = SHOT;
				draw_command(nGIOCATORE_COLPISCE_GIOCATORE,turno,nickname_client);

			}
			else if (result == cSUNK)
			{ // COLPITO E AFFONDATO
				navi_affondate[nPLAYER_1]++;
				set_sunk(nPLAYER_2,real_x,real_y,dir,len);
				draw_command(nGIOCATORE_AFFONDA_GIOCATORE,turno,nickname_client);
			}
			else if (result == cSHIP_1)
			{ // AFFONDATO IN UN COLPO
				navi_affondate[nPLAYER_1]++;
				mat[nPLAYER_2][DRAW][select_x][select_y] = SUNK;
				set_sunk1(nPLAYER_2,select_x,select_y);
				draw_command(nGIOCATORE_AFFONDA1_GIOCATORE,turno,nickname_client);
			}
			draw_mat(nPLAYER_2);
		}
		else
		{
			client_recv();
			int result = buffer[0];
			if (result == cSUNK)
			{
				client_recv();
				dir = buffer[2];
				len = buffer[3];
				real_x = buffer[0];
				real_y = buffer[1];
			}
			client_recv();
			int x = buffer[0];
			client_recv();
			int y = buffer[0];
			if (result == cFAKE)
			{
				draw_command(nGIOCATORE_RISPARA,turno,nickname_client);
			}
			if (result == cSHOT)
			{
				mat[nPLAYER_1][DRAW][x][y] = SHOT;
				draw_command(nGIOCATORE_COLPISCE_GIOCATORE,turno,nickname_client);
			}
			else if (result == cWATER)
			{
				mat[nPLAYER_1][DRAW][x][y] = WATER;
				draw_command(nGIOCATORE_ACQUA,turno,nickname_client);
			}
			else if (result == cSUNK)
			{
				navi_affondate[nPLAYER_2]++;
				set_sunk(nPLAYER_1,real_x,real_y,dir,len);
				draw_command(nGIOCATORE_AFFONDA_GIOCATORE,turno,nickname_client);
			}
			else if (result == cSHIP_1)
			{
				navi_affondate[nPLAYER_2]++;
				mat[nPLAYER_1][DRAW][x][y] = SUNK;
				draw_command(nGIOCATORE_AFFONDA1_GIOCATORE,turno,nickname_client);
			}
			draw_mat(nPLAYER_1);
		}
		sleep(3);
		turno = enemy(turno);
		
		if (SHIPS_MAX == navi_affondate[nPLAYER_1])
			return nPLAYER_1;
		else if(SHIPS_MAX == navi_affondate[nPLAYER_2])
			return nPLAYER_2;
	}
}
