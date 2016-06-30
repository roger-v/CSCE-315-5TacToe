#include "Astar.h"
/*
// prints board in a manner that is easy to read
void print_board(int b[][5])
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (b[i][j] == 0)
				cout << setw(4) << '-';
			else if (b[i][j] == 2)
				cout << setw(4) << 'o';
			else if (b[i][j] == 1)
				cout << setw(4) << 'x';
		}
		cout << endl;
	}
}
*/
//ensures that opponet doesn't win the game. Is called when opponent has 4 in a row, column or diagonal
void dont_lose(int values[][5], int b[][5], int row, int column, int diagrl, int diaglr)
{
	if (row >= 0)
	{
		for (int q = 0; q < 5; ++q)						//add the number of x's in the row
		if (b[row][q] == 0) values[row][q] += 5;
	}

	else if (column >= 0)
	{
		for (int q = 0; q < 5; ++q)						//add the number of x's in the row
		if (b[q][column] == 0) values[q][column] += 5;
	}

	else if (diagrl >= 0)								//right to left diagonal 
	{
		int p = 4;
		for (int q = 0; q < 5; ++q)
		{
			if (b[q][p] == 0) values[q][q] += 5;
			--p;
		}
	}
	else if (diaglr >= 0)								//left to right diagonal
	{
		for (int q = 0; q < 5; ++q)						
		if (b[q][q] == 0) values[q][q] += 5;
	}
}

// searches through rows using a function to assign values to values[5][5]
void check_rows(int o_count, int x_count, int values[][5], int b[][5])
{
	for (int i = 0; i < 5; ++i)								//check row viability 
	{
		for (int j = 0; j < 5; ++j)
		{
			if (b[i][j] == 2)	o_count++;					//go through each row to see how o's and x's are present
			else if (b[i][j] == 1) x_count++;
		}
		if (o_count > 0 && x_count > 0)
		{
			for (int k = 0; k < 5; ++k)						//this is a bad move. 
			if (b[i][k] == 2)	values[i][k] -= o_count;   	//add 0 to each open position in values								
		}
		else
		{
			for (int q = 0; q < 5; ++q)						//add the number of x's in the row
			if (b[i][q] == 0) values[i][q] += x_count;
		}
		if (o_count == 4) dont_lose(values, b, i, -1, -1, -1);
		x_count = 0;
		o_count = 0;
	}
}

// searches through columns using a function to assign values to values[5][5]
void check_columns(int o_count, int x_count, int values[][5], int b[][5])
{
	for (int i = 0; i < 5; ++i)								//check column viability 
	{
		for (int j = 0; j < 5; ++j)
		{
			if (b[j][i] == 2)	o_count++;					//go through each column to see how o's and x's are present
			else if (b[j][i] == 1) x_count++;
		}
		if (o_count > 0 && x_count > 0)
		{
			for (int k = 0; k < 5; ++k)						//this is a bad move. 
			if (b[k][i] == 0)	values[k][i] -= o_count;   	//add 0 to each open position in values								
		}
		else
		{
			for (int q = 0; q < 5; ++q)						//add the number of x's in the row
			if (b[q][i] == 0) values[q][i] += x_count;
		}
		if (o_count == 4) dont_lose(values, b, -1, i, -1, -1);
		x_count = 0;
		o_count = 0;

	}
	//print_board(values);									//error check
}

// searches through the left to right daigonal using a function to assign values to values[5][5]
void check_diaglr(int o_count, int x_count, int values[][5], int b[][5])
{
	for (int i = 0; i < 5; ++i)
	{
		if (b[i][i] == 2) o_count++;
		else if (b[i][i] == 1) x_count++;
	}

	if (o_count > 0 && x_count > 0)
	{
		for (int k = 0; k < 5; ++k)						//this is a bad move. 
		if (b[k][k] == 0)	values[k][k] -= o_count;   	//add 0 to each open position in values								
	}
	if (o_count == 4) dont_lose(values, b, -1, -1, -1, 1);
	else
	{
		for (int q = 0; q < 5; ++q)						//add the number of x's in the row
		if (b[q][q] == 0) values[q][q] += x_count;
	}
}

