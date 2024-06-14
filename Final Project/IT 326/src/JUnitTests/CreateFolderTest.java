// JUnit testing for the create folder operation
// By Matthew Cox
// 5/5/24

package JUnitTests;

import static org.junit.Assert.assertEquals;

import java.io.File;
import java.io.IOException;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import Controllers.*;
import Models.*;

public class CreateFolderTest 
{
    private File csvFile;
    private boolean Result;

    @Before
    public void setUp() throws ClassNotFoundException, IOException
    {
        csvFile = new File("test.csv");
        LNAccountController.createAccount("matthewc0813@gmail.com","Password123");
    }

    @Test
    public void testCreateValidFolder() throws IOException, ClassNotFoundException //Test to see if a folder got created with the correct name and owner
    {
        LNAccount testAcct = LNAccountController.searchForAccount("matthewc0813@gmail.com");
        LNFolderController.createFolder("test", testAcct);
        LNFolder testFolder = testAcct.getFolders().get(0);
        String folderName = testFolder.getName();
        String acctName = testFolder.getOwner().getEmail();
        testAcct.saveAccount();
        assertEquals("test", folderName);
        assertEquals("matthewc0813@gmail.com", acctName);
    }
}