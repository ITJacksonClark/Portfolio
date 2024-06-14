// JUnit testing for the login operation
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

public class LoginTest{
    private LNAccountHandler acctHandler;
    private File csvFile;

    @Before
    public void setUp() throws FileNotFoundException{
        acctHandler = new LNAccountHandler();
        csvFile = new File("accounts.csv");
    }

    /*
     * Basis Path Testing - Part 1 (39->50)
     */
    @Test
    public void testingVerifyString() throws IOException, ClassNotFoundException{
        String username = null;
        String password = null;
        acctHandler.createAccount("jacksonclarkit@gmail.com", "j@ckson149");
        boolean expected = false;
        boolean actual = acctHandler.login(username, password);
        assertEquals(expected, actual);
    }

    /*
     * Basis Path Testing - Part 2 (39->41->42->50)
     */
    @Test
    public void testingNoAccountFoundInAccountsCSV() throws IOException, ClassNotFoundException{
        String username = "jwclar1@ilstu.edu";
        String password = "j@ckson149";
        acctHandler.createAccount("jacksonclarkit@gmail.com", password);
        boolean expected = false;
        boolean actual = acctHandler.login(username, password);
        assertEquals(expected, actual);
    }

    /*
     * Basis Path Testing - Part 3 (39->41->42->44->50)
     */
    @Test
    public void testingPasswordDoesntMatchAccount() throws IOException, ClassNotFoundException{
        String username = "jwclar1@ilstu.edu";
        String password = "j@ckson149";
        acctHandler.createAccount(username, "j@ckson139");
        boolean expected = false;
        boolean actual = acctHandler.login(username, password);
        assertEquals(expected, actual);
    }

    /*
     * Basis Path Testing - Part 4 (39->41->42->44->46)
     */
    @Test
    public void testingUsernameAndPasswordMatch() throws IOException, ClassNotFoundException{
        String username = "jwclar1@ilstu.edu";
        String password = "j@ckson149";
        acctHandler.createAccount(username, password);
        boolean expected = true;
        boolean actual = acctHandler.login(username, password);
        assertEquals(expected, actual);
    }

    @After
    public void cleanUp(){
        acctHandler = null;
        csvFile.delete(); //Clears the file after use
    }

}
