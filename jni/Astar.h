//
// Created by PASTACORK on 6/28/2016.
//

#ifndef INC_5TACTOE_ASTAR_H
#define INC_5TACTOE_ASTAR_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <ctime>
//#include <chrono>
using namespace std;
//using namespace std::chrono;

// prints board in a manner that is easy to read
void print_board(int b[][5]);

//ensures that opponet doesn't win the game. Is called when opponent has 4 in a row, column or diagonal
void dont_lose(int values[][5], int b[][5], int row, int column, int diagrl, int diaglr);

// searches through rows using a function to assign values to values[5][5]
void check_rows(int o_count, int x_count, int values[][5], int b[][5]);

// searches through columns using a function to assign values to values[5][5]
void check_columns(int o_count, int x_count, int values[][5], int b[][5]);

// searches through the left to right daigonal using a function to assign values to values[5][5]
void check_diaglr(int o_count, int x_count, int values[][5], int b[][5]);

// searches through the right to left daigonal using a function to assign values to values[5][5]
void check_diagrl(int o_count, int x_count, int values[][5], int b[][5]);

//checks for aggressive blocks where o is in a column and x is in a row
void check_aggressive_rc(int oc, int xr, int values[][5], int b[][5]);

//checks for aggressive blocks where o is in a row and x is in a column
void check_aggressive_cr(int orow, int xc, int values[][5], int b[][5]);

pair<int,int> coor_tie_game(int b[][5]);

//selects the coordinate pair of the most optimal move
pair<int, int> coordinates(int val[][5], int b[][5]);

//main interface for the AI, conducts all the searches
vector<int> a_star(int b[][5]);

#endif //INC_5TACTOE_ASTAR_H
