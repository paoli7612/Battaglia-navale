// client.cpp
#include "naval.cpp"
#define ML 256

char *enemy_nickname;
int port = 5000;
char addr[17];
char nickname[17];
char passwd[17];
int sock;
char buffer[ML];
struct sockaddr_in saddr;

void ask_credential(){
	draw_ask_question();
	
	color(COLOR_CREDENTIAL);
	go_print(5,9,ask_SERVER_IP);
	color(COLOR_SCANF);
	scanf("%16s",addr);
	fflush(stdin);
	
	color(COLOR_CREDENTIAL);
	go_print(5,11,ask_NICKNAME);
	color(COLOR_SCANF);
	scanf("%16s",nickname);
	fflush(stdin);
	
	color(COLOR_CREDENTIAL);
	go_print(5,13,ask_PASSWD);
	color(COLOR_SCANF);
	
	int n=0, enter=1;
	while (enter)
	{
		char t = getch();
		if (t == 13)
			enter = 0;
		else
		{
			passwd[n] = t;
			printf("%c",cPASSWD_CHAR);
			n++;
		}		
	}
	fflush(stdin);
	terminal_clear();
}

void reset_buffer()
{
	for (int n=0; n<ML; n++)
		buffer[n] = 0;
}

void client_send(char buffer[ML])
{
	send(sock, buffer, sizeof(buffer), 0);	
}

void client_recv()
{
	reset_buffer();
	while (true)
	{
		recv(sock, buffer, ML, 0);
		for (int n=0; n<ML; n++)
			if (buffer[n] != 0)
				return;
	}
}

void client_send_coord(int n, int c)
{
	buffer[0] = static_cast<char>(n);
	buffer[1] = static_cast<char>(c);
	send(sock, buffer, sizeof(buffer), 0);
}

int client_start()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2,2), &wsadata) == SOCKET_ERROR)
		return false;
	sock = socket(PF_INET, SOCK_STREAM, 0);
	
	if (sock==SOCKET_ERROR)
		return false;
		
	saddr.sin_family = PF_INET;
	saddr.sin_addr.s_addr = inet_addr(addr);
	saddr.sin_port = htons(port);
	
	if (connect(sock, (struct sockaddr *) &saddr, sizeof(saddr)) == SOCKET_ERROR)
		return false;
		
	client_send(nickname);
	
	draw_loading_start(false);
	client_recv();
	
	draw_loading_start(true);	
	client_recv();
	
	return true;
}