// searches through the right to left daigonal using a function to assign values to values[5][5]
void check_diagrl(int o_count, int x_count, int values[][5], int b[][5])
{
	int p = 4;
	for (int i = 0; i < 5; ++i)
	{
		if (b[i][p] == 2) o_count++;
		else if (b[i][p] == 1) x_count++;
		--p;
	}
	if (o_count == 4) dont_lose(values, b, -1, -1, 1, -1);
	p = 4;
	if (o_count > 0 && x_count > 0)
	{
		for (int k = 0; k < 5; ++k)
		{
			if (b[k][p] == 0)	values[k][p] -= o_count;   	//add 0 to each open position in values
			--p;
		}
	}
	else
	{
		p = 4;
		for (int q = 0; q < 5; ++q)						//add the number of x's in the row
		{
			if (b[q][p] == 0) values[q][p] += x_count;
			--p;
		}
	}

}

//checks for aggressive blocks where o is in a column and x is in a row
void check_aggressive_rc(int oc, int xr, int values[][5], int b[][5])
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)		
			if (b[j][i] == 2) oc++;		//column
		
		int max_xr = 0;
		for (int p = 0; p < 5; ++p)
		{
			for (int q = 0; q < 5; ++q)
			if (b[p][q] == 1) xr++;		//row
			if (xr >= max_xr) max_xr = xr;
			xr = 0;
		}
		for (int p = 0; p < 5; ++p)
		{
			for (int q = 0; q < 5; ++q)
			if (b[p][q] == 1) xr++;		//row
			if (oc >= 2 && xr == max_xr)	values[p][i] += 2 * oc;						
			xr = 0;
		}
		oc = 0;
	}
}

//checks for aggressive blocks where o is in a row and x is in a column
void check_aggressive_cr(int orow, int xc, int values[][5], int b[][5])
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
			if (b[i][j] == 2) orow++;		//row
		
		int max_xc = 0;
		for (int p = 0; p < 5; ++p)
		{
			for (int q = 0; q < 5; ++q)
			if (b[q][p] == 1) xc++;		//column
			if (xc >= max_xc) max_xc = xc;
			xc = 0;
		}
		for (int p = 0; p < 5; ++p)
		{
			for (int q = 0; q < 5; ++q)
			if (b[q][p] == 1) xc++;		//row
			if (orow >= 2 && xc == max_xc)	values[i][p] += 2 * orow;					
			xc = 0;
		}
		orow = 0;
	}
}

//selects the coordinate pair of the most optimal move
pair<int, int> coordinates(int val[][5], int b[][5])
{
	vector<pair<int, int> >moves;
	int best_move = 0;

	for (int i = 0; i < 5; ++i)								//find the best posible 
	{
		for (int j = 0; j < 5; ++j)
		{
			if (val[i][j] >= best_move && b[i][j] == 0)
				best_move = val[i][j];
		}
	}

	for (int i = 0; i < 5; ++i)								//add to vector (accounts for duplicates)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (val[i][j] == best_move && b[i][j] == 0)
				moves.push_back(make_pair(i, j));
		}
	}
	srand((int)time(0));
	int random = (rand() % moves.size());					//make random move if multiple are optimal
	return moves[random];
}

//main interface for the AI, conducts all the searches 
vector<int> a_star(int b[][5])
{
	//high_resolution_clock::time_point t1 = high_resolution_clock::now();
	int values[5][5] = { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } };
	int x = 0;
	int o = 0;

	
	check_rows(o, x, values, b);
	check_columns(o, x, values, b);
	check_diaglr(o, x, values, b);
	check_diagrl(o, x, values, b);
	check_aggressive_rc(o, x, values, b);					
	check_aggressive_cr(o, x, values, b);
	
	vector<int> ai_move;
	pair<int, int> play = coordinates(values, b);			//select move
	ai_move.push_back(play.first);
	ai_move.push_back(play.second);

	//high_resolution_clock::time_point t2 = high_resolution_clock::now();
	
	//auto duration = duration_cast<microseconds>(t2 - t1).count();
	//cerr << "Total time: " << duration<<" microsec"<<endl;
	return ai_move;
}

/*
int main()
{
	int board[5][5] = { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } };
	int a;
	int b;
	vector<int> move = {0,0};
	board[2][2] = 1;
	print_board(board);
	for (int i = 0; i < 15; i++)
	{		
		cout << endl << "player 1:  "<<endl;
		cin >> a >> b;
		board[a][b] = 2;
		move = a_star(board,3);
		board[move[0]][move[1]] = 1;
		print_board(board);
	}
}
*/