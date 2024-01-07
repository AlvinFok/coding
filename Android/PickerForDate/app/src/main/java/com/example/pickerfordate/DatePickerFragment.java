package com.example.pickerfordate;


import android.app.Dialog;
import android.app.TimePickerDialog;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.Fragment;
import android.text.format.DateFormat;
import android.widget.TimePicker;

import java.util.Calendar;

import java.util.Calendar;
import java.util.Calendar;

/**
 * A simple {@link Fragment} subclass.
 */
public class DatePickerFragment extends DialogFragment implements TimePickerDialog.OnTimeSetListener {



    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState){
        final Calendar c =Calendar.getInstance();
        int hour = c.get(Calendar.HOUR_OF_DAY);
        int minute = c.get(Calendar.MINUTE);

        return  new TimePickerDialog(getActivity(), this, hour, minute,  DateFormat.is24HourFormat(getActivity()));

    }

    /*@Override
    public void onDateSet(DatePicker view, int year, int month, int dayOfMonth) {
        MainActivity activity = (MainActivity)getActivity();
        activity.processDatePickerResult(year, month, dayOfMonth);
    }*/

    @Override
    public  void onTimeSet(TimePicker view, int hour, int minute){
        MainActivity activity = (MainActivity) getActivity();
        activity.processTimePickerResult(hour, minute);
    }
}
