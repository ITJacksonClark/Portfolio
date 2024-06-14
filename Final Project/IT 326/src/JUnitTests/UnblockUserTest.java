// JUnit testing for the unblock user operation
// By Derek Kmieciak
// 5/5/24

package JUnitTests;

import static org.junit.Assert.assertEquals;

import java.io.File;
import java.io.IOException;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import Handlers.LNAccountHandler;
import Models.LNAccount;

public class UnblockUserTest
{
    LNAccountHandler testHandler;
    File csvFile;
    String username = "xyz456@email.com";
    String unblockTestName = "unblockThis@account.com";
    boolean result;
    LNAccount testUser;
    LNAccount unblockedUser;

    @Before
    public void setUp() throws ClassNotFoundException, IOException
    {
        testHandler = new LNAccountHandler();
        csvFile = new File("accounts.csv");
        testHandler.createAccount(username, "123");
        testHandler.createAccount(unblockTestName, "xyz");

        unblockedUser = LNAccountHandler.getAcctOps().retrieveAcct(unblockTestName); //Block this user
        testHandler.blockUser(username, unblockedUser.getAcctID());
    }

    @Test
    public void testingVerify() throws ClassNotFoundException, IOException
    {
        result = testHandler.unblockUser(username, unblockedUser.getAcctID());
        assertEquals(true, result);
        //Successful run
    }

    @Test
    public void testingNullUser() throws ClassNotFoundException, IOException
    {
        //A user which doesn't exist can't unblock anything.
        //There should be no way for this to occur since the user must be logged in to access this use case,
        //but a check is provided as extra assurance. 
        result = testHandler.unblockUser("This account was never created", unblockedUser.getAcctID());
        assertEquals(false, result);
    }

    @Test
    public void testingAttemptToUnblockNonBlockedID() throws ClassNotFoundException, IOException
    {
        result = testHandler.unblockUser(username, 5000);
        assertEquals(false, result);
    }

    @After
    public void cleanUp()
    {
        testHandler = null;
        testUser = null;
        unblockedUser = null;
        csvFile.delete();
    }
}