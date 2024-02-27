package Alvin.Homwork;

/**
 * Hello world!
 *
 */
public class App {
    public static void main(String[] args) {
        System.out.println("Hello World!");
        try {
            nextDate("1900/02/28");
        } catch (Exception e) {
        }

    }

    public static int binarySearch(int[] array, int key) {
        int left = 0, right = array.length - 1;
        int mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (array[mid] == key) {// found the hey
                return mid;
            } else if (array[mid] < key) {// key is bigger than array[mid], search right side
                left = mid + 1;
            } else {// key is smaller than array[mid], search left side
                right = mid - 1;
            }
        }
        // not found
        return -1;
    }

    public static String nextDate(String date) throws Exception {
        // YYYY/MM/DD
        String[] tokens = date.split("/");
        int year = Integer.valueOf(tokens[0]), month = Integer.valueOf(tokens[1]), day = Integer.valueOf(tokens[2]);
        if (year < 1812 || year > 2012) {
            throw new Exception("year must between 1812 - 2012");
        }
        if (month < 1 || month > 12) {
            throw new Exception("month must between 1 - 12");
        }
        if (day < 1 || day > 31) {
            throw new Exception("day must between 1 - 31");
        }
        if (month == 2) {
            boolean isLeapyear = false;
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
                isLeapyear = true;
            }
            if (day == 29 && isLeapyear == false) {
                throw new Exception(String.format("it does not have 29 days in %d", year));
            }
            if ((day == 29 && isLeapyear == true) || (day == 28 && isLeapyear == false)) {
                day = 1;
                month += 1;
            } else {
                day += 1;
            }
        } else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
            if (day == 31) {
                day = 1;
                month += 1;
            } else {
                day += 1;
            }
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day == 30) {
                day = 1;
                month += 1;
            } else {
                day += 1;
            }
        }
        if (month > 12) {
            month = 1;
            year += 1;
        }
        return String.format("%d/%02d/%02d", year, month, day);
    }
}
