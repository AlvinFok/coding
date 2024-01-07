package com.example.pickerfordate;

import android.support.v4.app.DialogFragment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void showDatePicker(View view) {
        DialogFragment fragment = new DatePickerFragment();
        fragment.show(getSupportFragmentManager(), "datePicker");
    }

    public  void  processDatePickerResult(int year, int month, int day){
        String day_str = Integer.toString(day);
        String month_str = Integer.toString(month);
        String year_str = Integer.toString(year);
        String date = day_str + "/" + month_str + "/" + year_str;
        Toast.makeText(this, "Date:" + date, Toast.LENGTH_SHORT).show();
    }

    public  void showTime(View view){
        DialogFragment fragment = new DialogFragment();
        fragment.show(getSupportFragmentManager(), "timePicker");
    }

    public void processTimePickerResult(int hour, int minute){
        String hour_str = Integer.toString(hour);
        String minute_str = Integer.toString(minute);
        Toast.makeText(this, "Time:" + hour_str + minute_str, Toast.LENGTH_SHORT).show();
    }


}
