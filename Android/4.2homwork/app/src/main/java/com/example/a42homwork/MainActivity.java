package com.example.a42homwork;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.CheckBox;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private String message = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void showToast(View view) {

        Toast.makeText(getApplicationContext(), message, Toast.LENGTH_SHORT).show();
    }

    public void checkBoxClicked(View view) {
        Log.d("checkBoxClicked", "get in");
        boolean checked = ((CheckBox)view).isChecked();
        Log.d("checkBoxClicked", "here");

        switch (view.getId()){
            case R.id.Cherries:
                if(checked)
                message += getString(R.string.cherries) +" ";
                break;
            case R.id.chocolate_syrup:
                if(checked)
                message += getString(R.string.chocolate_syrup)+" ";
                break;
            case R.id.Crushed_nuts:
                if(checked)
                message += getString(R.string.crushed_nuts)+" ";
                break;
            case R.id.orio_cookie_crumbles:
                if(checked)
                message += getString(R.string.orio_cookie_crumbles)+" ";
                break;
            case R.id.Sprinkles:
                if(checked)
                message += getString(R.string.sprinkles)+" ";
                break;
            default:
                break;
        }
    }
}
