#include "life.h"

GameBoard::GameBoard()
{
	board = NULL;
}

GameBoard::GameBoard(int x, int y)
{
	board_width = x;
	board_height = y;
	cell_count = x * y;

	srand(time(NULL));
	board = new int * [board_width];

	for (int i=0; i < board_width; ++i)
	{
		board[i] = new int [board_height];

		for (int j=0; j < board_height; ++j)
		{
			board[i][j] = rand() % 2;
		}
	}
}

GameBoard::~GameBoard()
{
	for (int i=0; i < board_width; ++i)
	{
		delete [] board[i];
	}
	
	delete [] board;
}

void GameBoard::display_board()
{
	int index = 0;
	
	while (index < board_height)
	{
		for (int i=0; i < board_width; ++i)
		{
			if (board[i][index] == 1)
				cout << "#" << ' ' << flush;
			else
				cout << ' ' << ' ' << flush;
		}

		cout << endl;

		++index;
	}
}

void GameBoard::progress_state()
{
	int kill_index = 0;
	int revive_index = 0;
	Point cells_to_kill[cell_count];
	Point cells_to_revive[cell_count];

	int index = 0;
	
	while (index < board_width)
	{
		for (int i=0; i < board_height; ++i)
		{
			if (kill_cell(index, i))
			{
				cells_to_kill[kill_index] = {index, i};
				++kill_index;
			}

			else
			{
				cells_to_revive[revive_index] = {index, i};
				++revive_index;
			}
		}

		++index;
	}

	for (int k=0; k < kill_index; ++k)
	{
		board[cells_to_kill[k].x][cells_to_kill[k].y] = 0;
	}

	for (int r=0; r < revive_index; ++r)
	{
		board[cells_to_revive[r].x][cells_to_revive[r].y] = 1;
	}
}

bool GameBoard::kill_cell(int x, int y)
{

	int live_neighbor_count = 0;
	Point coordinates[8] = {{-1,-1},
				   {-1, 0},
				   {-1, 1},
				   {0, 1},
				   {1, 1},
				   {1, 0},
				   {1, -1},
				   {0, -1}};

	for (int i=0; i < 8; ++i)
	{
		int neighbor_x = x + coordinates[i].x;
		int neighbor_y = y + coordinates[i].y;

		if (!(neighbor_x < 0 || 
		    neighbor_x > board_width-1 ||
		    neighbor_y < 0 ||
		    neighbor_y > board_height-1))
		{
			if (board[neighbor_x][neighbor_y] == 1)
				++live_neighbor_count;
		}
/*
		Code for treating all cells as having 8 neighbors

		if (neighbor_x < 0)
		{
			neighbor_x = board_size -1;
		}

		if (neighbor_x > board_size -1)
		{
			neighbor_x = 0;
		}

		if (neighbor_y < 0)
		{
			neighbor_y = board_size -1;
		}

		if (neighbor_y > board_size -1)
		{
			neighbor_y = 0;
		}
		
		if (board[neighbor_x][neighbor_y] == 1)
			++live_neighbor_count;
			
*/
	}
	
	if (board[x][y] == 1)
	{
		if (live_neighbor_count < 2 || live_neighbor_count > 3)
			return 1;
		
		return 0;
	}

	else
	{
		if (live_neighbor_count == 3)
			return 0;
		
		return 1;
	}
}

void GameBoard::read_in()
{
	const char infile[] = "ggg.txt";
	ifstream in;
	in.open(infile);
	int width = 0;
	int height = 0;
	
	if (in)
	{
		char line_length[100];
		string line;

		in.get(line_length, 100, '\n');
		in.ignore(100, '\n');
		
		width = strlen(line_length);
		++height;

		board = new int * [width];
		for (int l=0; l < width; ++l)
			board[l] = NULL;

		board_width = width;

		while (in && getline(in, line))
		{
			++height;
		}

		board_height = height;

		cell_count = width * height;

		in.close();
		in.open(infile);
		int j = 0;

		while (j < board_width && in && getline(in, line))
		{
			int k = 0;

			for (int i=0; i < width; ++i)
			{
				if (!board[i])
					board[i] = new int [board_height];
				
				board[i][j] = (((int)line[k]) - 48);

				++k;
			}

			++j;
		}
	}
}	












