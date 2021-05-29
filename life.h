#include <cctype>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <unistd.h>


using namespace std;

struct Point
{
	int x;
	int y;
};

class GameBoard
{

	public:
		GameBoard(int size);
		~GameBoard();
		void display_board();
		void progress_state();


	private:
		int board_size;
		int ** board;
		bool kill_cell(int, int);

};

		
