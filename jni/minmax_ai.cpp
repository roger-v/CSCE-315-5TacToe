#include <vector>
#include <ctime>
#include <cmath>
#include "minmax_ai.h"
#include <iostream>
#include <iomanip>
#include "timer.h"
#include <stdlib.h>

using namespace std;

timer timer;

AiMove maxTracker(-1000000);
AiMove minTracker(1000000);

bool usercont;
bool aicont;

bool pruneBestMove(AiMove newAiMove){
	bool cont;
	if(newAiMove.score > maxTracker.score){
		maxTracker = newAiMove;
		cont = true;
	}
	else cont = false;

	return cont;
}

bool pruneWorstMove(AiMove newAiMove){
	bool cont;
	if(newAiMove.score < minTracker.score){
		minTracker = newAiMove;
		cont = true;
	}
	else cont = false; // if its not worse, no point, PRUNE

	return cont;
}

AiMove pruning(int player, AiMove move){
	bool cont;
	if(player == _aiPlayer){
		cont = pruneBestMove(move);
		if(cont) {
			return move;
		}
		else {
			return maxTracker;
		}
	}
	else{// player is _user
		cont = pruneWorstMove(move);
		if(cont) return move;
		else{
		 	return minTracker;
		}
	}

}

AiMove checkBestMovePrune(){
	AiMove bestmove;
	int max = abs (maxTracker.score);
	int min = abs (minTracker.score);
	if(max > min){
		bestmove = maxTracker;
	}
	else if (min > max){
		bestmove = minTracker;
	}
	else{
		return minTracker;
	}
	return bestmove;
}

bool loopAction(BOARD& board, int player ,MOVE_LIST& moves, int x, int y, int depth){
	//make move to test
	bool cont;
		AiMove newMove;
		AiMove pruneMove;
		newMove.x = x;
		newMove.y = y;
		board.setPlay(x,y,player);
		int guess = 0;
		int win = checkVictory(board);
		if(win == _aiPlayer)  guess = 10;	
		else if(win == _user) guess = -10;
		else if(win == -1) guess = 0;
		newMove.guessScore = guess;
		depth++;
		//if ai, recurse with user
		if(player == _aiPlayer){
			if(newMove.guessScore >= maxTracker.score && abs(maxTracker.score) != 1000000 ){
				aicont = false;
				board.setPlay(x,y,0);
				cont = false;
				return cont;
			}
			newMove.score = AiPlayerMove(board, _user, depth).score;
			pruneMove = pruning(player, newMove);
		}
		else{
			if(newMove.guessScore <= minTracker.score && abs(minTracker.score) != 1000000 ){
				usercont = false;
				board.setPlay(x,y,0);
				cont = false;
				return cont;
			}
			newMove.score = AiPlayerMove(board, _aiPlayer, depth).score;
			pruneMove = pruning(player, newMove);
		}
			cont = true;

		moves.list.push_back(pruneMove);
		board.setPlay(x,y,0); //set back to prev empty
		return cont;
}

//------------------------------KEEP THIS--------------------------------------
void v0_recurse(BOARD& board, MOVE_LIST& moves, int player,int depth){
	for (int y =0; y < gridSize; y++){
		for (int x =0; x < gridSize; x++){
			if(board.boardM[x][y] == 0){
				bool check = loopAction(board, player,moves, x, y,depth);
				if(!check){
					//printf("depth at breakv0: %d\n", depth);
					break;
				}
			}else continue;	
		}
	}
}

void v1_recurse(BOARD& board, MOVE_LIST& moves, int player,int depth){
	for (int x =0; x < gridSize; x++){
		for (int y =gridSize-1; y > -1; y--){
			if(board.boardM[x][y] == 0){
				bool check = loopAction(board, player,moves, x, y,depth);
				if(!check){
					//printf("depth at breakv0: %d\n", depth);
					break;
				}
			}else continue;	
		}
	}
}


//------------------------------KEEP THIS--------------------------------------

AiMove AiPlayerMove(BOARD& board, int player, int depth){
	srand (time(NULL));
	int win = checkVictory(board);
	if(win == _aiPlayer) return AiMove(10);	
	else if(win == _user) return AiMove(-10);
	else if(win == -1) return AiMove(0);

	//maybe here?
	unsigned long currtime = timer.getTime();
	int version = rand() % 2;
	//int version = 0;
	if(currtime <= 5){
		//alter back to v0,1,2,3 after testing!
		MOVE_LIST moves;
		if(version == 0) {
				v0_recurse(board, moves, player, depth);
		}
		else if(version == 1){
				v1_recurse(board, moves, player, depth);
		}

		AiMove bMove = checkBestMovePrune();
		return bMove;
	}	
	
	//return maxTracker;
	AiMove bMove = checkBestMovePrune();
	return bMove;
}

vector<int> performMove(BOARD& board){
	timer.start();
	printf("AI thinking...\n");
	maxTracker.score = -1000000;
	minTracker.score = 1000000;
	AiMove bestmove = AiPlayerMove(board, 1, 0);//0 is depth
	cout<<"AI Played: "<<bestmove.x<<", "<<bestmove.y<<endl;
	printf("score: %d\n", bestmove.score);
	int check = checkVictory(board);
	if(check == 1 || check == 2 || check == -1){
		printf("PLAYER %d WON! \n",check);
	}
	else{
		board.boardM[bestmove.x][bestmove.y] = _aiPlayer;
	}
	timer.stop();
	int crtime = timer.getTime();
	printf("Time: %d\n",crtime);
	timer.reset();
	vector<int> v;
	v.push_back(bestmove.x);
	v.push_back(bestmove.y);
	return v;
}