// The driver class for the program
// By Jackson Clark, Joseph Vlastnik, Derek Kmieciak, Nathan Cerne, & Matthew Cox
// 5/5/24

package Main;

import Controllers.LNAccountController;
import Controllers.LNFileController;
import Controllers.LNFolderController;
import Models.LNAccount;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class LNMain
{
    public static int getFileFunc(Scanner scanner,String loginUsername, int folderID){
        System.out.println("Enter the name of the file.");
        String name = scanner.nextLine();
        try {
            return LNFileController.getFileID(name, folderID, loginUsername);
        } catch (ClassNotFoundException | IOException e) {
            System.out.println("yagh");
            return -1;
        }
    }
    public static void main(String[] args) throws IOException, ClassNotFoundException
    {
        boolean endAllFlag = false; // End the app boolean variable
        Scanner scanner = new Scanner(System.in); // Gets user input
        int userInput; // Stores user input
        boolean loginUser = false; // End the user experience boolean variable
        String loginUsername = ""; // Stores the current logged in user's email
        String loginPassword = ""; // Stores the current logged in user's password
        // App starts here
        while (!endAllFlag)
        {
            System.out.println("Select an option: ");
            System.out.println("0: Exit");
            System.out.println("1: Create an account");
            System.out.println("2: Login");
            try
            {
                if (scanner.hasNextLine())
                {
                    userInput = Integer.parseInt(scanner.nextLine());
                    if (userInput < 0 || userInput > 2)
                    {
                        System.out.println("Error: Please enter a valid option");
                    }
                    else if (userInput == 0)
                    {
                        System.out.println("Goodbye");
                        endAllFlag = true;
                    }
                    else if (userInput == 1)
                    {
                        System.out.println("Enter a email");
                        String username = scanner.nextLine();
                        System.out.println("Enter a password");
                        String password = scanner.nextLine();
                        if (LNAccountController.createAccount(username, password))
                        {
                            System.out.println("Account was created and saved successfully!");
                        }
                        else
                        {
                            System.out.println(" Account not created.");
                        }
                    }
                    else if (userInput == 2)
                    {
                        System.out.println("Enter a email");
                        String username = scanner.nextLine();
                        System.out.println("Enter a password");
                        String password = scanner.nextLine();
                        if (LNAccountController.login(username, password))
                        {
                            loginUsername = username;
                            loginPassword = password;
                            loginUser = true;
                        }
                        else
                        {
                            System.out.println("Error: Incorrect username or password");
                        }
                    }
                }
            }
            catch (NumberFormatException e)
            { // Catching user inputting anything but a number
                System.out.println("Error: Please enter a number");
            }

            if (loginUser != false)
            {
                // User experience starts here
                boolean endFlag = false;
                while (!endFlag)
                {
                    System.out.println("0: Loggout");
                    System.out.println("1: Delete Account");
                    System.out.println("2: Update Account");
                    System.out.println("3: Block User");
                    System.out.println("4: Unblock User");
                    System.out.println("5: Pin Comment");
                    System.out.println("6: Remove Comment");
                    System.out.println("7: Edit Comment");
                    System.out.println("8: Check notifactions" + "(" + LNAccountController.getNotifCount(loginUsername)
                            + " new notification(s))");
                    System.out.println("9: Clear all notifications");
                    System.out.println("10: Disable Notifiactions");
                    System.out.println("11: view file");
                    System.out.println("12: search for a comment");
                    System.out.println("13: Upload File");
                    System.out.println("14: Update File Name");
                    System.out.println("15: Update File Contents");
                    System.out.println("16: Download File");
                    System.out.println("17: Move File");
                    System.out.println("18: Remove File");
                    System.out.println("19: create a folder");
                    System.out.println("20: rename a folder");
                    System.out.println("21: remove a folder");
                    // System.out.println("22: leave a comment");
                    // System.out.println("23: reply to a comment");
                    try
                    {
                        userInput = Integer.parseInt(scanner.nextLine());
                        if (userInput < 0 || userInput > 21)
                        {
                            System.out.println("Error: Please enter a valid option");
                        }
                        else if (userInput == 0)
                        {
                            if (LNAccountController.loggout())
                            {
                                loginUsername = "";
                                loginPassword = "";
                                loginUser = false;
                                endFlag = true;
                            }
                        }
                        else if (userInput == 1)
                        {
                            String yesOrNo = "";
                            while (!yesOrNo.toLowerCase().equals("Yes".toLowerCase())
                                    && !yesOrNo.toLowerCase().equals("No".toLowerCase()))
                            {
                                System.out.println("Are you sure you want to do this? (Input Yes or No)");
                                yesOrNo = scanner.nextLine();
                                if (yesOrNo.toLowerCase().equals("Yes".toLowerCase()))
                                {
                                    if (LNAccountController.deleteAccount(loginUsername, loginPassword))
                                    {
                                        loginUsername = "";
                                        loginPassword = "";
                                        loginUser = false;
                                        endFlag = true;
                                    }
                                    else
                                    {
                                        System.out.println("User was not deleted");
                                    }
                                }
                                else if (yesOrNo.toLowerCase().equals("No".toLowerCase()))
                                {
                                    System.out.println("User will not be deleted");
                                }
                                else
                                {
                                    System.out.println("Please input either yes or no");
                                }
                            }
                        }
                        else if (userInput == 2)
                        {
                            System.out.println("Change email here:");
                            String changeUsername = scanner.nextLine();
                            System.out.println("Change password here:");
                            String changePassword = scanner.nextLine();
                            if (LNAccountController.updateAccount(changeUsername, changePassword, loginUsername,
                                    loginPassword))
                            {
                                loginUsername = changeUsername;
                                loginPassword = changePassword;
                                System.out.println("Account successfully updated!");
                            }
                            else
                            {
                                System.out.println("User was not updated");
                            }
                        }
                        else if (userInput == 3)
                        {
                            System.out.println("All accounts & IDs: ");
                            LNAccountController.printNamesAndIDs();
                            LNAccountController.printBlockedUsers(loginUsername);
                            System.out.println("Enter the ID of the user you want to block: ");
                            try
                            {
                                int blocked = Integer.parseInt(scanner.nextLine());
                                if (LNAccountController.blockUser(loginUsername, blocked))
                                    System.out.println("User ID = " + blocked + " blocked successfully!");
                                else
                                    System.out.println("Failed to block user ID = " + blocked
                                            + " (User is already blocked, ID does not exist or attempted to block own ID)");
                            }
                            catch (NumberFormatException e)
                            {
                                System.err.println("Invalid ID number");
                            }
                        }
                        else if (userInput == 4) // Unblock user
                        {
                            int numBlocked = LNAccountController.printBlockedUsers(loginUsername);
                            if (numBlocked == 0)
                            {
                                System.out.println("You have no currently blocked users.");
                            }
                            else
                            {
                                System.out.println("Enter the ID of the user you want to unblock: ");
                                try
                                {
                                    int unblocked = Integer.parseInt(scanner.nextLine());
                                    if (LNAccountController.unblockUser(loginUsername, unblocked))
                                        System.out.println("User ID = " + unblocked + " unblocked successfully!");
                                    else
                                        System.out.println(
                                                "Failed to unblock user ID = " + unblocked + " (User is not blocked)");
                                }
                                catch (NumberFormatException e)
                                {
                                    System.err.println("Invalid ID number");
                                }
                            }
                        }
                        else if (userInput == 5) // Pin Comment
                        {
                            int numCmts = LNAccountController.printComments(loginUsername);
                            if (numCmts == 0)
                                System.out.println("You have no comments to pin.");
                            else
                            {
                                System.out.println("Enter the number of the comment you want to pin: ");
                                try
                                {
                                    int selected = Integer.parseInt(scanner.nextLine());
                                    if (LNAccountController.pinComment(loginUsername, selected))
                                        System.out.println("Comment successfully pinned!");
                                    else
                                        System.out.println("Couldn't pin comment");
                                }
                                catch (NumberFormatException e)
                                {
                                    System.out.println("Invalid selection");
                                }
                            }
                        }
                        else if (userInput == 6) // Remove Comment
                        {
                            int numCmts = LNAccountController.printComments(loginUsername);
                            if (numCmts == 0)
                                System.out.println("You have no comments to remove.");
                            else
                            {
                                System.out.println("Enter the number of the comment you want to remove: ");
                                int removed = Integer.parseInt(scanner.nextLine());
                                try
                                {
                                    if (LNAccountController.removeComment(loginUsername, removed))
                                        System.out.println("Comment successfully removed!");
                                    else
                                        System.out.println("Couldn't remove comment");
                                }
                                catch (NumberFormatException e)
                                {
                                    System.out.println("Invalid selection");
                                }
                            }
                        }
                        else if (userInput == 7) // Edit comment
                        {
                            int numCmts = LNAccountController.printComments(loginUsername);
                            if (numCmts == 0)
                                System.out.println("You have no comments to edit.");
                            else
                            {
                                System.out.println("Enter the number of the comment you want to edit: ");
                                int selected = Integer.parseInt(scanner.nextLine());
                                System.out.println("Enter the new text for the comment: ");
                                try
                                {
                                    String newText = scanner.nextLine();
                                    if (LNAccountController.editComment(loginUsername, selected, newText))
                                        System.out.println("Comment successfully edited!");
                                    else
                                        System.out.println("Couldn't edit comment");
                                }
                                catch (NumberFormatException e)
                                {
                                    System.out.println("Invalid selection");
                                }
                            }
                        }
                        else if (userInput == 8) // check notifications
                        {
                            if (LNAccountController.getNotifCount(loginUsername) == 0)
                                System.out.println("You have no notifications");
                            else
                            {
                                LNAccountController.printNotif(loginUsername);
                            }
                        }
                        else if (userInput == 9) // clear notifications
                        {
                            System.out.println("Clear all notifications? (press 1 to continue)");
                            userInput = Integer.parseInt(scanner.nextLine());
                            if (userInput == 1)
                            {
                                if (LNAccountController.clearNotifs(loginUsername))
                                    System.out.println("Notifiactions cleared");
                            }
                            else
                            {
                                System.out.println("Notifiactions not cleared");
                            }
                        }
                        else if (userInput == 10) // disable notifications
                        {
                            System.out.println("Disable notifacations? (press 1 to continue)");
                            userInput = Integer.parseInt(scanner.nextLine());
                            if (userInput == 1)
                            {
                                if (LNAccountController.disableNotifs(loginUsername))
                                    System.out.println("Notifiactions turned off");
                            }
                            else
                            {
                                System.out.println("Notifiactions will not be disabled");
                            }
                        }
                        else if (userInput == 11) // view a file
                        {
                            System.out.println("Enter ID of desired file");
                            LNFileController.previewFiles();
                            userInput = Integer.parseInt(scanner.nextLine());
                            for (int i = 0; i < LNFileController.previewFiles(); i++)
                            {
                                if (userInput == LNFileController.getFileList().get(i).getID())
                                {
                                    /* the code for viewing the file goes here */
                                    File selectFile = LNFileController.getFileList().get(i).getFile();
                                    LNFileController.viewFile(selectFile);
                                }
                                else
                                {
                                    System.out.println("Error - No ID match found");
                                }
                            }

                        }
                        else if (userInput == 12) // search for a comment
                        {
                            System.out.println("Enter a search term: ");
                            String search = scanner.nextLine();
                            LNAccountController.searchComments(search, loginUsername);
                        }
                        else if (userInput == 13){ //upload file
                            System.out.println("Enter the name of the file.");
                            String name = scanner.nextLine();
                            System.out.println("Enter the folder to put it under, if any.");
                            String folderName = scanner.nextLine();
                            //get folder id here somehow
                            if(LNFileController.uploadFile(name, 0, loginUsername)){
                                System.out.println("File Uploaded.");
                            }
                            else{
                                System.out.println("There was an error. Check if the file is already uploaded?");
                            }
                        }
                        else if (userInput == 14){ //update file name
                            int id = getFileFunc(scanner,loginUsername,0);
                            if(id ==-1){

                            }
                            else{
                                System.out.println("Enter the new name of the file.");
                            String newName = scanner.nextLine();
                            if (LNFileController.updateFile(id, newName, null)) {
                                System.out.println("File modified.");
                            } else {
                                System.out.println("File not modified as there was an error.");
                            }
                            }
                        }
                        else if (userInput == 15){ //update file contents
                            int id = getFileFunc(scanner,loginUsername,0);
                            System.out.println("Enter the new contents of the file.");
                            String newContents = scanner.nextLine();
                            if (LNFileController.updateFile(id, null, newContents)) {
                                System.out.println("File modified.");
                            } else {
                                System.out.println("File not modified as there was an error.");
                            }
                        }
                        else if (userInput == 16){ //download file
                            int id = getFileFunc(scanner,loginUsername,0);
                            System.out.println("Enter the folder to download it to.");
                            String folderName = scanner.nextLine();
                            System.out.println("Enter the name of the file to be downloaded as.");
                            String downloadName = scanner.nextLine();
                            if (LNFileController.downloadFile(downloadName, folderName, LNFileController.getFileFromID(id))) {
                                System.out.println("File Downloaded.");
                            } else {
                                System.out.println("File not downloaded due to error.");
                            }
                        }
                        else if (userInput == 17){ //move file
                            int id = getFileFunc(scanner,loginUsername,0);
                            System.out.println("Enter the folder to move it to, if any.");
                            String folderName = scanner.nextLine();
                            //get new folder int here
                            if(LNFileController.moveFile(LNFileController.getFileFromID(id), 1, loginUsername)){
                                System.out.println("File moved.");
                            }
                            else{
                                System.out.println("File not moved. Check if folder exists or if a file with the same name already exists in there.");
                            }
                        }
                        else if (userInput == 18){ //remove file
                            int id = getFileFunc(scanner,loginUsername,0);
                            if(LNFileController.removeFile(LNFileController.getFileFromID(id)))
                            System.out.println("File has been removed");
                            else
                            System.out.println("There was an error.");
                        }
                        else if(userInput == 19) //Create a folder
                        {
                            System.out.print("Please enter name of new folder: ");
                            String folderName = scanner.nextLine();
                            LNAccount temp = LNAccountController.searchForAccount(loginUsername);
                            LNFolderController.createFolder(folderName, temp);
                            temp.saveAccount();
                            System.out.println(temp.getFolders().size());
                        }
                        else if(userInput == 20) // rename folder
                        {
                            LNAccount tempAcct = LNAccountController.searchForAccount(loginUsername);
                            for(int i = 0; i < tempAcct.getFolders().size(); i++)
                            {
                                System.out.println(tempAcct.getFolders().get(i).getName() + ": " +
                                tempAcct.getFolders().get(i).getFolderID());
                            }
                            System.out.print("Please enter the ID of the folder: ");
                            int folderID = Integer.parseInt(scanner.nextLine());
                            System.out.print("Please enter new name: " );
                            String newFolderName = scanner.nextLine();
                            LNFolderController.renameFolder(folderID, newFolderName, tempAcct);
                            tempAcct.saveAccount();    
                        }
                        else if (userInput == 21) // remove folder
                        {
                            LNAccount tempAcct = LNAccountController.searchForAccount(loginUsername);
                            for(int i = 0; i < tempAcct.getFolders().size(); i++)
                            {
                                System.out.println(tempAcct.getFolders().get(i).getName() + ": " +
                                tempAcct.getFolders().get(i).getFolderID());
                            }
                            System.out.print("Please enter the ID of the folder: ");
                            int folderID = Integer.parseInt(scanner.nextLine());
                            LNFolderController.removeFolder(folderID, tempAcct);
                            tempAcct.saveAccount();
                        }
                        // else if(userInput == 22) // leave comement
                        // {
                        //     LNAccount tempAcct = LNAccountController.searchForAccount(loginUsername);
                        //     LNFile testFile = null;
                        //     LNAccount testAccount = new LNAccount("123", "456");
                        //     LNCommentController.leaveComment("Test", testFile, testAccount, tempAcct);
                        // }
                        // else if(userInput == 23) // reply to comment
                        // {
                        //     System.out.println("Please enter the Comment's owner's username: ");
                        //     String commentOwner = scanner.nextLine(); 
                        //     for(int i = 0; i < LNAccountController.searchForAccount(commentOwner).getComments().size(); i++)
                        //     {
                        //         System.out.println(LNAccountController.searchForAccount(commentOwner).getComments().get(i).getID() + ": " +
                        //         LNAccountController.searchForAccount(commentOwner).getComments().get(i).getText());
                        //     }
                        //     System.out.println("What is the ID of the comment you would like to reply to?");
                        //     int commentID = Integer.parseInt(scanner.nextLine());
                        //     LNComment comment = null;
                        //     for(int i = 0; i < LNAccountController.searchForAccount(commentOwner).getComments().size(); i++)
                        //     {
                        //         if(LNAccountController.searchForAccount(commentOwner).getComments().get(i).getID() == commentID)
                        //         {
                        //             comment = LNAccountController.searchForAccount(commentOwner).getComments().get(i);
                        //             break;
                        //         }
                        //     }
                        //     System.out.println("Please enter your response: ");
                        //     String responseText = scanner.nextLine();
                        //     LNCommentController.replyToComment(responseText, comment, LNAccountController.searchForAccount(loginUsername));
                        // }

                    }
                    catch (NumberFormatException e)
                    {
                        System.out.println("Error: Please enter a number");
                    }
                }
                // User experience ends here
            }
        }
        // App ends here
        PrintWriter pw = new PrintWriter("accounts.csv");
        pw.print(""); // Clears file after use
        pw.close();
        scanner.close();
    }
}
