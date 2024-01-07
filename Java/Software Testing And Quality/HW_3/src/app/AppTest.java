package app;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class AppTest {
    App app = new App();

    // @BeforeAll
    // void beforeAll() {
    //     System.out.println(">>>>>>>>>>>>>>>>>>>>>>>.");
    // }

    // @AfterAll
    // void afterAll() {
    //     System.out.println("<<<<<<<<<<<<<<<<<<<<");
    // }

    // @BeforeEach
    // void before() {
    //     System.out.println("Test started.");
    // }

    // @AfterEach
    // void after() {
    //     System.out.println("Test finished.");
    // }

    @Test
    void getTriangleTypeTest() {
        try {
            assertEquals("is triangle", App.getTriangleType(2, 3, 4));
            // assertEquals("is equailateral triangle", App.getTriangleType(3, 3, 3));
            // assertEquals("is isosceles triangle", App.getTriangleType(2, 2, 1));
            // assertEquals("is right angle triangle", App.getTriangleType(3, 4, 5));
            // assertEquals("is triangle", App.getTriangleType(3, 5, 6));
            // assertThrows(Exception.class, ()->App.getTriangleType(1, 2, 3));
        } catch (Exception e) {
            e.printStackTrace();
        }
        // assertEquals(true,true);
        
    }
    
}