package com.example.simpleasynctask;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.ProgressBar;
import android.widget.TextView;

import java.lang.ref.WeakReference;
import java.util.Random;

public class SimpleAsyncTask extends AsyncTask<Void,  Integer, String> {
    private WeakReference<TextView> textView;
    private ProgressBar progressBar;
    SimpleAsyncTask(TextView tv, ProgressBar pb){
        progressBar = pb;
        textView = new WeakReference<>(tv);
    }
    @Override
    protected String doInBackground(Void... voids){
        Random r = new Random();
        int n = r.nextInt(11);
        int s = n * 200;
        int percentage = (int)(s * 0.01);
        try{
            for(int i=0,count = 0; i<s;i+=percentage, count++){
                Thread.sleep(i);
                publishProgress(count);
            }

        }catch (InterruptedException e){
            e.printStackTrace();
        }
        Log.d("ProgressBackground","finish");

        return "Awake at last after sleeping for " + s + " milliseconds!";
    }

    protected void onPostExecute(String result){
        textView.get().setText(result);
    }

    @Override
    protected void onProgressUpdate(Integer... values) {
        Log.d("ProgressUpdate",values[0].toString());
        progressBar.setProgress(values[0]);
        super.onProgressUpdate(values);

    }

}
