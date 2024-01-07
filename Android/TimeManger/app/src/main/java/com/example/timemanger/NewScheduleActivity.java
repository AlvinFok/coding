package com.example.timemanger;

import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.design.widget.BottomNavigationView;
import android.support.v7.app.AppCompatActivity;
import android.support.annotation.NonNull;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.TimePicker;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

public class NewScheduleActivity extends AppCompatActivity implements AdapterView.OnItemSelectedListener{
    private TextView mTextMessage;

    private static String TAG = "NewScheduletActivity";
    private String startTime;
    private String endTime;
    private String date;
    private String type;
    private int totleTime;

    private EditText nameEditText;
    private EditText commentEditText;



    private BottomNavigationView.OnNavigationItemSelectedListener mOnNavigationItemSelectedListener
            = new BottomNavigationView.OnNavigationItemSelectedListener() {

        @Override
        public boolean onNavigationItemSelected(@NonNull MenuItem item) {
            Intent intent;
            switch (item.getItemId()) {
                case R.id.navigation_report:
                    intent = new Intent(NewScheduleActivity.this, ReportActivity.class);
                    startActivity(intent);
                    return true;
                case R.id.navigation_schedule:
                    intent = new Intent(NewScheduleActivity.this, MainActivity.class);
                    startActivity(intent);
                    return true;

            }
            return false;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_new_schedule);
        BottomNavigationView navView = findViewById(R.id.nav_view);
        mTextMessage = findViewById(R.id.message);
        navView.setSelectedItemId(R.id.navigation_add);
        navView.setOnNavigationItemSelectedListener(mOnNavigationItemSelectedListener);

        nameEditText = findViewById(R.id.Whatido);
        commentEditText = findViewById(R.id.editText_comment);

        Spinner spinner = (Spinner) findViewById(R.id.option);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.DoingWhat, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);
        spinner.setOnItemSelectedListener(this);

        final TextView dateText = (TextView) findViewById(R.id.DateView);
        Button dateButton = (Button) findViewById(R.id.DateButton);
        dateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final Calendar c = Calendar.getInstance();
                int mYear = c.get(Calendar.YEAR);
                int mMonth = c.get(Calendar.MONTH);
                int mDay = c.get(Calendar.DAY_OF_MONTH);
                new DatePickerDialog(NewScheduleActivity.this, new DatePickerDialog.OnDateSetListener() {
                    @Override
                    public void onDateSet(DatePicker view, int year, int month, int day) {
                        String format = String.format("%04d-%02d-%02d",year, month+1, day);
                        dateText.setText("日期:" + format.toString());
                        date = format;
                    }

                }, mYear, mMonth, mDay).show();
            }

        });

        final TextView startTimeText = (TextView) findViewById(R.id.StartTimeView);
        Button startTimeButton = (Button) findViewById(R.id.StartTimeButton);
        startTimeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final Calendar c = Calendar.getInstance();
                int hour = c.get(Calendar.HOUR_OF_DAY);
                int minute = c.get(Calendar.MINUTE);
                new TimePickerDialog(NewScheduleActivity.this, new TimePickerDialog.OnTimeSetListener() {

                    @Override
                    public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
                        startTimeText.setText("起始時間 " + String.format("%02d:%02d", hourOfDay, minute));
                        startTime = String.format("%02d:%02d", hourOfDay, minute);
                    }
                }, hour, minute, false).show();
            }
        });

        final TextView endTimeText = (TextView) findViewById(R.id.EndTimeView);
        Button endTimeButton = (Button) findViewById(R.id.EndTimeButton);
        endTimeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final Calendar c = Calendar.getInstance();
                int hour = c.get(Calendar.HOUR_OF_DAY);
                int minute = c.get(Calendar.MINUTE);
                new TimePickerDialog(NewScheduleActivity.this, new TimePickerDialog.OnTimeSetListener() {

                    @Override
                    public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
                        endTimeText.setText("結束時間 " + String.format("%02d:%02d", hourOfDay, minute));
                        endTime = String.format("%02d:%02d", hourOfDay, minute);
                    }
                }, hour, minute, false).show();
            }
        });
    }
    private String setDateFormat(int year, int monthOfYear, int dayOfMonth) {
        return String.format("%04d-%02d-%02d", String.valueOf(year), String.valueOf(monthOfYear + 1), String.valueOf(dayOfMonth)) ;
    }

    public void createNewStroke(View view){
        Log.d(TAG, "Button click");
        Intent intent = new Intent(this, MainActivity.class);
        String name = nameEditText.getText().toString();
        String comment = commentEditText.getText().toString();
        getTotleTime();

        SQLiteDatabase db = openOrCreateDatabase("good", Context.MODE_PRIVATE,null);
        String s = "CREATE TABLE IF NOT EXISTS " +
                    "Schedule" +
                    "(Name VARCHAR(32)," +
                    "Time VARCHAR(32)," +
                    "endTime VARCHAR(32)," +
                    "Date VARCHAR(32)," +
                    "Type VARCHAR(32)," +
                    "Comment VARCHAR(32)," +
                    "Totle VARCHAR(32))";
        db.execSQL(s);

        ContentValues cv = new ContentValues(7);
        cv.put("Name", name);
        cv.put("Time", startTime);
        cv.put("endTime", endTime);
        cv.put("Date", date);
        cv.put("Type", type);
        cv.put("Comment", comment);
        cv.put("Totle", totleTime);
        db.insert("Schedule", null, cv);
        db.close();

        startActivity(intent);

    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
        type = parent.getItemAtPosition(position).toString();
        //UI test
        //nameEditText.setText(type);
        Toast.makeText(parent.getContext(), type, Toast.LENGTH_SHORT);
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {

    }

    private void getTotleTime(){
        totleTime = (Integer.parseInt(endTime.substring(0,2)) - Integer.parseInt(startTime.substring(0,2))) * 60;
        if(totleTime < 0)
            totleTime *= -1;
        totleTime += Integer.parseInt(endTime.substring(3,5)) - Integer.parseInt(startTime.substring(3,5));
    }
}
