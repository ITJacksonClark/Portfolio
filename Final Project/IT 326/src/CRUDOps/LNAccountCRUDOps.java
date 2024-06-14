// CRUD operations for the Account class
// By Jackson Clark & Derek Kmieciak
// 5/5/24

package CRUDOps;

import java.io.IOException;
import java.util.ArrayList;

//import Classes.LNAccount;
//import Classes.LNComment;
import Models.LNAccount;
import Models.LNComment;

public abstract class LNAccountCRUDOps
{
        public abstract ArrayList<LNAccount> readFromAccountCSV() throws IOException, ClassNotFoundException; // abstract
                                                                                                              // method
                                                                                                              // for
                                                                                                              // reading
                                                                                                              // in
                                                                                                              // the
                                                                                                              // accounts.csv
                                                                                                              // file

        public abstract boolean writeToAccountCSV(ArrayList<LNAccount> accts)
                        throws IOException, ClassNotFoundException; // abstract
                                                                    // method
                                                                    // for
                                                                    // writing
                                                                    // to
                                                                    // the
                                                                    // accounts.csv
                                                                    // file

        public abstract boolean saveAcct(LNAccount acct) throws IOException, ClassNotFoundException; // abstract method
                                                                                                     // for
                                                                                                     // saving an
                                                                                                     // account

        public abstract LNAccount retrieveAcct(String username) throws IOException, ClassNotFoundException; // abstract
                                                                                                            // method
                                                                                                            // for
                                                                                                            // retrieving
                                                                                                            // an
                                                                                                            // account

        public abstract boolean deleteAccount(String username, String password)
                        throws IOException, ClassNotFoundException; // abstract
                                                                    // method
                                                                    // for
                                                                    // deleting
                                                                    // an
                                                                    // account

        public abstract boolean updateAccount(String username, String password, String curUsername, String curPassword)
                        throws IOException, ClassNotFoundException; // abstract method for updating an account

        public abstract int getNotifCount(String username) throws IOException, ClassNotFoundException; // Abstract
                                                                                                       // method
                                                                                                       // for getting
                                                                                                       // amount
                                                                                                       // of
                                                                                                       // notifications

        public abstract boolean disableNotifs(String username) throws IOException, ClassNotFoundException; // Abstract
                                                                                                           // method for
                                                                                                           // disabling
                                                                                                           // notifications

        public abstract boolean clearNotifs(String username) throws IOException, ClassNotFoundException;

        public abstract boolean updateAccountBlocked(ArrayList<Integer> newBlacklist, String curUsername)
                        throws IOException, ClassNotFoundException;

        public abstract boolean updateAccountPinned(ArrayList<LNComment> newPinned, String curUsername)
                        throws IOException, ClassNotFoundException;

        public abstract boolean updateAccountComments(ArrayList<LNComment> newComments, String curUsername)
                        throws IOException, ClassNotFoundException;

        public abstract ArrayList<LNAccount> retrieveAccounts() throws IOException, ClassNotFoundException;
};
