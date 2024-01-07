package lab;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner keyboard = new Scanner(System.in);
		double angle = keyboard.nextDouble();
		keyboard.close();
		double radian = angleToRadian(angle);
		System.out.println("Java sin:");
		System.out.println(Math.sin(radian));
		System.out.println("My sin:");
		System.out.println(sin(radian));

	}

	public static double angleToRadian(double angle) {
		double pi = 3.14159;
		double radian = angle * pi / 180;
		return radian;
	}

	public static double sin(double x) {
		double vlaue = 0;
		int sign = 1;
		int factorial = 1;
		double java_sin = Math.sin(x);
		for (; Math.abs(vlaue - java_sin) > 0.0000000001; factorial += 2) {
			vlaue += sign * power(x, factorial) / fact(factorial);
			sign *= -1;
		}
		return vlaue;
	}

	public static int fact(int n) {
		if (n == 1) {
			return 1;
		}
		return n * fact(n - 1);
	}

	public static double power(double num, int n) {
		if (n == 1) {
			return num;
		}
		return num * power(num, n - 1);
	}
}
