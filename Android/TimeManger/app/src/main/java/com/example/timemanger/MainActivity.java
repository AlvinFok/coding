package com.example.timemanger;

import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.design.widget.BottomNavigationView;
import android.support.v7.app.AppCompatActivity;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.LinearLayoutManager;
import android.util.Log;
import android.view.MenuItem;
import android.widget.TextView;
import android.widget.Toast;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private TextView mTextMessage;
    private Cursor c;

    private BottomNavigationView.OnNavigationItemSelectedListener mOnNavigationItemSelectedListener
            = new BottomNavigationView.OnNavigationItemSelectedListener() {

        @Override
        public boolean onNavigationItemSelected(@NonNull MenuItem item) {
            Intent intent;
            switch (item.getItemId()) {

                case R.id.navigation_add:
                    Toast.makeText(MainActivity.this,"add button clicked",Toast.LENGTH_SHORT).show();
                    intent = new Intent(MainActivity.this,NewScheduleActivity.class);
                    startActivity(intent);
                    return true;
                case R.id.navigation_report:
                    Toast.makeText(MainActivity.this,"report button clicked",Toast.LENGTH_SHORT).show();
                    intent = new Intent(MainActivity.this,ReportActivity.class);
                    startActivity(intent);
                    return true;

                 default:
                     break;
            }
            return false;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        BottomNavigationView navView = findViewById(R.id.nav_view);
        mTextMessage = findViewById(R.id.message);
        navView.setSelectedItemId(R.id.navigation_schedule);
        navView.setOnNavigationItemSelectedListener(mOnNavigationItemSelectedListener);
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        String currentDate = sdf.format(new Date());                       //get phone current date
        Toast.makeText(this, "date = " + currentDate,Toast.LENGTH_SHORT).show();

        List<stroke> strokeList = new ArrayList<>();
        SQLiteDatabase db = openOrCreateDatabase("good", Context.MODE_PRIVATE,null);


        try {
            c = db.rawQuery(("SELECT * FROM Schedule WHERE Date =" + "\'" + currentDate + "\'" ), null);
            if(c.getCount() == 0){
                Log.d("get daya base","0");
                strokeList.add(new stroke("暫無行程", "", "", "","",R.drawable.nothing));
            }

            if(c.moveToFirst()) {
                do {
                    Log.d("get daya base","get");
                    int image;
                    switch (c.getString(c.getColumnIndex("Type"))){
                        case "工作":
                            image = R.drawable.work;
                            break;
                        case "娛樂":
                            image = R.drawable.entertainment;
                            break;
                        case "學習":
                            image = R.drawable.learning;
                            break;
                        case "家庭":
                            image = R.drawable.family;
                            break;
                        default:
                            image = R.drawable.nothing;
                            break;
                    }
                    strokeList.add(new stroke(c.getString(c.getColumnIndex("Name")), c.getString(c.getColumnIndex("Time")), c.getString(c.getColumnIndex("endTime")), c.getString(c.getColumnIndex("Type")), c.getString(c.getColumnIndex("Comment")), image));
                } while (c.moveToNext());
            }

        }
        catch (Exception e){
            Log.d("get daya base","nothing");
            strokeList.add(new stroke("暫無行程", "","", "","", R.drawable.nothing));
        }
        RecyclerView recyclerView = (RecyclerView) findViewById(R.id.recyclerView);
        recyclerView.setLayoutManager(new LinearLayoutManager(MainActivity.this));
        recyclerView.setAdapter(new strokeAdapter(this, strokeList));

    }
}
