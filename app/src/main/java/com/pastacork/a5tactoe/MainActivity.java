package com.pastacork.a5tactoe;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity {

    public static int difficulty = 0; //0 easy, 1 medium, 2 hard
    public static int AIType = 0; //0 = A*, 1 = Minimax

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void setAIType(View view){
        if (view.getId() == R.id.astarChoice){
            AIType = 0;
        }
        else if (view.getId() == R.id.minimaxChoice){
            AIType = 1;
        }
        View v = findViewById(R.id.aiTypeQuery);
        v.setVisibility(View.INVISIBLE);

        View w = findViewById(R.id.difficultyQuery);
        w.setVisibility(View.VISIBLE);
    }

    public void setDifficulty(View view){
        if (view.getId() == R.id.easyChoice){
            difficulty = 0;
        }
        else if (view.getId() == R.id.mediumChoice){
            difficulty = 1;
        }
        else if (view.getId() == R.id.hardChoice){
            difficulty = 2;
        }
        View w = findViewById(R.id.difficultyQuery);
        w.setVisibility(View.INVISIBLE);
        System.out.println("starting game with difficulty " + difficulty + ", and AI Type " + AIType);
        Intent openBoard = new Intent(this, Board.class);
        startActivity(openBoard);
    }

    public void startGame(View view) {
        if (findViewById(R.id.aiTypeQuery).getVisibility() == View.INVISIBLE && findViewById(R.id.difficultyQuery).getVisibility() == View.INVISIBLE) {
            View v = findViewById(R.id.aiTypeQuery);
            v.setVisibility(View.VISIBLE);
        }
    }

    public void exitButton(View view){
        if (findViewById(R.id.aiTypeQuery).getVisibility() == View.INVISIBLE && findViewById(R.id.difficultyQuery).getVisibility() == View.INVISIBLE) {
            System.out.println("Exiting app");
            moveTaskToBack(true);
        }
    }

    @Override
    public void onBackPressed(){
        if (findViewById(R.id.aiTypeQuery).getVisibility() == View.VISIBLE || findViewById(R.id.difficultyQuery).getVisibility() == View.VISIBLE){
            findViewById(R.id.aiTypeQuery).setVisibility(View.INVISIBLE);
            findViewById(R.id.difficultyQuery).setVisibility(View.INVISIBLE);
        }
        else super.onBackPressed();
    }
}
