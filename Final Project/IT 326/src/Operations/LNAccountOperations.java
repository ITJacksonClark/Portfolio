// Operations for the Account class
// By Jackson Clark & Derek Kmieciak
// 5/5/24

package Operations;

import CRUDOps.LNAccountCRUDOps;
import Models.LNAccount;
import Models.LNComment;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

public class LNAccountOperations extends LNAccountCRUDOps
{

    private static LNAccountCRUDOps acctOps = null;

    public static LNAccountCRUDOps getLNAccountOperationsInstance()
    { // Gets the abstract account CRUDOps object
        if (acctOps == null)
            acctOps = new LNAccountOperations();
        return acctOps;
    }

    // Reads in the accounts.csv file into an array list of account objects
    public ArrayList<LNAccount> readFromAccountCSV() throws IOException, ClassNotFoundException
    {
        File output = new File("accounts.csv");
        output.createNewFile(); // Create file if it doesn't exist -- prevent crashes
        try (FileInputStream fis = new FileInputStream("accounts.csv");
                ObjectInputStream ois = new ObjectInputStream(fis))
        {
            return (ArrayList<LNAccount>) ois.readObject();
        }
        catch (EOFException exc)
        {
            return null;
        }
    }

    // Writes into the accounts.csv file and reutrns a boolean based on if it worked
    // or not
    public boolean writeToAccountCSV(ArrayList<LNAccount> accts) throws IOException, ClassNotFoundException
    {
        File csvFile = new File("accounts.csv");
        csvFile.createNewFile();
        // Does nothing if it exists-- prevents FileNotFound exceptions if it can't find
        // the file

        try (FileOutputStream fos = new FileOutputStream(csvFile); ObjectOutputStream oos = new ObjectOutputStream(fos))
        {
            oos.writeObject(accts);
            oos.flush();
            return true;
        }
        catch (Exception e)
        {
            return false;
        }
    }

    // Reads in the accounts from the accounts.csv file and adds the new account to
    // the array list of accounts just read and finally writes
    // the new array list with the new account to the accounts.csv file
    public boolean saveAcct(LNAccount acct) throws IOException, ClassNotFoundException
    {
        ArrayList<LNAccount> accts = readFromAccountCSV();
        if (accts == null)
        {
            accts = new ArrayList<>(); 
        }

        if (retrieveAcct(acct.getEmail()) == null)
        {
            accts.add(acct);
        }
        else
        {
            //Logic for updating the account's contents and differing between newly created accounts with the same name
            if(acct.getAcctID() == retrieveAcct(acct.getEmail()).getAcctID())
            {
                deleteAccount(acct.getEmail(), acct.getPassword());
                accts = readFromAccountCSV();
                accts.add(acct);
                if (writeToAccountCSV(accts) != false)
                {
                    return true;
                }
                return false;
            }
            else
            {
                System.out.print("Error: Account has already been made.");
                return false;
            }
        }

        if (writeToAccountCSV(accts) != false)
        {
            return true;
        }
        return false;
    }

    // Reads in the accounts from the accounts.csv file and searches for the account
    // based on email alone
    public LNAccount retrieveAcct(String username) throws IOException, ClassNotFoundException
    {
        ArrayList<LNAccount> acctArr = readFromAccountCSV();
        if (acctArr != null)
        {
            for (int i = 0; i < acctArr.size(); i++)
            {
                if (acctArr.get(i).getEmail().toLowerCase().equals(username.toLowerCase()))
                {
                    return acctArr.get(i);
                }
            }
        }
        return null;
    }

    // Reads in the accounts from the accounts.csv file and removes the specified
    // account from the array list of accounts just read and finally writes
    // the new array list with the account specified removed to the accounts.csv
    // file
    public boolean deleteAccount(String username, String password) throws IOException, ClassNotFoundException
    {
        ArrayList<LNAccount> acctArr = readFromAccountCSV();
        if (acctArr != null)
        {
            for (int i = 0; i < acctArr.size(); i++)
            {
                if (acctArr.get(i).getEmail().toLowerCase().equals(username.toLowerCase())
                        && acctArr.get(i).getPassword().equals(password))
                {
                    acctArr.remove(i);
                    writeToAccountCSV(acctArr);
                    return true;
                }
            }
        }
        return false;
    }

