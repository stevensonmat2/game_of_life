#include "life.h"

GameBoard::GameBoard()
{
	board = NULL;
}

GameBoard::GameBoard(int size)
{
	board_size = size;

	srand(time(NULL));
	board = new int * [size];

	for (int i=0; i < size; ++i)
	{
		board[i] = new int [size];

		for (int j=0; j < size; ++j)
		{
			board[i][j] = rand() % 2;
		}
	}
}

GameBoard::~GameBoard()
{
	for (int i=0; i < board_size; ++i)
	{
		delete [] board[i];
	}
	
	delete [] board;
}

void GameBoard::display_board()
{
	int index = 0;
	
	while (index < board_size)
	{
		for (int i=0; i < board_size; ++i)
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
	Point cells_to_kill[board_size*board_size];
	Point cells_to_revive[board_size*board_size];

	int index = 0;
	
	while (index < board_size)
	{
		for (int i=0; i < board_size; ++i)
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
		    neighbor_x > board_size-1 ||
		    neighbor_y < 0 ||
		    neighbor_y > board_size-1))
		{
			if (board[neighbor_x][neighbor_y] == 1)
				++live_neighbor_count;
		}
	}
	
	if (board[x][y] == 1)
	{
		return live_neighbor_count <= 1 || 
		live_neighbor_count > 3? 1 : 0;
	}
	
	return live_neighbor_count == 3? 0 : 1;
}

void GameBoard::read_in()
{
	const char infile[] = "ggg.txt";
	//const char infile[] = "ext.txt";
	ifstream in;
	in.open(infile);
	int size = 0;
	
	if (in)
	{
		char length[100];
		string line;

		in.get(length, 100, '\n');
		in.ignore(100, '\n');
		
		size = strlen(length);

		board = new int * [size];
		for (int l=0; l < size; ++l)
			board[l] = NULL;

		board_size = size;
		in.close();
		in.open(infile);
		int j = 0;

		while (j < size && in && getline(in, line))
		{
			int k = 0;

			for (int i=0; i < size; ++i)
			{
				if (!board[i])
					board[i] = new int [size];
				
				board[i][j] = (((int)line[k]) - 48);

				++k;
			}

			++j;
		}
	}
}	












