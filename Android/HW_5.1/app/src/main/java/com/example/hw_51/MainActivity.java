package com.example.hw_51;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity {
    private int level;
    private ImageView imageView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        imageView = findViewById(R.id.imageView);
    }

    public void click(View view) {
        if(view.getId() == R.id.button_min){
            if(level > 0) {
                level--;
            }
        }
        else if(view.getId() == R.id.button_plus){
            if(level < 6){
                level++;
            }
        }
        imageView.setImageLevel(level);
    }
}
