// Operations for the Folder class
// By Matthew Cox
// 5/5/24

package Operations;

import CRUDOps.LNFolderCRUDOps;
import Models.*;
import java.util.ArrayList;

public class LNFolderOperations extends LNFolderCRUDOps
{
    private ArrayList<LNFolder> folders = null;
    private static LNFolderCRUDOps folOps = null;

    public static LNFolderCRUDOps getLNFolderOperationsInstance()
    {
        if(folOps == null)
            folOps = new LNFolderOperations();
        return folOps;
    }

    @Override
    public LNFolder createFolder(String name, LNAccount owner)
    {
        //Creates a new folder
        LNFolder fol = new LNFolder(name, owner);
        //Sets the folders array list to the owners arraylist
        folders = owner.getFolders();
        //New folder gets added to the arraylist
        folders.add(fol);
        //Owners owned folders gets updated
        owner.setFolders(folders);
        return fol;
    }

    @Override
    public boolean deleteFolder(LNFolder folToDel)
    {
       if (folToDel == null)
            return false;
        else
        {
            //Finds the owner of the folder
            LNAccount folToDelOwner = folToDel.getOwner();
            folders = folToDelOwner.getFolders();
            //for loop that gos through the owner's ownedFolders list
            for (int i = 0; i < folders.size(); i++)
            {
                //If statement to check if the current folder is the same as the one getting deleted
                if(folToDel.getFolderID() == folders.get(i).getFolderID())
                {
                    //Removes folder from the arraylist and sets the owners arraylist to the updated arraylist
                    folders.remove(i);
                    folToDelOwner.setFolders(folders);
                    return true;
                }
            }
            //Returns false in the case that folder can't be found
            return false;
        }
    }

    @Override
    public boolean saveFolder()
    {
        //todo
        return false;
    }

    @Override
    public boolean updateFolder(LNFolder folder, int FolderID, String name, LNAccount owner, ArrayList<LNFile> files)
    {
        //If statement that returns false if the folder is a null object
        if(folder == null)
            return false;
        
        //If statemment to check if the name is getting updated
        if(!folder.getName().equals(name))
            folder.setName(name);
        
        //If statement to check if the owner is gettting updated
        if(folder.getOwner().getAcctID() != owner.getAcctID())
        {
            deleteFolder(folder); //deletes the folder from the orgnial owners folder arraylist
            folder.setOwner(owner); //changes the owner of the folder
            //Updates the owners folders arraylist
            folders = owner.getFolders();
            folders.add(folder);
            owner.setFolders(folders);
        }
        
        return true;
    }

    @Override
    public boolean addFile(LNFolder folder, LNFile file)
    {
       //Checks if the folder or the file are null 
       if(folder == null || file == null)
            return false;

       //Adds the file to the folder 
       ArrayList<LNFile> fileList = folder.getFileList();
       fileList.add(file);
       folder.setFileList(fileList); 
       return true;
    }

    @Override
    public boolean deleteFile(LNFolder folder, LNFile file)
    {
        //Checks if the folder or the file are null 
        if(folder == null || file == null)
            return false;
        
        //Removes the file from the folder
        ArrayList<LNFile> fileList = folder.getFileList();
        for(int i = 0; i < fileList.size(); i++)
        {
            if(fileList.get(i).getID() == file.getID())
            {
                fileList.remove(i);
                return true;
            }
        }

        //Returns false if the file can't be found in the folder
        return false;
    }
}