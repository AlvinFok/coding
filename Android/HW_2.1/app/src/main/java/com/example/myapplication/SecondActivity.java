package com.example.myapplication;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class SecondActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);
        TextView textView_helloCount = findViewById(R.id.textView_helloAndCount);
        Intent intent = getIntent();
        int count = intent.getIntExtra(MainActivity.EXTRA_COUNTNUM,0);
        String text = "Hello!\n" + Integer.toString(count);
        textView_helloCount.setText(text);
    }
}
