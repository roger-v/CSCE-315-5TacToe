package com.pastacork.a5tactoe;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.GridLayout;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.Random;

public class Board extends Activity{

    public native String testFunc();

    static {
        System.loadLibrary("interface");
    }

    private int [][] state = new int [5][5]; //0 empty, 1 X, 2 O

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
        System.out.println("JNI FUNCTION testFunc() -> " + testFunc());
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
                        System.out.println(rowIndex + ", " + colIndex);
                        if (playerTurn && state[rowIndex][colIndex] == 0) {
                            ((ImageView) view).setImageResource(R.drawable.o);
                            state[rowIndex][colIndex] = 2;
                            playerTurn = false;
                            if (MainActivity.AIType == 0)
                                dummyAstar();
                            else
                                dummyMinimax();
                        }
                    }
                }
            });
        }
    }

    private void setUpResetListener(){
        findViewById(R.id.reset).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (gameIsActive) {
                    state = new int[5][5];
                    for (int i = 0; i < 25; i++) {
                        ((ImageView) grid.getChildAt(i)).setImageDrawable(null);
                    }
                    makeFirstMove();
                }
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

    private void AIMove(int rowIndex, int colIndex){
        if (state[rowIndex][colIndex] == 0) {
            ImageView img = (ImageView) grid.getChildAt(rowIndex * 5 + colIndex);
            img.setImageResource(R.drawable.x);
            state[rowIndex][colIndex] = 1;
            return;
        }
        System.out.println("AI failed to make move at " + rowIndex + ", " + colIndex);
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

    private void dummyAstar(){
        System.out.println("dummy A star");
        int rowIndex = randInt(0, 4);
        int colIndex = randInt(0, 4);
        while (state[rowIndex][colIndex] != 0){
            rowIndex = randInt(0, 4);
            colIndex = randInt(0, 4);
        }
        AIMove(rowIndex, colIndex);
        playerTurn = true;
    }

    private void dummyMinimax(){
        System.out.println("dummy Minimax");
        int rowIndex = randInt(0, 4);
        int colIndex = randInt(0, 4);
        while (state[rowIndex][colIndex] != 0){
            rowIndex = randInt(0, 4);
            colIndex = randInt(0, 4);
        }
        AIMove(rowIndex, colIndex);
        playerTurn = true;
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

}
