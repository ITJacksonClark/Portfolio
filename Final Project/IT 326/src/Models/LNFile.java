// The File class
// By Joseph Vlastnik & Nathan Cerne
// 5/5/24

package Models;

import java.io.File;
import java.io.FileWriter;
import java.io.Serializable;
import java.io.IOException;
import java.util.List;
import java.util.Random;

import CRUDOps.LNFileCRUDOps;
import Operations.LNFileOperations;
import java.util.ArrayList;

public class LNFile implements Serializable {
    private int fileID;
    private String name;
    private String content;
    private int folderID;
    private String account;
    private File actualFile;
    private ArrayList<LNComment> comments;

    public LNFile(String name, int folderID, String account) {
        this.name = name;
        this.folderID = folderID;
        this.account = account;
        fileID = generateID();
        content = "";
        actualFile = new File(name);
        try {
            actualFile.createNewFile();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private int generateID() {
        Random gen = new Random();
        int ID = -1;
        while (ID == -1) {
            ID = gen.nextInt(10000);
            try {
                if (getFileOps().getFileByID(ID) != null) {
                    ID = -1;
                }
            } catch (ClassNotFoundException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
        return ID;
    }

    // return name of file.
    public String getName() {
        return name;
    }

    public void deleteFile() {
        comments = null;
        actualFile.delete();
    }

    public String getAccount() {
        return account;
    }

    public boolean addComment(LNComment e) {
        comments.add(e);
        return true;
    }

    public boolean setName(String name) {
        File newFile = new File(name);
        boolean worked = actualFile.renameTo(newFile);
        if(worked){
            this.name = name;
            if(actualFile.exists()){
                actualFile.delete();
            }
            actualFile = newFile;
        }
        return worked;
    }

    public boolean setContents(String contents) {
        if(actualFile.canWrite()){
            try (FileWriter toWrite = new FileWriter(actualFile)) {
                toWrite.write(contents);
                toWrite.close();
                content = contents;
            } catch (IOException e) {
                return false;
            }
            return true;
        }
        else{
            return false;
        }
    }

    public int getfileID() {
        return fileID;
    }

    public void setfileID(int fileID) {
        this.fileID = fileID;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public int getFolderID() {
        return folderID;
    }

    public void setFolderID(int folderID) {
        this.folderID = folderID;
    }

    public void setaccount(String account) {
        this.account = account;
    }

    public void setComments(ArrayList<LNComment> comments) {
        this.comments = comments;
    }

    public static LNFileCRUDOps getFileOps() {
        return LNFileOperations.getLNFileOperationsInstance();
    }

    public File getFile() {
        return this.actualFile;
    }

    public int getID() {
        return this.fileID;
    }

    public ArrayList<LNComment> getComments() {
        return this.comments;
    }
}
