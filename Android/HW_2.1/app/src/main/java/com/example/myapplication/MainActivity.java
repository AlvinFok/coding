package com.example.myapplication;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private int count = 0;
    private TextView showCount;
    private static final String LOG_TAG = MainActivity.class.getSimpleName();
    public static  final String EXTRA_COUNTNUM = ".com.example.android.towactivities.extra.Message";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        showCount = (TextView) findViewById(R.id.show_count);
    }

    public void showToast(View view) {
        Toast toast = Toast.makeText(this,R.string.toast_massage, Toast.LENGTH_SHORT);
        toast.show();
    }

    public void showCount(View view) {
        count++;
        if(showCount != null){
            showCount.setText(Integer.toString(count));
        }

    }

    public void launchSecondActivicty(View view) {
        Log.d(LOG_TAG, "button_hello click");
        Intent intent = new Intent(this,SecondActivity.class);
        intent.putExtra(EXTRA_COUNTNUM,count);
        startActivity(intent);
    }
}
