// Handler for the Folder class
// By Matthew Cox
// 5/5/24

package Handlers;

import CRUDOps.LNFolderCRUDOps;
import Models.*;
import OperationsFactory.OperationsFactory;
import java.io.IOException;
import java.util.ArrayList;

public class LNFolderHandler 
{
    private boolean verify(String verfString)
    {
        return verfString instanceof String;
    }

    private boolean verify(int verfInt)
    {
        try
        {
            return true;
        }catch (Exception e)
        {
            return false;
        }
    }

    public static LNFolderCRUDOps getFolOps()
    {
        return OperationsFactory.getFolOps();
    }

    /**
     * Method to get the files of the folder
     * @param folder the folder
     * @return the files
     */
    public ArrayList<LNFile> getFilesInFolder(LNFolder folder)
    {
        return folder.getFileList();
    }

    /**
     * Creates a new folder
     * @param name name of the folder
     * @param owner owner of the folder
     * @throws IOException
     * @throws ClassNotFoundException
     * @return the folder
     */
    public LNFolder createFolder(String name, LNAccount owner) throws IOException, ClassNotFoundException
    {
        if(verify(name))
        {
            return getFolOps().createFolder(name, owner);
        }
        else
            return null;
    }

    /**
     * Renames the folder
     * @param ID ID of the folder getting its name changed
     * @param name new name
     * @param owner owner of the file
     * @return True if name is changed
     * @throws IOException
     */
    public Boolean renameFolder(int ID, String name, LNAccount owner) throws IOException
    {
        if(verify(ID))
        {
            LNFolder fol = folderLookUp(ID, owner);
            if(fol == null)
                return null;
            if(verify(name))
            {
                getFolOps().updateFolder(fol, fol.getFolderID(), name, fol.getOwner(), fol.getFileList());
                return true;
            }
            else
                return false;
        }
        else
            return false;

    }

    /**
     * Deletes the folder and the files inside the folder
     * @param ID the ID of the folder being deleted
     * @param owner owner of the folder
     * @return True when the folder is deleted
     * @throws ClassNotFoundException
     * @throws IOException
     */
    public Boolean removeFolder(int ID, LNAccount owner) throws ClassNotFoundException, IOException
    {
        if(verify(ID))
        {
            LNFolder fol = folderLookUp(ID, owner);
            if(fol == null)
                return false;
            else
                return getFolOps().deleteFolder(fol);
        }
        else
            return false;
    }

    public boolean addFile(LNFolder folder, LNFile file)
    {
        return getFolOps().addFile(folder, file);
    }

    public boolean deleteFile(LNFolder folder, LNFile file)
    {
        return getFolOps().deleteFile(folder, file);
    }

    /**
     * Looks up a folder that is owend by a user
     * @param ID id of the folder
     * @param owner owner of the folder
     * @return returns the folder that matched the id 
     */
    private LNFolder folderLookUp(int ID, LNAccount owner)
    {
        ArrayList<LNFolder> folders = owner.getFolders();
        for (int i=0;i < folders.size();i++) 
        {
            if (folders.get(i).getFolderID() == ID)  
                return folders.get(i);
        }
        return null;
    }
}
