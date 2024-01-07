package app;

import java.util.Arrays;

public class App {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello Java");
    }

    public static String getTriangleType(int a, int b, int c) throws Exception {
        assert a > 0 && b > 0 && c > 0 : "one of the edge is negative or zero";
        int[] edges = new int[] { a, b, c };
        // sort the edges
        Arrays.sort(edges);
        // the sum of two shortest edges is little than the biggest edge cannot form a
        // triangle
        if (edges[0] + edges[1] <= edges[2]) {
            throw new Exception("this three edges cannot form a triangle");
        }
        if (edges[0] == edges[1] && edges[1] == edges[2]) { // check three edges is equal
            return "is equailateral triangle";
        }
        else if (edges[0] == edges[1] || edges[1] == edges[2]) { // check there are two edges is equal
            if (edges[0] * edges[0] + edges[1] * edges[1] == edges[2] * edges[2]) {
                return "is isosceles right triangle";
            }
            return "is isosceles triangle";
        }
        // check a square + b square == c square
        else if (edges[0] * edges[0] + edges[1] * edges[1] == edges[2] * edges[2]) {
            return "is right angle triangle";
        }
        else {
            return "is triangle";
        }
        
    }

}