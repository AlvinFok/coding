package com.example.timemanger;

import org.junit.Before;
import org.junit.Test;

import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.CoreMatchers.is;
import static org.junit.Assert.*;
import static org.junit.Assert.assertThat;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    private stroke s;

    @Before
    public void setUp(){s = new stroke("打工", "12:00", "15:00", "工作", "很累", 1);}

    @Test
    public void name(){
        String ans = s.getName();
        assertThat(ans, is(equalTo("打工")));
    }

    @Test
    public void start(){
        String ans = s.getStart();
        assertThat(ans, is(equalTo("12:00")));
    }

    @Test
    public void end(){
        String ans = s.getEnd();
        assertThat(ans, is(equalTo("15:00")));
    }

    @Test
    public void type(){
        String ans = s.getType();
        assertThat(ans, is(equalTo("工作")));
    }

    @Test
    public void comment(){
        String ans = s.getComment();
        assertThat(ans, is(equalTo("很累")));
    }

    @Test
    public void image(){
        double ans = s.getImage();
        assertThat(ans, is(equalTo(1d)));
    }
}