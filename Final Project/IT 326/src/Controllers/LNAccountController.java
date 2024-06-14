// Controller for the Account class
// By Jackson Clark & Derek Kmieciak
// 5/5/24

package Controllers;

import Handlers.LNAccountHandler;
import Models.LNAccount;
import java.io.IOException;

public class LNAccountController
{
    private static LNAccountHandler acctHandler = null;

    private static LNAccountHandler getLNAccountHandlerInstance()
    { // Gets the account handler object
        if (acctHandler == null)
            acctHandler = new LNAccountHandler();
        return acctHandler;
    }

    // Calls login implementation from account handler
    public static boolean login(String username, String password) throws IOException, ClassNotFoundException
    {
        return getLNAccountHandlerInstance().login(username, password);
    }

    // Calls create account implementation from account handler
    public static boolean createAccount(String username, String password) throws IOException, ClassNotFoundException
    {
        return getLNAccountHandlerInstance().createAccount(username, password);
    }

    public static boolean updateAccount(String username, String password, String curUsername, String curPassword)
            throws IOException, ClassNotFoundException
    {
        return getLNAccountHandlerInstance().updateAccount(username, password, curUsername, curPassword);
    }

    public static boolean deleteAccount(String username, String password) throws IOException, ClassNotFoundException
    {
        return getLNAccountHandlerInstance().deleteAccount(username, password);
    }

    public static boolean loggout() // Calls loggout implementation from account handler
    {
        return getLNAccountHandlerInstance().loggout();
    }

    public static int printBlockedUsers(String currentUser) throws ClassNotFoundException, IOException
    {
        return acctHandler.printBlockedUsers(currentUser);
    }

    public static void printNamesAndIDs() throws ClassNotFoundException, IOException
    {
        acctHandler.printNamesAndIDs();
    }

    public static boolean blockUser(String currentUser, int id) throws ClassNotFoundException, IOException
    {
        return acctHandler.blockUser(currentUser, id);
    }

    public static boolean unblockUser(String currentUser, int id) throws ClassNotFoundException, IOException
    {
        return acctHandler.unblockUser(currentUser, id);
    }

    public static int printComments(String currentUser) throws ClassNotFoundException, IOException
    {
        return acctHandler.printComments(currentUser);
    }

    public static boolean pinComment(String currentUser, int selected) throws ClassNotFoundException, IOException
    {
        return acctHandler.pinComment(currentUser, selected);
    }

    public static boolean removeComment(String currentUser, int removed) throws ClassNotFoundException, IOException
    {
        return acctHandler.removeComment(currentUser, removed);
    }

    public static boolean editComment(String currentUser, int selected, String newText)
            throws ClassNotFoundException, IOException
    {
        return acctHandler.editComment(currentUser, selected, newText);
    }

    public static int searchComments(String keyword, String username) throws ClassNotFoundException, IOException
    {
        return acctHandler.searchComments(keyword, username);
    }

    // calls the getNotifCount implementation from account handler -Nathan
    public static int getNotifCount(String username) throws IOException, ClassNotFoundException
    {
        return getLNAccountHandlerInstance().getNotifCount(username);
    }

    public static boolean disableNotifs(String username) throws IOException, ClassNotFoundException
    {
        return getLNAccountHandlerInstance().disableNotifs(username);
    }

    public static boolean clearNotifs(String username) throws IOException, ClassNotFoundException
    {
        return getLNAccountHandlerInstance().clearNotifs(username);
    }

    public static int printNotif(String username) throws ClassNotFoundException, IOException
    {
        return getLNAccountHandlerInstance().printNotif(username);
    }

    public static LNAccount searchForAccount(String username) throws IOException, ClassNotFoundException
    {
        return getLNAccountHandlerInstance().searchForAccount(username);
    }
}
