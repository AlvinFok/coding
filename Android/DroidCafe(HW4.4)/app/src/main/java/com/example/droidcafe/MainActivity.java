package com.example.droidcafe;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private String orderMessage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this,
                        OrederActivity.class);
                intent.putExtra("order", orderMessage);
                startActivity(intent);
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        switch (id){
            case R.id.action_contact:
                Intent intent = new Intent(MainActivity.this, OrederActivity.class);
                intent.putExtra("contact", orderMessage);
                startActivity(intent);
                return true;
            case R.id.action_favorites:
                displayToast(getString(R.string.action_favorites_message));
                return true;
            case R.id.action_status:
                displayToast(getString(R.string.action_status_message));
                return true;
            case R.id.action_order:
                displayToast(getString(R.string.action_order_message));
                return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public  void displayToast(String message){
        Toast.makeText(getApplicationContext(), message, Toast.LENGTH_SHORT).show();
    }

    public void showDountOrder(View view){
        orderMessage = getString(R.string.donut_order_message);
        displayToast(orderMessage);
        Intent intent = new Intent(MainActivity.this, OrederActivity.class);
        intent.putExtra("contact", orderMessage);
        startActivity(intent);
    }

    public void showIceCreamOrder(View view) {
        orderMessage = getString(R.string.ice_cream_order_message);
        displayToast(orderMessage);
        Intent intent = new Intent(MainActivity.this, SecondActivity.class);
        intent.putExtra("contact", orderMessage);
        startActivity(intent);
    }

    public void showFroyoOrder(View view) {
        orderMessage = getString(R.string.froyo_order_message);
        displayToast(orderMessage);
        Intent intent = new Intent(MainActivity.this, ThridActivity.class);
        intent.putExtra("contact", orderMessage);
        startActivity(intent);
    }

}
