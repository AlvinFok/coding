package com.example.simpleasynctask;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private TextView textView;
    private ProgressBar progressBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = findViewById(R.id.textView_1);
        progressBar = findViewById(R.id.progressBar);
        if(savedInstanceState != null){
            textView.setText(savedInstanceState.getString("text_napping"));
        }
    }

    @Override
    protected void onSaveInstanceState(Bundle outState){
        super.onSaveInstanceState(outState);
        outState.putString("text_napping",textView.getText().toString());
    }

    public void startTask(View view) {
        textView.setText(R.string.napping);

        new SimpleAsyncTask(textView, progressBar).execute();
    }
}
