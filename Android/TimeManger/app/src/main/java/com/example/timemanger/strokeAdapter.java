package com.example.timemanger;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.lang.reflect.Member;
import java.util.List;

class strokeAdapter extends RecyclerView.Adapter<strokeAdapter.ViewHolder> {

    private Context context;
    private List<stroke> strokeList;
    private String time;

    strokeAdapter(Context context, List<stroke> strokeList){
        this.context = context;
        this.strokeList = strokeList;
    }

    @Override
    public strokeAdapter.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        return new ViewHolder(LayoutInflater.from(context).inflate(R.layout.card, parent, false));
    }

    @Override
    public void onBindViewHolder(strokeAdapter.ViewHolder holder, int position) {
        final stroke s = strokeList.get(position);
        time = s.getEnd();
        if(!time.equals(""))
            holder.timeView.setText(s.getStart() + "~" + time);
        holder.strokeView.setText(s.getName());
        holder.noteView.setText(s.getComment());
        holder.imageView.setImageResource(s.getImage());
        //Glide.with(context).load(s.getImage()).into(holder.imageView);
        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast toast = Toast.makeText(context, "aaa", Toast.LENGTH_SHORT);
                toast.setDuration(Toast.LENGTH_SHORT);
                toast.show();
            }
        });
    }

    @Override
    public int getItemCount() {
        return strokeList.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder{
        TextView timeView, strokeView, noteView;
        ImageView imageView;
        ViewHolder(View itemView){
            super(itemView);
            timeView = (TextView) itemView.findViewById(R.id.timeView);
            strokeView = (TextView) itemView.findViewById(R.id.strokeView);
            noteView = (TextView) itemView.findViewById(R.id.noteView);
            imageView = (ImageView) itemView.findViewById(R.id.imageView);
        }
    }
}
