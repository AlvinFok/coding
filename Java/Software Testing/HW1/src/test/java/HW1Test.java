package test.java;


import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;
public class HW1Test {

    public int findLast (int[] x, int y)
    {
        for (int i=x.length-1; i >= 0; i--)
        {
            if (x[i] == y)
            {
                return i;
            }
        }
        return -1;
    }

    public static int lastZero (int[] x)
    {
        for (int i=x.length-1; i >= 0; i--)
        {
            if (x[i] == 0)
            {
                return i;
            }
        }
        return -1;
    }

    public int countPositive (int[] x)
    {
        int count = 0;
        for (int i=0; i < x.length; i++)
        {
            if (x[i] > 0)
            {
                count++;
            }
        }
        return count;
    }

    public static int oddOrPos(int[] x)
    {
        int count = 0;
        for (int i = 0; i < x.length; i++)
        {
            if (Math.abs(x[i])%2 == 1 || x[i] > 0)
            {
                count++;
            }
        }
        return count;
    }



    @Test
    public void findLast (){
        int[] x = new int[]{2, 3, 5};
        int y = 2;
        assertEquals(0, findLast(x, y));

    }

    @Test
    public void lastZero (){
        int[] x = new int[]{0, 1, 0};
        int y = 2;
        assertEquals(2, lastZero(x));

    }

    @Test
    public void countPositive (){
        int[] x = new int[]{-4, 2, 0, 2};
        int y = 2;
        assertEquals(2, countPositive(x));

    }

    @Test
    public void oddOrPos (){
        int[] x = new int[]{-3, -2, 0, 1, 4};
        int y = 2;
        assertEquals(3, oddOrPos(x));

    }
}
