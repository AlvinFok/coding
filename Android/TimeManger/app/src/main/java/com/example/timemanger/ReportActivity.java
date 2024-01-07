package com.example.timemanger;

import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Color;
import android.os.Bundle;
import android.os.strictmode.SqliteObjectLeakedViolation;
import android.support.design.widget.BottomNavigationView;
import android.support.v7.app.AppCompatActivity;
import android.support.annotation.NonNull;
import android.util.Log;
import android.view.MenuItem;
import android.widget.TextView;
import android.widget.Toast;

import com.github.mikephil.charting.charts.PieChart;
import com.github.mikephil.charting.components.Legend;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.PieData;
import com.github.mikephil.charting.data.PieDataSet;
import com.github.mikephil.charting.data.PieEntry;
import com.github.mikephil.charting.formatter.PercentFormatter;
import com.github.mikephil.charting.highlight.Highlight;
import com.github.mikephil.charting.listener.OnChartValueSelectedListener;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class ReportActivity extends AppCompatActivity {


    private static String TAG = "ReportActivity";

    private int[] yData = {0,0,0,0};
    private String[] xData = {"工作", "娛樂", "學習", "家庭"};
    private PieChart pieChart;

    private BottomNavigationView.OnNavigationItemSelectedListener mOnNavigationItemSelectedListener//the bar navigation
            = new BottomNavigationView.OnNavigationItemSelectedListener() {

        @Override
        public boolean onNavigationItemSelected(@NonNull MenuItem item) {
            Intent intent;
            switch (item.getItemId()) {
                case R.id.navigation_schedule:
                    intent = new Intent(ReportActivity.this,MainActivity.class);
                    startActivity(intent);
                    return true;
                case R.id.navigation_add:
                    intent = new Intent(ReportActivity.this,NewScheduleActivity.class);
                    startActivity(intent);
                    return true;

            }
            return false;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_report);
        BottomNavigationView navView = findViewById(R.id.nav_view);
        //mTextMessage = findViewById(R.id.message);
        navView.setOnNavigationItemSelectedListener(mOnNavigationItemSelectedListener);
        navView.setSelectedItemId(R.id.navigation_report);
        Log.d(TAG, "onCreat:creat the chart");

        pieChart = (PieChart) findViewById(R.id.PieChartID);
        //pieChart.getDescription().setText("cool");
        pieChart.setRotationEnabled(true);
        pieChart.setHoleRadius(63f);
        pieChart.setTransparentCircleAlpha(200);
        pieChart.setUsePercentValues(true);
        pieChart.setTransparentCircleRadius(70);


        addDataSet();

        pieChart.setOnChartValueSelectedListener(new OnChartValueSelectedListener() {
            @Override
            public void onValueSelected(Entry e, Highlight h) {
                Log.d(TAG, "onValue: value chart");
                Log.d(TAG,"onValue: " + e.toString());
                Log.d(TAG,"onValue: " + h.toString());

                int pos1 = e.toString().indexOf("y: ");
                String sales = e.toString().substring(pos1+3);

                for(int i = 0; i < yData.length; i++){
                    if(yData[i] == Float.parseFloat(sales)){
                        pos1 = i;
                        break;
                    }
                }
                String employee = xData[pos1];
                Toast.makeText(ReportActivity.this, "type: " + employee + "\n" + "num: " + sales, Toast.LENGTH_LONG).show();
            }

            @Override
            public void onNothingSelected() {

            }
        });
    }

    private void addDataSet() {
        Log.d(TAG, "addDataSet start");
        List<PieEntry> yEntrys = new ArrayList<>();
        ArrayList<String> xEntrys = new ArrayList<>();
        xEntrys.add("工作");
        xEntrys.add("娛樂");
        xEntrys.add("學習");
        xEntrys.add("家庭");

        SQLiteDatabase db = openOrCreateDatabase("good", Context.MODE_PRIVATE,null);
        Cursor c;
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        String currentDate = sdf.format(new Date());

        try {
            c = db.rawQuery(("SELECT * FROM Schedule WHERE Date =" + "\'" + currentDate + "\'" ), null);
            if(c.getCount() ==  0){
                Log.d("get daya base","0");
                yData[0] = 0;
                yData[1] = 0;
                yData[2] = 0;
                yData[3] = 0;
            }

            if(c.moveToFirst()) {
                do {
                    switch (c.getString(c.getColumnIndex("Type"))){
                        case "工作":
                            yData[0] += c.getInt(c.getColumnIndex("Totle"));
                            break;
                        case "娛樂":
                            yData[1] += c.getInt(c.getColumnIndex("Totle"));
                            break;
                        case "學習":
                            yData[2] += c.getInt(c.getColumnIndex("Totle"));
                            break;
                        case "家庭":
                            yData[3] += c.getInt(c.getColumnIndex("Totle"));
                            break;
                        default:
                            yData[0] = 0;
                            yData[1] = 0;
                            yData[2] = 0;
                            yData[3] = 0;
                            break;
                    }
                } while (c.moveToNext());
            }

        }
        catch (Exception e){
            Log.d("get daya base","nothing");
        }

        yEntrys.add(new PieEntry(yData[0], "工作"));
        yEntrys.add(new PieEntry(yData[1], "娛樂"));
        yEntrys.add(new PieEntry(yData[2], "學習"));
        yEntrys.add(new PieEntry(yData[3], "家庭"));


        //製作data set
        PieDataSet pieDataSet = new PieDataSet(yEntrys,"");
        pieDataSet.setSliceSpace(5);
        pieDataSet.setValueTextSize(30);

        //data set 上色
        ArrayList<Integer> colors = new ArrayList<>();

        colors.add(Color.rgb(255,165,0));//org
        colors.add(Color.rgb(238, 44, 44));//red
        colors.add(Color.rgb(128, 238, 104));//green
        colors.add(Color.rgb(30, 144, 255));//blue

        pieDataSet.setColors(colors);

        //說明data set
        Legend l = pieChart.getLegend();
        l.setEnabled(true);
        l.setForm(Legend.LegendForm.CIRCLE);
        l.setVerticalAlignment(Legend.LegendVerticalAlignment.TOP);
        l.setHorizontalAlignment(Legend.LegendHorizontalAlignment.LEFT);
        l.setOrientation(Legend.LegendOrientation.HORIZONTAL);


        //create data object
        PieData pieData = new PieData(pieDataSet);
        pieData.setValueFormatter(new PercentFormatter(pieChart));
        pieChart.setData(pieData);
        pieChart.invalidate();
    }

    private void openDateBase(){
        SQLiteDatabase db = openOrCreateDatabase("good", Context.MODE_PRIVATE,null);
    }

}
