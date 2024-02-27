package Alvin.Homwork;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;

/**
 * Unit test for simple App.
 */
public class AppTest {
    /**
     * Rigorous Test :-)
     */

    @Test
    public void binarySearchNormal() {
        assertEquals(-1, App.binarySearch(new int[] {}, 1));// no element not found

        assertEquals(0, App.binarySearch(new int[] { 1 }, 1));// one element found
        assertEquals(-1, App.binarySearch(new int[] { 2 }, 1));// one element not found

        assertEquals(0, App.binarySearch(new int[] { 1, 2 }, 1));// two(even) element found at first
        assertEquals(1, App.binarySearch(new int[] { 1, 2 }, 2));// two(even) element found at last
        assertEquals(-1, App.binarySearch(new int[] { 1, 2 }, 3));// two(even) element not found

        assertEquals(0, App.binarySearch(new int[] { 1, 2, 3 }, 1));// three(odd) element found at first
        assertEquals(1, App.binarySearch(new int[] { 1, 2, 3 }, 2));// three(odd) element found at mid
        assertEquals(2, App.binarySearch(new int[] { 1, 2, 3 }, 3));// three(odd) element found at last
        assertEquals(-1, App.binarySearch(new int[] { 1, 2, 3 }, 4));// three(odd) element not found
    }

    @Test
    public void nextDateNormal() {
        try {
            // test 1812(min)
            assertEquals("1812/01/02", App.nextDate("1812/01/01"));
            assertEquals("1812/01/11", App.nextDate("1812/01/10"));
            assertEquals("1812/02/01", App.nextDate("1812/01/31"));

            assertEquals("1812/05/01", App.nextDate("1812/04/30"));
            assertEquals("1812/05/02", App.nextDate("1812/05/01"));
            assertEquals("1812/06/01", App.nextDate("1812/05/31"));

            assertEquals("1812/12/02", App.nextDate("1812/12/01"));
            assertEquals("1812/12/11", App.nextDate("1812/12/10"));
            assertEquals("1813/01/01", App.nextDate("1812/12/31"));
            // test 1999(mid)
            assertEquals("1999/01/02", App.nextDate("1999/01/01"));
            assertEquals("1999/01/11", App.nextDate("1999/01/10"));
            assertEquals("1999/02/01", App.nextDate("1999/01/31"));

            assertEquals("1999/05/01", App.nextDate("1999/04/30"));
            assertEquals("1999/05/02", App.nextDate("1999/05/01"));
            assertEquals("1999/06/01", App.nextDate("1999/05/31"));

            assertEquals("1999/12/02", App.nextDate("1999/12/01"));
            assertEquals("1999/12/11", App.nextDate("1999/12/10"));
            assertEquals("2000/01/01", App.nextDate("1999/12/31"));
            // test 2012(max)
            assertEquals("2012/01/02", App.nextDate("2012/01/01"));
            assertEquals("2012/01/11", App.nextDate("2012/01/10"));
            assertEquals("2012/02/01", App.nextDate("2012/01/31"));

            assertEquals("2012/05/01", App.nextDate("2012/04/30"));
            assertEquals("2012/05/02", App.nextDate("2012/05/01"));
            assertEquals("2012/06/01", App.nextDate("2012/05/31"));

            assertEquals("2012/12/02", App.nextDate("2012/12/01"));
            assertEquals("2012/12/11", App.nextDate("2012/12/10"));
            assertEquals("2013/01/01", App.nextDate("2012/12/31"));
            // test leap year
            assertEquals("2000/02/29", App.nextDate("2000/02/28"));
            assertEquals("2000/03/01", App.nextDate("2000/02/29"));
            assertEquals("1900/03/01", App.nextDate("1900/02/28"));

        } catch (Exception e) {
            System.out.println(e.toString());
        }

    }

    @Test
    public void nextDateRangeTest() {
        // test year(min- , max+)
        assertThrows(Exception.class, () -> App.nextDate("1811/01/01"), "year must between 1812 - 2012");
        assertThrows(Exception.class, () -> App.nextDate("2013/01/01"), "year must between 1812 - 2012");
        // test month(min- , max+)
        assertThrows(Exception.class, () -> App.nextDate("1812/00/01"), "month must between 1 - 12");
        assertThrows(Exception.class, () -> App.nextDate("1812/13/01"), "month must between 1 - 12");
        // test day(min- , max+)
        assertThrows(Exception.class, () -> App.nextDate("1812/01/00"), "day must between 1 - 31");
        assertThrows(Exception.class, () -> App.nextDate("1812/01/32"), "day must between 1 - 31");
        // test wrong leap year
        assertThrows(Exception.class, () -> App.nextDate("1900/02/29"), "it does not have 29 days in 1900");
    }

}
