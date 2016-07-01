package com.pastacork.a5tactoe;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.GridLayout;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.Random;

public class Board extends Activity{

    public native int [] testFunc(int [][] state);
    public native int [] minimax(int [][] state);
    public native int [] astar(int [][] state);
    public void printState(){
        String c = "";
        for (int i = 0; i < 5; i++){
            if (i > 0) c+=',';
            for (int j = 0; j < 5; j++){
                c += Integer.toString(state[i][j]);
            }
        }
        System.out.println("Current board: " + c);
    }

    static {
        System.loadLibrary("interface");
    }

    private int [][] state = new int [5][5]; //0 empty, 1 X, 2 O

    private final int X = 1;
    private final int O = 2;
    private final int TIE = 0;

    private static int slots_occupied = 0;

    private boolean playerTurn = false;

    public GridLayout grid;

    private boolean gameIsActive = true;

    public Board(){

    }

    @Override
    public void onBackPressed() {
        finish();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.board);
        grid = (GridLayout) findViewById(R.id.grid);
        makeFirstMove();
        setUpBoardListeners();
        setUpResetListener();
        setUpMenuListeners();
        setUpGameOverListener();
    }

    private boolean boardIsFull(){
        return slots_occupied == 25;
    }

    private int [] lastSlot(){
        if (slots_occupied == 24) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++){
                    if (state[i][j] == 0){
                        int ret[] = {i, j};
                        return ret;
                    }
                }
            }
        }
        int ret[] = {-1, -1};
        return ret;
    }

    private void setUpBoardListeners(){
        for (int i = 0; i < 25; i++){
            grid.getChildAt(i).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    if (gameIsActive) {
                        String name = getResources().getResourceEntryName(view.getId());
                        int rowIndex = Character.getNumericValue(name.charAt(1));
                        int colIndex = Character.getNumericValue(name.charAt(2));
                        if (playerTurn && state[rowIndex][colIndex] == 0) {
                            ((ImageView) view).setImageResource(R.drawable.o);
                            state[rowIndex][colIndex] = 2;
                            playerTurn = false;
                            slots_occupied++;
                            if (checkVictory(O)) {
                                displayVictoryMessage(O);
                                resetGame();
                                return;
                            }
                            if (MainActivity.AIType == 0) {
                                int moves[] = astar(state);
                                AIMove(moves[0], moves[1]);
                                if (checkVictory(X)) {
                                    displayVictoryMessage(X);
                                    resetGame();
                                    return;
                                }
                            }
                            else {
                                if (slots_occupied == 24)
                                    AIMove(lastSlot()[0], lastSlot()[1]);
                                else {
                                    int moves[] = minimax(state);
                                    AIMove(moves[0], moves[1]);
                                }
                                if (checkVictory(X)) {
                                    displayVictoryMessage(X);
                                    resetGame();
                                    return;
                                }
                            }
                            if (boardIsFull()){
                                displayVictoryMessage(TIE);
                                resetGame();
                                return;
                            }
                        }
                    }
                }
            });
        }
    }

    private void displayVictoryMessage(int victor){
        //0 is tie, 1 is AI, 2 is player
        View v = findViewById(R.id.gameOverWindow);
        v.setVisibility(View.VISIBLE);
        TextView tv = (TextView) findViewById(R.id.gameOverMessage);
        switch (victor){
            case 0:
                tv.setText("Tie!");
                break;
            case 1:
                tv.setText("You lost!");
                break;
            case 2:
                tv.setVisibility(View.GONE);
                findViewById(R.id.daugherity).setVisibility(View.VISIBLE);
                break;
            default:
                break;

        }
        gameIsActive = false;
    }

    private void resetGame(){
        if (gameIsActive) {
            state = new int[5][5];
            for (int i = 0; i < 25; i++) {
                ((ImageView) grid.getChildAt(i)).setImageDrawable(null);
            }
            slots_occupied = 0;
            makeFirstMove();
            printState();
        }
    }

    private void setUpResetListener(){
        findViewById(R.id.reset).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                resetGame();
                gameIsActive = true;
            }
        });
    }

    private void setUpMenuListeners(){
        findViewById(R.id.menuButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (gameIsActive) {
                    View exitToMenu = findViewById(R.id.menuQuery);
                    exitToMenu.setVisibility(View.VISIBLE);
                    gameIsActive = false;
                }
            }
        });

        findViewById(R.id.menuYesButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });

        findViewById(R.id.menuNoButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                View exitToMenu = findViewById(R.id.menuQuery);
                exitToMenu.setVisibility(View.INVISIBLE);
                gameIsActive = true;
            }
        });
    }

    private void setUpGameOverListener(){
        Button b = (Button) findViewById(R.id.gameOverButton);
        b.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                findViewById(R.id.gameOverWindow).setVisibility(View.INVISIBLE);
                findViewById(R.id.gameOverMessage).setVisibility(View.VISIBLE);
                findViewById(R.id.daugherity).setVisibility(View.GONE);
                gameIsActive = true;
                resetGame();
            }
        });
    }

    private void AIMove(int rowIndex, int colIndex){
        if (state[rowIndex][colIndex] == 0) {
            ImageView img = (ImageView) grid.getChildAt(rowIndex * 5 + colIndex);
            img.setImageResource(R.drawable.x);
            state[rowIndex][colIndex] = 1;
            playerTurn = true;
            slots_occupied++;
            return;
        }
        System.out.println("AI failed to make move at " + rowIndex + ", " + colIndex);
        printState();
        ((TextView) findViewById(R.id.gameTitle)).setText("ERROR");
    }

    private void makeFirstMove(){
        int difficulty = MainActivity.difficulty;
        int randomNumber = randInt(0, 3);
        if (difficulty == 0)
            randomSide(randomNumber);
        else if (difficulty == 1)
            randomCorner(randomNumber);
        else
            AIMove(2, 2);
        playerTurn = true;
    }

    private int randInt(int min, int max){
        Random rand = new Random();
        int randomNum = rand.nextInt((max - min) + 1) + min;
        return randomNum;
    }

    private void randomSide(int randomNumber){
        switch (randomNumber){
            case 0:
                AIMove(0, randInt(1, 3));
                break;
            case 1:
                AIMove(randInt(1, 3), 4);
                break;
            case 2:
                AIMove(4, randInt(1, 3));
                break;
            case 3:
                AIMove(randInt(1, 3), 0);
                break;
        }
    }

    private void randomCorner(int randomNumber){
        switch (randomNumber){
            case 0:
                AIMove(0,0);
                break;
            case 1:
                AIMove(0,4);
                break;
            case 2:
                AIMove(4,4);
                break;
            case 3:
                AIMove(4,0);
                break;
        }
    }

    public boolean checkVictory(int player){
        boolean rows[] = new boolean[5];
        for (int i = 0; i < 5; i++){
            rows[i] = state[i][0] == player && state[i][1] == player
                    && state[i][2] == player && state[i][3] == player
                    && state[i][4] == player;
            if (rows[i]) return true;
        }
        boolean cols[] = new boolean[5];
        for (int j = 0; j < 5; j++){
            cols[j] = state[0][j] == player && state[1][j] == player
                    && state[2][j] == player && state[3][j] == player
                    && state[4][j] == player;
            if (cols[j]) return true;
        }
        boolean diag1 = state[0][0] == player && state[1][1] == player
                && state[2][2] == player && state[3][3] == player
                && state[4][4] == player;
        if (diag1) return true;
        boolean diag2 = state[0][4] == player && state[1][3] == player
                && state[2][2] == player && state[3][1] == player
                && state[4][0] == player;
        if (diag2) return true;
        return false;
    }

}
