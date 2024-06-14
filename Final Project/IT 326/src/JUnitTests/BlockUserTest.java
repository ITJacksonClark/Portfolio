// JUnit testing for the block user operation
// By Derek Kmieciak
// 5/5/24

package JUnitTests;


import org.junit.Before;
import org.junit.After;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

import java.io.File;
import java.io.IOException;



import Handlers.LNAccountHandler;
import Models.LNAccount;

public class BlockUserTest
{

    LNAccountHandler testHandler;
    File csvFile;
    String username = "abc123@email.com";
    String blockTestName = "blockThis@account.com";
    boolean result;
    LNAccount testUser;
    LNAccount blockedUser;

    @Before
    public void setUp() throws ClassNotFoundException, IOException
    {
        testHandler = new LNAccountHandler();
        csvFile = new File("accounts.csv");
        testHandler.createAccount(username, "123");
        testHandler.createAccount(blockTestName, "xyz");
    }

    @Test
    public void testingVerify() throws ClassNotFoundException, IOException
    {
        blockedUser = LNAccountHandler.getAcctOps().retrieveAcct(blockTestName); //ID of this account is needed
        result = testHandler.blockUser(username, blockedUser.getAcctID());
        assertEquals(true, result);
        //Successful run
    }

    @Test
    public void testingNullUser() throws ClassNotFoundException, IOException
    {
        //A user which doesn't exist can't block anything.
        //There should be no way for this to occur since the user must be logged in to access this use case,
        //but a check is provided as extra assurance. 
        blockedUser = LNAccountHandler.getAcctOps().retrieveAcct(blockTestName);
        result = testHandler.blockUser("Account with this name was never made", blockedUser.getAcctID());
        assertEquals(false, result);
    }

    @Test
    public void testingBlockingOwnAccount() throws ClassNotFoundException, IOException
    {
        blockedUser = LNAccountHandler.getAcctOps().retrieveAcct(username); //Attempting to block the user's own ID
        result = testHandler.blockUser(username, blockedUser.getAcctID());
        assertEquals(false, result);
    }

    @Test
    public void testingAttemptToBlockNonexistentID() throws ClassNotFoundException, IOException
    {
        //Since IDs are randomly assigned in a range 0-1000 we don't need an account to get an ID from for this test.
        //Any ID out of the generated range is guaranteed to not exist, so we'll use 5000. 
        result = testHandler.blockUser(username, 5000);
        assertEquals(false, result);
    }

    @Test
    public void testingAlreadyBlockedID() throws ClassNotFoundException, IOException
    {
        blockedUser = LNAccountHandler.getAcctOps().retrieveAcct(blockTestName);
        result = testHandler.blockUser(username, blockedUser.getAcctID()); //This should work - not blocked yet.
        assertEquals(true, result);
        //Now if the user attempts to block the same account again it will fail
        result = testHandler.blockUser(username, blockedUser.getAcctID());
        assertEquals(false, result);
    }


    @After
    public void cleanUp()
    {
        testHandler = null;
        testUser = null;
        blockedUser = null;
        csvFile.delete();
    }

}