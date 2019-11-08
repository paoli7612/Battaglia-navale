//launcher/main.cpp
#include "info.cpp"
char key_pressed;
int main(int argc, char *argv[]){
	init_terminal(LAUNCHER);
	int running = true;
	draw_launcher();
	while (running){
		select_menu();
		switch(select_y){
			case mSTART:
				if (argc == 2) system("start client/main.exe byBatch");
				else system("start ../client/main.exe");
				running = false;
				break;
			case mSERVER:
				if (argc == 2) system("start server/main.exe byBatch");
				else system("start ../server/main.exe");
				running = false;
				break;
			case mINFO:
				info_show();
				draw_launcher();
				break;
			case mEXIT:
				running = false;
				break;
		}
	}
    return 0;
}
