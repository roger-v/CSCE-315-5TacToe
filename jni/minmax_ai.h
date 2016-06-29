//
// Created by PASTACORK on 6/28/2016.
//
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "timer.h"
#include <stdlib.h>
#include <jni.h>
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

bool pruneBestMove(AiMove newAiMove);

bool pruneWorstMove(AiMove newAiMove);

AiMove pruning(int player, AiMove move);

AiMove checkBestMovePrune();

bool loopAction();

int checkVictory(BOARD board);

void v0_recurse(BOARD& board, MOVE_LIST& moves, int player,int depth);

void v1_recurse(BOARD& board, MOVE_LIST& moves, int player,int depth);

AiMove AiPlayerMove(BOARD& board, int player, int depth);

void performMove(BOARD& board);

JNIEXPORT jstring JNICALL testCPPFunc(JNIEnv* env, jobject thiz);
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
