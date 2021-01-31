//client/main.cpp
#include "partita.cpp"

int main(int argc, char *argv[]){

	ask_credential();
	init_terminal(CLIENT);
	draw_client(nickname, addr, port);
	int vincitore;

	if (client_start())
	{
		sleep(1);
		terminal_clear();
		vincitore = partita_start();
		draw_command(nVITTORIA_GIOCATORE,vincitore,nickname_client);
		getchar();
		getchar();
	}
	else
	{
		system("cls");
		printf("Connessione non riuscita");
		sleep(3);
	}

	terminal_exit();

	if (argc > 1)
		system("start launcher/main.exe byBatch");
	else
		system("start ../launcher/main.exe");
	return 0;
}
