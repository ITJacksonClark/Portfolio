// Handler for the File class
// By Joseph Vlastnik & Nathan Cerne
// 5/5/24

package Handlers;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import CRUDOps.LNFileCRUDOps;
import Models.LNFile;
import OperationsFactory.OperationsFactory;

public class LNFileHandler {

    public static LNFileCRUDOps getFileOps() //
    {
        return OperationsFactory.getFileOps();
    }

    public boolean uploadFile(String name, int folderID, String account) throws ClassNotFoundException, IOException {
        if (verify(name) && verify(folderID) && verify(account))
            return getFileOps().createFile(name, folderID, account);
        else
            return false;
    }

    public boolean removeFile(LNFile file) throws ClassNotFoundException, IOException {
        if (verify(file))
            return getFileOps().deleteFile(file);
        else
            return false;
    }

    public boolean moveFile(LNFile file, int destination, String account) throws ClassNotFoundException, IOException {
        if (verify(file) && verify(destination) && verify(account))
            return getFileOps().moveFile(file.getfileID(), destination, account);
        else
            return false;
    }

    public boolean updateFile(int id, String name, String contents) throws ClassNotFoundException, IOException {
        if (verify(id) && (verify(name)||name==null) && (verify(contents)||contents==null))
            return getFileOps().updateFile(id, name, contents);
        else
            return false;
    }

    public boolean downloadFile(String name, String folder, LNFile file) throws IOException {
        if (verify(name) && verify(folder) && verify(file))
            return getFileOps().downloadFile(name, folder, file);
        else
            return false;
    }

    private boolean verify(String verifyStr) {
        return verifyStr instanceof String;
    }

    private boolean verify(Integer verifyInt) {
        return verifyInt instanceof Integer;
    }

    private boolean verify(LNFile verifyFile) {
        return verifyFile instanceof LNFile;
    }

    private boolean verify(File verifyFile) {
        return verifyFile instanceof File;
    }

    public int previewFiles() throws ClassNotFoundException, IOException {
        return getFileOps().previewFiles();
    }

    public ArrayList<LNFile> getFileList() throws ClassNotFoundException, IOException {
        return getFileOps().getFileList();
    }

    public int viewFile(File theFile) {
        if(verify(theFile))
        return getFileOps().viewFile(theFile);
        return -1;
    }

    public int getFileID(String name, int folderID, String account) throws ClassNotFoundException, IOException {
        if (verify(name) && verify(folderID) && verify(account))
        return getFileOps().getFileID(name, folderID, account);
        System.out.println("dummy");
        return -1;
    }
    public LNFile getFileFromID(int id){
        if(verify(id))
            try {
                return getFileOps().getFileByID(id);
            } catch (Exception e) {
                return null;
            }
        return null;
    }
}
