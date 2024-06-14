// The Account class
// By Jackson Clark & Derek Kmieciak
// 5/5/24

package Models;

import CRUDOps.LNAccountCRUDOps;
import Operations.LNAccountOperations;
import java.io.IOException;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Random;

public class LNAccount implements Serializable
{
    private int accountID; // Account's ID
    private String accountEmail; // Account's email
    private String accountPassword; // Account's password
    private boolean enableNotifs; // Account's prefence towards receving notifications
    private ArrayList<LNFile> ownedFiles; // Account's list of files
    private ArrayList<LNFolder> ownedFolders; // Account's list of folders
    private ArrayList<LNNotification> notifications; // Account's list of notifications
    private ArrayList<LNComment> comments; // Account's list of comments
    private ArrayList<LNComment> pinned; // Account's list of pinned comments
    private ArrayList<Integer> blockedUserIDs; // Account's blocked list of users with their ID's specifying them

    public LNAccount(String accountEmail, String accountPassword) throws IOException, ClassNotFoundException
    {
        // Creating account ID/checking to see if the same ID already exists starting
        // here
        Random rand = new Random();
        this.accountID = -1;
        boolean alreadyID = true;
        while (alreadyID == true)
        {
            alreadyID = false;
            this.accountID = rand.nextInt(1000);
            if (getAcctOps().readFromAccountCSV() != null)
            {
                for (int i = 0; i < getAcctOps().readFromAccountCSV().size(); i++)
                {
                    if (this.accountID == getAcctOps().readFromAccountCSV().get(i).getAcctID())
                    {
                        alreadyID = true;
                    }
                }
            }
        }
        // Creating account ID/checking to see if the same ID already exists ending here
        this.accountEmail = accountEmail;
        this.accountPassword = accountPassword;
        this.ownedFiles = new ArrayList<>();
        this.ownedFolders = new ArrayList<>();
        this.notifications = new ArrayList<>();
        this.comments = new ArrayList<>();
        this.pinned = new ArrayList<>();
        this.blockedUserIDs = new ArrayList<>();
        this.enableNotifs = true;
    }

    public static LNAccountCRUDOps getAcctOps() // Gets CRUD operations
    {
        return LNAccountOperations.getLNAccountOperationsInstance();
    }

    public int getAcctID() // Gets the account's ID
    {
        return accountID;
    }

    public String getEmail() // Gets the account's email
    {
        return accountEmail;
    }

    public String setEmail(String username) // Sets the account's email
    {
        accountEmail = username;
        return accountEmail;
    }

    public String getPassword() // Gets the account's password
    {
        return accountPassword;
    }

    public String setPassword(String password) // Sets the account's password
    {
        accountPassword = password;
        return accountPassword;
    }

    public ArrayList<LNFile> getFiles() // Gets the account's list of files
    {
        return ownedFiles;
    }

    public void setFiles(ArrayList<LNFile> files)
    {
        this.ownedFiles = files;
    }

    public ArrayList<LNFolder> getFolders() // Gets the account's list of folders
    {
        return ownedFolders;
    }

    public void setFolders(ArrayList<LNFolder> folders)
    {
        this.ownedFolders = folders;
    }

    public ArrayList<LNNotification> getNotifs() // Gets the account's list of notifications
    {
        return notifications;
    }

    public void setNotifications(ArrayList<LNNotification> notifs)
    {
        this.notifications = notifs;
    }

    public ArrayList<LNComment> getComments() // Gets the account's list of comments
    {
        return comments;
    }

    public void setComments(ArrayList<LNComment> cmts)
    {
        this.comments = cmts;
    }

    public ArrayList<LNComment> getPinned()
    {
        return pinned;
    }

    public void setPinned(ArrayList<LNComment> pinned)
    {
        this.pinned = pinned;
    }

    public ArrayList<Integer> getBlockedUsers() // Gets the account's list of blocked users
    {
        return blockedUserIDs;
    }

    public void setBlockedUsers(ArrayList<Integer> ids)
    {
        this.blockedUserIDs = ids;
    }

    public boolean getEnableNotifs()
    { // gets the accounts notification setting
        return enableNotifs;
    }

    public boolean disableNotifs()// changes enableNotifs to false
    {
        this.enableNotifs = false;
        return true;
    }

    public boolean saveAccount() throws IOException, ClassNotFoundException
    {
        return getAcctOps().saveAcct(this);
    }

}
