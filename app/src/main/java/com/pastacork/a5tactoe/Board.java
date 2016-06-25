package com.pastacork.a5tactoe;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.GridLayout;
import android.widget.ImageView;

import java.util.Random;

public class Board extends Activity{

    public int difficulty = 0; //0 = easy, 1 = medium, 2 = hard;

    private int [][] state = new int [5][5]; //0 empty, 1 X, 2 O

    private boolean playerTurn = false;

    public GridLayout grid;

    private boolean gameIsActive = true;

    public Board(){

    }

    public Board(int difficulty){
        this.difficulty = difficulty;
    }

    @Override
    public void onBackPressed() {
        moveTaskToBack(true);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        System.out.println("activity started");
        setContentView(R.layout.board);
        grid = (GridLayout) findViewById(R.id.grid);
        makeFirstMove();
    }

    public void resetGame(View view){
        if (gameIsActive) {
            System.out.println("resetting now");
            state = new int[5][5];
            for (int i = 0; i < 25; i++) {
                ((ImageView) grid.getChildAt(i)).setImageDrawable(null);
            }
            makeFirstMove();
        }
    }

    public void playerMove(View view){
        if (gameIsActive) {
            String name = getResources().getResourceEntryName(view.getId());
            int rowIndex = Character.getNumericValue(name.charAt(1));
            int colIndex = Character.getNumericValue(name.charAt(2));
            System.out.println(rowIndex + ", " + colIndex);
            if (playerTurn && state[rowIndex][colIndex] == 0) {
                ((ImageView) view).setImageResource(R.drawable.o);
                state[rowIndex][colIndex] = 2;
                playerTurn = false;
                dummyAI();
            }
        }
    }

    private void AIMove(int rowIndex, int colIndex){
        if (state[rowIndex][colIndex] == 0) {
            ImageView img = (ImageView) grid.getChildAt(rowIndex * 5 + colIndex);
            img.setImageResource(R.drawable.x);
            System.out.println("AI made move at " + rowIndex + ", " + colIndex);
            state[rowIndex][colIndex] = 1;
            return;
        }
        System.out.println("AI failed to make move at " + rowIndex + ", " + colIndex);
    }

    private void makeFirstMove(){
        int randomNumber = randInt(0, 3);
        //difficulty = 0 -> 0 for top, 1 for right, 2 for bottom, 3 for left
        //difficulty = 1 -> 0 for top left, 1 for top right, 2 for bottom right, 3 for bottom left
        if (difficulty == 0){
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
        else if (difficulty == 1){
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
        else {
            AIMove(2, 2);
        }
        playerTurn = true;
    }

    private int randInt(int min, int max){
        Random rand = new Random();
        int randomNum = rand.nextInt((max - min) + 1) + min;
        return randomNum;
    }

    private void dummyAI(){
        int rowIndex = randInt(0, 4);
        int colIndex = randInt(0, 4);
        while (state[rowIndex][colIndex] != 0){
            rowIndex = randInt(0, 4);
            colIndex = randInt(0, 4);
        }
        AIMove(rowIndex, colIndex);
        playerTurn = true;
    }

    public void showExitPrompt(View view){
        if (gameIsActive) {
            View exitToMenu = findViewById(R.id.menuQuery);
            exitToMenu.setVisibility(View.VISIBLE);
            gameIsActive = false;
        }
    }

    public void menuQueryButtons(View view){
        if (view.getId() == R.id.menuYesButton){
            finish();
        }
        else if (view.getId() == R.id.menuNoButton){
            View exitToMenu = findViewById(R.id.menuQuery);
            exitToMenu.setVisibility(View.INVISIBLE);
            gameIsActive = true;
        }
    }

}
