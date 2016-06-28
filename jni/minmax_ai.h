//
// Created by PASTACORK on 6/28/2016.
//
#include <cstdlib>
#include <vector>
#include <iostream>
#ifndef INC_5TACTOE_MINMAX_AI_H
#define INC_5TACTOE_MINMAX_AI_H

#ifdef __cplusplus
extern "C" {
#endif



using namespace std;
//global names for in-game relations
const int _aiPlayer = 1; //x
const int _user = 2; //0
const int TIE_VAL = -1;
const int NO_VAL = 0;
const int maxDepth = 5;
const int gridSize = 5;
const int HARD = 3;
const int MEDIUM = 2;
const int EASY = 1;

struct AiMove{//[3]
	AiMove() {};
	AiMove(int arg) : score(arg) {}
	int x;
	int y;
	int score;
	int guessScore;
};

struct BOARD{
	int boardM[5][5];
	void setPlay(int x, int y, int player){
		boardM[x][y] = player;
	}
    void setPlay(AiMove move, int player){
        boardM[move.x][move.y] = player;
    }
};
struct MOVE_LIST{
	vector<AiMove> list;
};

AiMove checkBestMove(vector<AiMove> moves, int Ai_or_user);

AiMove AiPlayerMove(BOARD& board, int player, int depth);
void loopAction();

int checkVictory(BOARD board) {//[3]--modifed from original source
    bool victory;
    int c;
    // Check the rows
    for (int y = 0; y < 5; y++) {
        c = board.boardM[0][y];//getVal(0, y);
        if (c != NO_VAL) {
            victory = true;
            for (int x = 0; x < 5; x++) {
                if (board.boardM[x][y] != c) {
                    victory = false;
                    break;
                }
            }
            if (victory) return c;
        }
    }
    // Check the columns
    for (int x = 0; x < 5; x++) {
        c = board.boardM[x][0];//getVal(x, 0);
        if (c != NO_VAL) {
            victory = true;
            for (int y = 0; y < 5; y++) {
                if (board.boardM[x][y] != c) {
                    victory = false;
                    break;
                }
            }
            if (victory) return c;
        }
    }
    // Check top left diagonal
    c =board.boardM[0][0];// getVal(0, 0);
    if (c != NO_VAL) {
        victory = true;
        for (int xy = 0; xy < 5; xy++) {
            if (board.boardM[xy][xy] != c) {
                victory = false;
                break;
            }
        }
        if (victory) return c;
    }
    // Check top right diagonal
    c = board.boardM[5-1][0];
    if (c != NO_VAL) {
        victory = true;
        for (int xy = 0; xy < 5; xy++) {
            if (board.boardM[5 - xy - 1][xy] != c) {
                victory = false;
                break;
            }
        }
        if (victory) return c;
    }
    // Check for tie game
    for (int i = 0; i < 5; i++) {
    	for(int z = 0; z <5; z++){
    		if (board.boardM[i][z] == NO_VAL) return NO_VAL;
    	}
    }
    // If we get here, every spot was filled, so return tie
    return TIE_VAL;
}

/*
[1]- http://stackoverflow.com/questions/20287095/checking-if-all-elements-of-a-vector-are-equal-in-c
[2]- http://stackoverflow.com/questions/15531258/test-if-all-elements-of-a-vector-are-equal
[3]- https://www.youtube.com/watch?v=CwziaVrM_vc
	-Author: MakingGamesWithBen
*/

#ifdef __cplusplus
}
#endif

#endif //INC_5TACTOE_MINMAX_AI_H
