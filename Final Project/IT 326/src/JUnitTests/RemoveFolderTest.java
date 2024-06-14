// JUnit testing for the remove folder operation
// By Matthew Cox
// 5/5/24

package JUnitTests;

import static org.junit.Assert.assertEquals;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import Controllers.*;
import Models.*;

public class RemoveFolderTest 
{
    private File csvFile;
    private boolean Result;

    @Before
    public void setUp() throws FileNotFoundException, IOException, ClassNotFoundException
    {
        csvFile = new File("test.csv");
        LNAccountController.createAccount("matthewc0813@gmail.com","Password123");
    }

    @Test
    public void testDeFolderRightID() throws ClassNotFoundException, IOException //Test to see if a folder got removed with the correct ID
    {
        LNAccount testAcct = LNAccountController.searchForAccount("matthewc0813@gmail.com");
        LNFolderController.createFolder("test", testAcct);
        LNFolder testFolder = testAcct.getFolders().get(0);
        testAcct.saveAccount();
        int testFolID = testFolder.getFolderID();
        Result = LNFolderController.removeFolder(testFolID, testAcct);
        assertEquals(true, Result);
    }

    @Test
    public void testDeFolderWrongID() throws ClassNotFoundException, IOException //Test to see if a folder got removed with the wrong ID
    {
        LNAccount testAcct = LNAccountController.searchForAccount("matthewc0813@gmail.com");
        LNFolderController.createFolder("test", testAcct);
        LNFolder testFolder = testAcct.getFolders().get(0);
        testAcct.saveAccount();
        int testFolID = testFolder.getFolderID();
        Result = LNFolderController.removeFolder(testFolID/2, testAcct);
        assertEquals(false, Result);
    }
}