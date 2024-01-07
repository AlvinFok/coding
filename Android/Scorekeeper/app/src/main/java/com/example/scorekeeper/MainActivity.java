package com.example.scorekeeper;

import android.content.SharedPreferences;
import android.preference.Preference;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.app.AppCompatDelegate;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private int score1;
    private int score2;
    private TextView score1_view;
    private TextView score2_view;
    static final String STATE_SCORE_1 = "Team 1 Score";
    static final String STATE_SCORE_2 = "Team 2 Score";
    private SharedPreferences preference;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        score1_view = findViewById(R.id.score_1);
        score2_view = findViewById(R.id.score_2);
        preference = getSharedPreferences("com.example.android.scorekeeper", MODE_PRIVATE);
        score1 = preference.getInt("score1",0);
        score2 = preference.getInt("score2",0);
        score1_view.setText(String.valueOf(score1));
        score2_view.setText(String.valueOf(score2));
        /*if(savedInstanceState != null){
            score1 = savedInstanceState.getInt(STATE_SCORE_1);
            score2 = savedInstanceState.getInt(STATE_SCORE_2);
            score1_view.setText(String.valueOf(score1));
            score2_view.setText(String.valueOf(score2));
        }*/

    }

    @Override
    protected void onPause() {
        super.onPause();
        SharedPreferences.Editor preferencesEditor = preference.edit();
        preferencesEditor.putInt("score1",score1);
        preferencesEditor.putInt("score2",score2);
        preferencesEditor.apply();
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        outState.putInt(STATE_SCORE_1,score1);
        outState.putInt(STATE_SCORE_2,score2);
        super.onSaveInstanceState(outState);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if(item.getItemId() == R.id.nigt_mode){
            int nightMode = AppCompatDelegate.getDefaultNightMode();
            if(nightMode == AppCompatDelegate.MODE_NIGHT_YES){
                AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_NO);
                Log.d("set night mode","YES");
            }
            else{
                AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_YES);
                Log.d("set night mode","NO");
            }
            recreate();
        }
        return  true;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main_menu, menu);
        int nightMode = AppCompatDelegate.getDefaultNightMode();
        if(nightMode == AppCompatDelegate.MODE_NIGHT_YES){
            menu.findItem(R.id.nigt_mode).setTitle(R.string.day_mode);
        }
        else{
            menu.findItem(R.id.nigt_mode).setTitle(R.string.night_mode);
        }
        return true;
    }

    public void decreaseScore(View view) {
        switch (view.getId()){
            case R.id.decreaseTeam1:
                score1--;
                score1_view.setText(String.valueOf(score1));
                break;
            case R.id.decreaseTeam2:
                score2--;
                score2_view.setText(String.valueOf(score2));
                break;
        }
    }

    public void increaseScore(View view) {
        switch (view.getId()){
            case R.id.increaseTeam1:
                score1++;
                score1_view.setText(String.valueOf(score1));
                break;
            case R.id.increaseTeam2:
                score2++;
                score2_view.setText(String.valueOf(score2));
                break;
        }
    }
}
