//server/socket.cpp
#include "naval.cpp"
#define ML 256

using namespace std;

int port = 5000;	//Porta
char hname[256]; 	//Nome del computer
char *addr;			//Indirizzo IP
int sock;

struct hostent* he;
struct sockaddr_in saddr;

int clients[2];
char *hname_client[2];
char *addr_client[2];
char *nickname_client[2] = {cGIOCATORE_1,cGIOCATORE_2};

char buffer_toSend[ML];
char buffer_client[2][ML];

void reset_buffer(int client){
	for (int n=0; n<ML; n++){
		buffer_client[client][n] = 0;
	}
}

void reset_buffer_toSend(){
	for (int n=0; n<ML; n++){
		buffer_toSend[n] = '-';
	}
}

void apply_buffer_toSend(char *bufferP){
	for (int n=0; n<sizeof(bufferP); n++){
		buffer_toSend[n] = bufferP[n];
	}
}

void server_start(){
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2,2),&wsadata);
	sock = socket(PF_INET, SOCK_STREAM, 0);
	saddr.sin_family = PF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(port);
	bind(sock, (struct sockaddr *) &saddr, sizeof(saddr));
	gethostname (hname, sizeof (hname));
	he = gethostbyname (hname);
	addr = inet_ntoa (*(struct in_addr*) he->h_addr_list[0]);
}

void server_send(int client, char buffer[ML]){
	send(clients[client], buffer, sizeof(buffer), 0);
}

void server_send_aff(int client,int x, int y, int dir, int len){
	buffer_client[client][0] = x;
	buffer_client[client][1] = y;
	buffer_client[client][2] = dir;
	buffer_client[client][3] = len;
	send(clients[client], buffer_client[client], sizeof(buffer_client[client]), 0);
}

void server_send_char(int client, char c){
	buffer_client[client][0] = c;
	send(clients[client], buffer_client[client], sizeof(buffer_client[client]), 0);
}

void server_recv_connect_clients(int client){
	reset_buffer(client);
	for (int n=0; n<ML; n++){buffer_client[client][n]=0;}
	while (true){
		recv(clients[client], buffer_client[client], ML, 0);
		for (int n=0; n<ML; n++)
		{
			if (buffer_client[client][n] != 0){
				return;
			}
		}
	}
}

void server_recv(int client)
{
	reset_buffer(client);
	
	for (int n=0; n<ML; n++)
	{
		buffer_client[client][n]=NO_RECV;
	}
	
	while (true)
	{
		recv(clients[client], buffer_client[client], ML, 0);
		for (int n=0; n<ML; n++)
		{
			if (buffer_client[client][n] != NO_RECV){
				return;
			}
		}
	}
}


void server_stop(){
	close(sock);
	WSACleanup();
}

void server_wait_clients(){
	draw_wait_clients(1);
	for (int n=0; n<2; n++){
		// Attendi collegamento client
		listen(sock, 1);
		clients[n] = accept(sock, NULL, NULL);
		// Ricevi il nickName
		server_recv_connect_clients(n);
		nickname_client[n] = buffer_client[n];
		// Stampa il client
		draw_client(nickname_client[n],n);
	}
	draw_wait_clients(0);
	server_send(nPLAYER_1,"1");
	server_send(nPLAYER_2,"1");
	sleep(1);
	server_send(nPLAYER_1,"1");
	server_send(nPLAYER_2,"1");
}

void save_naval(int client){
	int p=0;
	for (int y=0; y<10; y++){
		for (int x=0; x<10; x++){
			mat[client][x][y] = buffer_client[client][p];
			p++;
		}
	}
	naval_draw_mat(mat[client],client);
}

void convert_char_mat(int client){
	int p=0;
	for (int y=0; y<10; y++)
		for (int x=0; x<10; x++){
			mat[client][x][y] = buffer_client[client][p];
			p++;
		}
}
