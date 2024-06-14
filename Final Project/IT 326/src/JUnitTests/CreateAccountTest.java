// JUnit testing for the create account operation
// By Jackson Clark
// 5/5/24

package JUnitTests;

import static org.junit.Assert.assertEquals;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import Handlers.LNAccountHandler;

public class CreateAccountTest {

    private LNAccountHandler acctHandler;
    private File csvFile;

    @Before
    public void setUp() throws FileNotFoundException{
        acctHandler = new LNAccountHandler();
        csvFile = new File("accounts.csv");
    }

    /*
     * Basis Path Testing - Part 1 (55->63)
     */
    @Test
    public void testingVerifyString() throws IOException, ClassNotFoundException{
        String username = null;
        String password = null;
        boolean expected = false;
        boolean actual = acctHandler.createAccount(username, password);
        assertEquals(expected, actual);
    }

    /*
     * Basis Path Testing - Part 2 (55->57->61->63)
     */
    @Test
    public void testingRegexPatternDoesntMatch() throws IOException, ClassNotFoundException{
        String username = "jwclar1";
        String password = "j@ckson149";
        boolean expected = false;
        boolean actual = acctHandler.createAccount(username, password);
        assertEquals(expected, actual);
    }

    /*
     * Basis Path Testing - Part 3 (55->57->59)
     */
    @Test
    public void testingRegexPatternDoesMatch() throws IOException, ClassNotFoundException{
        String username = "jwclar1@ilstu.edu";
        String password = "j@ckson149";
        boolean expected = true;
        boolean actual = acctHandler.createAccount(username, password);
        assertEquals(expected, actual);
    }

    @After
    public void cleanUp(){
        acctHandler = null;
        csvFile.delete(); //Clears the file after use
    }
}
