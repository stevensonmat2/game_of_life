#include "life.h"

int main()
{
	//GameBoard game(60);
	GameBoard game;
	game.read_in();

	//game.write_state();

	int go = 100;

	game.display_board();	

	while (true)
	{
		usleep(200000);
		game.progress_state();
		system("clear");
		game.display_board();
		
		--go;
	}

	return 0;
}
