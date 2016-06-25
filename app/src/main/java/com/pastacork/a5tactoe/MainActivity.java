package com.pastacork.a5tactoe;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void startGame(View view) {
        System.out.println("starting game");
        Intent openBoard = new Intent("com.pastacork.a5tactoe.BOARD");
        startActivity(openBoard);
    }

    public void exitButton(View view){
        System.out.println("Exiting app");
        moveTaskToBack(true);
    }
}
