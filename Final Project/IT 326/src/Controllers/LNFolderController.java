// Controller for the Folder class
// By Matthew Cox
// 5/5/24

package Controllers;

import Handlers.LNFolderHandler;
import Models.LNAccount;
import Models.LNFile;
import Models.LNFolder;
import java.io.IOException;

public class LNFolderController 
{
    private static LNFolderHandler folHandler = null;

    private static LNFolderHandler getFolderHandlerInstance()
    {
        if (folHandler == null)
            folHandler = new LNFolderHandler();
        return folHandler;
    }

    public static LNFolder createFolder(String name, LNAccount owner) throws ClassNotFoundException, IOException
    {
        return getFolderHandlerInstance().createFolder(name, owner);
    }

    public static boolean renameFolder(int ID, String name, LNAccount owner) throws IOException
    {
        return getFolderHandlerInstance().renameFolder(ID, name, owner);
    }

    public static boolean removeFolder(int ID, LNAccount owner) throws IOException, ClassNotFoundException
    {
        return getFolderHandlerInstance().removeFolder(ID, owner);
    }

    public static boolean addFile(LNFolder folder, LNFile file)
    {
        return getFolderHandlerInstance().addFile(folder, file);
    }

    public static boolean deleteFile(LNFolder folder, LNFile file)
    {
        return getFolderHandlerInstance().deleteFile(folder, file);
    }
}