    // Reads in the accounts from the accounts.csv file and updates the username and
    // password of the specified account
    // in the array list of accounts just read in and finally writes the new array
    // list with the updated account to the accounts.csv file
    public boolean updateAccount(String username, String password, String curUsername, String curPassword)
            throws IOException, ClassNotFoundException
    {
        ArrayList<LNAccount> acctArr = readFromAccountCSV();
        if (acctArr != null)
        {
            for (int i = 0; i < acctArr.size(); i++)
            {
                if (acctArr.get(i).getEmail().toLowerCase().equals(curUsername.toLowerCase())
                        && acctArr.get(i).getPassword().equals(curPassword))
                {
                    acctArr.get(i).setEmail(username);
                    acctArr.get(i).setPassword(password);
                    writeToAccountCSV(acctArr);
                    return true;
                }
            }
        }
        return false;
    }

    // Finds the account belonging to user name and returns the count of
    // notification in that account - Nathan
    public int getNotifCount(String username) throws ClassNotFoundException, IOException
    {
        ArrayList<LNAccount> acctArr = readFromAccountCSV();
        if (acctArr != null)
        {
            for (int i = 0; i < acctArr.size(); i++)
            {
                if (acctArr.get(i).getEmail().toLowerCase().equals(username.toLowerCase()))
                {
                    return acctArr.get(i).getNotifs().size();
                }
            }
        }
        return 0;
    }

    // Finds account belonging to username and calls disableNotifs on it - Nathan
    public boolean disableNotifs(String username) throws ClassNotFoundException, IOException
    {
        ArrayList<LNAccount> acctArr = readFromAccountCSV();
        if (acctArr != null)
        {
            for (int i = 0; i < acctArr.size(); i++)
            {
                if (acctArr.get(i).getEmail().toLowerCase().equals(username.toLowerCase()))
                {
                    return acctArr.get(i).disableNotifs();
                }
            }
        }
        return false;
    }

    // Clears all of the account's notifications
    public boolean clearNotifs(String username) throws ClassNotFoundException, IOException
    {
        ArrayList<LNAccount> acctArr = readFromAccountCSV();
        if (acctArr != null)
        {
            for (int i = 0; i < acctArr.size(); i++)
            {
                if (acctArr.get(i).getEmail().toLowerCase().equals(username.toLowerCase()))// Finds the desired account
                {
                    for (int j = 0; j < acctArr.get(i).getNotifs().size(); j++)// loops through all notifications
                    {
                        acctArr.get(i).getNotifs().get(j).markNotifiactionAsRead();
                        acctArr.get(i).getNotifs().get(j).detectActivity();
                    }
                }
            }
        }
        return false;
    }

    public boolean updateAccountBlocked(ArrayList<Integer> newBlacklist, String curUsername)
            throws ClassNotFoundException, IOException
    {
        ArrayList<LNAccount> acctArr = readFromAccountCSV();
        if (acctArr != null)
        {
            for (int i = 0; i < acctArr.size(); i++)
            {
                if (acctArr.get(i).getEmail().toLowerCase().equals(curUsername.toLowerCase()))
                {
                    acctArr.get(i).setBlockedUsers(newBlacklist);
                    writeToAccountCSV(acctArr);
                    return true;
                }
            }
        }
        return false;
    }

    public boolean updateAccountPinned(ArrayList<LNComment> newPinned, String curUsername)
            throws ClassNotFoundException, IOException
    {
        ArrayList<LNAccount> acctArr = readFromAccountCSV();
        if (acctArr != null)
        {
            for (int i = 0; i < acctArr.size(); i++)
            {
                if (acctArr.get(i).getEmail().toLowerCase().equals(curUsername.toLowerCase()))
                {
                    acctArr.get(i).setPinned(newPinned);
                    writeToAccountCSV(acctArr);
                    return true;
                }
            }
        }
        return false;
    }

    public boolean updateAccountComments(ArrayList<LNComment> newComments, String curUsername)
            throws ClassNotFoundException, IOException
    {
        ArrayList<LNAccount> acctArr = readFromAccountCSV();
        if (acctArr != null)
        {
            for (int i = 0; i < acctArr.size(); i++)
            {
                if (acctArr.get(i).getEmail().toLowerCase().equals(curUsername.toLowerCase()))
                {
                    acctArr.get(i).setComments(newComments);
                    writeToAccountCSV(acctArr);
                    return true;
                }
            }
        }
        return false;
    }

    public ArrayList<LNAccount> retrieveAccounts() throws ClassNotFoundException, IOException
    {
        ArrayList<LNAccount> acctArr = readFromAccountCSV();
        if(acctArr != null)
        {
            return acctArr;
        }
        return null;
    }
}
