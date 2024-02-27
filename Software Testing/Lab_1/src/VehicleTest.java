import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class VehicleTest {

    private Vehicle vehicle;
    @BeforeEach
    void setUp() {
        vehicle = new Vehicle();
    }

    @AfterEach
    void tearDown() {
        vehicle.finalize();
    }

    @Test
    void testFinalize() {
    }

    @Test
    void setSpeed() {
        vehicle.setSpeed(1);
        assertEquals(1, vehicle.getSpeed());
    }

    @Test
    void setDir() {
        vehicle.setDir("west");
        assertEquals("west", vehicle.getDir());
    }

    @Test
    void getSpeed() {
        assertEquals(0, vehicle.getSpeed());
    }

    @Test
    void getDir() {
        assertEquals("north", vehicle.getDir());
    }

    @Test
    void totalVehicle() {
        assertEquals(1, Vehicle.totalVehicle());
        Vehicle vehicle1 = new Vehicle();
        assertEquals(2, Vehicle.totalVehicle());
    }
}