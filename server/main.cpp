//server/main.cpp
#include "partita.cpp"
#include <fstream>

using namespace std;
void write_txt();

int main(int argc, char **argv)
{
	
	init_terminal(SERVER);
	
	server_start();
	draw_server(hname,addr,port);
	server_wait_clients();
	
	int vincitore = partita_start();
	
	if (argc == 2)
		system("start launcher/main.exe byBatch");
	else 
		system("start ../launcher/main.exe");
		
	getchar();
	write_txt();
	
	return 0;
}

void write_txt()
{
	FILE *scrivi = fopen("save.txt","w");
	for (int s=0; s<2; s++){
		for (int y=0; y<10; y++){
			for (int x=0; x<10; x++){
				fprintf(scrivi," %d\t",mat[s][x][y]);
			}
			fprintf(scrivi,"\n");
		}
		fprintf(scrivi,"\n");
		fprintf(scrivi,"\n");
	}
	fprintf(scrivi,"\n\n\n");
	fprintf(scrivi,"NAVE %d\n",SHIP);
	fprintf(scrivi,"COLPITO %d\n",SHOT);
	fprintf(scrivi,"AFFONDATO %d\n",SUNK);
	fprintf(scrivi,"ACQUA %d\n",WATER);
	fprintf(scrivi,"VUOTO %d\n",EMPTY);
	fclose(scrivi);
}


