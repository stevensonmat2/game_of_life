#include <cctype>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <string>


using namespace std;

struct Point
{
	int x;
	int y;
};

class GameBoard
{

	public:
		GameBoard();
		GameBoard(int x, int y);
		~GameBoard();
		void display_board();
		void progress_state();
		void read_in();


	private:
		int board_width;
		int board_height;
		int cell_count;
		int ** board;
		bool kill_cell(int, int);

};

		
