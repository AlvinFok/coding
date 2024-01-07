import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.*;
import org.mockito.junit.jupiter.MockitoExtension;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)

class StrangeGameTest {
    StrangeGame strangeGame;

    @Mock
    Hour hour;

    @Mock
    Prison prison;

    @BeforeEach
    public void beforeEach(){
        strangeGame = new StrangeGame();
        hour = mock(Hour.class);
        prison = mock(Prison.class);
    }

    @Test
    public void test_a(){
        Player player = new Player();
        strangeGame.hour = hour;//mock
        when(hour.getHour()).thenReturn(3);
        try {
            strangeGame.enterGame((player));
            verify(prison, never()).imprisonment(player);
        }
        catch (InterruptedException e){
            assert(false);//imprisonment should never run
        }
    }

    @Test
    public void test_b() {
        Player player = new Player();
        prison = spy(prison);
        strangeGame.hour = hour;//mock
        strangeGame.setPrison(prison);//mock
        when(hour.getHour()).thenReturn(12);
        try{
            doNothing().when(prison).imprisonment(any(Player.class));
            assertEquals("After a long period of punishment, the player can leave! :)", strangeGame.enterGame(player) );
        }
        catch (Exception e){
            System.out.println("test" + e);
        }

    }

    @Test
    public void test_c() throws InterruptedException{
        Player[] players = new Player[3];
        prison = spy(new Prison());
        strangeGame.hour = hour;//mock
        strangeGame.prison = prison;//mock
        when(hour.getHour()).thenReturn(12);
        doNothing().when(prison).imprisonment(any(Player.class));
        StrangeGame spy = spy(strangeGame);
        for(int i = 0; i < 3; i ++){
            players[i] = new Player();
            spy.enterGame(players[i]);
        }
        for(int i = 0; i < 3; i ++){
            verify(spy).enterGame(players[i]);
        }

    }

    @Test
    public void test_d(){
        GAMEDb db = mock(GAMEDb.class);
        strangeGame.db = db;
        when(db.getScore("310551006")).thenReturn(100);
        assertEquals(100, strangeGame.getScore("310551006"));
    }

    @Test
    public void test_e(){
        class MyPaypal implements paypalService{
            @Override
            public String doDonate() {
                return "Success";
            }
        }
        MyPaypal myPaypal = new MyPaypal();
        assertEquals("Thank you", strangeGame.donate(myPaypal));
    }

}