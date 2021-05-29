#include "life.h"

int main()
{
	GameBoard game(60);
	int go = 3;

	game.display_board();	

	while (true)
	{
		usleep(400000);
		system("clear");
		game.progress_state();
		game.display_board();
		
		--go;
	}

	return 0;
}
