// Controller for the File class
// By Joseph Vlastnik & Nathan Cerne
// 5/5/24

package Controllers;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import Models.LNFile;
import Handlers.LNFileHandler;

public class LNFileController {
    private static LNFileHandler handler = null;

    public static LNFileHandler getLNFileHandlerInstance() {
        if (handler == null)
            handler = new LNFileHandler();
        return handler;
    }

    // finalize, save it.
    public static boolean uploadFile(String name, int folderID, String account) throws ClassNotFoundException, IOException {
        return getLNFileHandlerInstance().uploadFile(name, folderID, account);
    }

    public static boolean removeFile(LNFile file) throws ClassNotFoundException, IOException {
        return getLNFileHandlerInstance().removeFile(file);
    }

    public static boolean moveFile(LNFile file, int destination, String account) throws ClassNotFoundException, IOException {
        return getLNFileHandlerInstance().moveFile(file, destination, account);
    }

    // when call update file, in that method you will ask user what they will want
    // to change,title, text
    public static boolean updateFile(int id, String name, String contents) throws ClassNotFoundException, IOException {
        return getLNFileHandlerInstance().updateFile(id, name, contents);
    }

    public static boolean downloadFile(String name, String folder, LNFile file) throws IOException {
        return getLNFileHandlerInstance().downloadFile(name, folder, file);
    }

    public static int previewFiles() throws ClassNotFoundException, IOException {
        return getLNFileHandlerInstance().previewFiles();
    }

    public static ArrayList<LNFile> getFileList() throws ClassNotFoundException, IOException {
        return getLNFileHandlerInstance().getFileList();
    }

    public static int viewFile(File theFile) {
        return getLNFileHandlerInstance().viewFile(theFile);
    }

    public static int getFileID(String name, int folderID, String account) throws ClassNotFoundException, IOException {
        return getLNFileHandlerInstance().getFileID(name,folderID, account);
    }

    public static LNFile getFileFromID(int id) {
        return getLNFileHandlerInstance().getFileFromID(id);
    }
}
