// JUnit testing for the move file operation
// By Joseph Vlastnik
// 5/5/24

package JUnitTests;

import static org.junit.Assert.assertEquals;

import java.io.File;
import java.io.IOException;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import Handlers.LNFileHandler;
import Models.LNFile;

public class MoveFileTest {
    LNFileHandler testHandle;
    File csvFile;
    
    @Before
    public void setUp() throws ClassNotFoundException, IOException{
        testHandle = new LNFileHandler();
        csvFile = new File("files.csv");
        testHandle.uploadFile("fish", 0, "jack");
        testHandle.uploadFile("fish", 1, "jack");
        testHandle.uploadFile("berries", 0, "jack");
        testHandle.uploadFile("fish", 2, "paul");
    }
    @Test
    public void testNullMove() throws ClassNotFoundException, IOException{
        boolean expected = false;
        boolean result = testHandle.moveFile(null, 0, null);
        assertEquals(expected, result);
    }
    @Test
    public void testBlockedMove() throws ClassNotFoundException, IOException{
        LNFile toMove = testHandle.getFileFromID(testHandle.getFileID("fish", 0, "jack"));
        boolean expected = false;
        boolean result = testHandle.moveFile(toMove, 1, "jack");
        assertEquals(expected, result);
    }
    @Test
    public void testNotBlockedMoveOne() throws ClassNotFoundException, IOException{
        LNFile toMove = testHandle.getFileFromID(testHandle.getFileID("berries", 0, "jack"));
        boolean expected = true;
        boolean result = testHandle.moveFile(toMove, 1, "jack");
        assertEquals(expected, result);
    }
    @Test
    public void testNotBlockedMoveTwo() throws ClassNotFoundException, IOException{
        LNFile toMove = testHandle.getFileFromID(testHandle.getFileID("fish", 0, "jack"));
        boolean expected = true;
        boolean result = testHandle.moveFile(toMove, 2, "jack");
        assertEquals(expected, result);
    }
    @After
    public void cleanUp(){
        testHandle = null;
        csvFile.delete(); //Clears the file after use
    }
}
