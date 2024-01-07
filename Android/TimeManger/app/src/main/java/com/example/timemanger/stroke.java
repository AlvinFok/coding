package com.example.timemanger;

public class stroke {
    private String name;
    private String start;
    private String end;
    private String type;
    private String comment;
    private int image;


    public stroke(String name, String start, String end, String type, String comment, int image){
        this.name = name;
        this.start = start;
        this.end = end;
        this.type = type;
        this.comment = comment;
        this.image = image;
    }

    public String getName(){return name;}
    public String getStart(){return start;}
    public String getType(){return type;}
    public String getComment(){return comment;}
    public int getImage(){return image;}
    public String getEnd(){return end;}
}
