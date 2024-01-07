package com.example.hw22;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private TextView showNum;
    private int count =0;
    private int number;
    private boolean restart = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        showNum = findViewById(R.id.showNum);
        if(savedInstanceState != null){
            restart = true;
            number = savedInstanceState.getInt("number");
            showNum.setText(Integer.toString(number));
        }
    }

    public void countUp(View view) {
        if(restart){
            count = number;
            restart = false;
        }

        count++;
        showNum.setText(Integer.toString(count));
    }

    @Override
    public void onSaveInstanceState(Bundle outState){
        super.onSaveInstanceState(outState);
        outState.putInt("number", count);
    }
}
