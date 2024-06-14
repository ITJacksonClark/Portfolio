// Operations for the File class
// By Joseph Vlastnik & Nathan Cerne
// 5/5/24

package Operations;

import CRUDOps.LNFileCRUDOps;
import Models.LNFile;

import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class LNFileOperations extends LNFileCRUDOps{

    private static LNFileCRUDOps fileOps = null;


    private LNFile getFileInternal(ArrayList<LNFile> records, int FileID){
        LNFile toGet = null;
        for (int i = 0; i < records.size(); i++) {
            toGet = records.get(i);
            if (toGet.getID()==FileID) {
                break;
            }
            else{
                toGet = null;
            }
        }
        return toGet;
    }
    public static LNFileCRUDOps getLNFileOperationsInstance(){
        if(fileOps==null)
            fileOps = new LNFileOperations();
        return fileOps;
    }

    public boolean createFile(String name,int folder,String account) throws ClassNotFoundException, IOException{
        ArrayList<LNFile> records = readFileCSV(); 
        if(records==null){
            records = new ArrayList<LNFile>();
        }
        if(getFileInternal(records, name, folder, account)!=null){
            return false;
        }
        boolean returnVal = records.add(new LNFile(name,folder,account));
        if(returnVal)
        writeFileCSV(records);
        return returnVal;
    }
    public boolean deleteFile(LNFile deleted) 
    throws IOException, ClassNotFoundException{
        if(deleted== null){
            return false;
        }
        ArrayList<LNFile> records = readFileCSV(); 
        if(records==null){
            return false;
        }
        for (int i = 0; i < records.size(); i++) {
            if(records.get(i).getID()==deleted.getID()){
            deleted.deleteFile();
            writeFileCSV(records);
            return true;
            }
        }
            return false;
    }
    private LNFile getFileInternal(ArrayList<LNFile> records, String name,int folder,String account) throws IOException, ClassNotFoundException{
        LNFile toGet = null;
        for (int i = 0; i < records.size(); i++) {
            toGet = records.get(i);
            if(records.get(i).getName().equals(name)&&
            records.get(i).getFolderID()==folder&&
            records.get(i).getAccount().equals(account)) {
                break;
            }
            else{
                toGet = null;
            }
        }
        return toGet;
    }
    public LNFile getFile(String name,int folder,String account) throws IOException, ClassNotFoundException{
        ArrayList<LNFile> records = readFileCSV(); 
        if(records==null){
            return null;
        }
        LNFile toGet = getFileInternal(records,name,folder,account);
        return toGet;
    }
    public LNFile getFileByID(int id) throws IOException, ClassNotFoundException{
        ArrayList<LNFile> records = readFileCSV(); 
        if(records==null){
            return null;
        }
        LNFile toGet = getFileInternal(records,id);
        return toGet;
    }

    public boolean updateFile(int FileID, String name, String contents)
    throws IOException, ClassNotFoundException{
        ArrayList<LNFile> records = readFileCSV(); 
        if(records==null){
            return false;
        }
        LNFile toGet = getFileInternal(records,FileID);
        if(toGet==null){
            return false;
        }
        boolean noError= true;
        if (name != null) {
            noError = toGet.setName(name);
        }
        //don't want to have it continue on if we run into an error beforehand for renaming it
        if(contents!= null&&noError){
            noError = toGet.setContents(contents);
        }
        //if there is no error, we update it. else just ignore
        if(noError){
            writeFileCSV(records);
        }
        return noError;
    }

    public boolean moveFile(int FileID, int folder, String callingAccount)
    throws IOException, ClassNotFoundException{
        ArrayList<LNFile> records = readFileCSV(); 
        if(records==null){
            return false;
        }
        LNFile toGet = getFileInternal(records,FileID);
        if(toGet==null){
            return false;
        }
        LNFile existing = getFileInternal(records,toGet.getName(),folder,callingAccount);
        if(existing!=null){
            return false;
        }
        toGet.setFolderID(folder);
        writeFileCSV(records);
        return true;
    }

    public boolean downloadFile(String fileName, String folderName, LNFile toDownload) 
    throws IOException{
        File folderPath = new File(folderName);
        File newFile = new File(folderName+fileName);
        boolean madeFolders = folderPath.mkdirs();
        //check if the folders were made or if path exists, if so, check
        //if file can be made or written to, then write
        if (madeFolders||folderPath.exists()) {
            if (newFile.createNewFile()||newFile.canWrite()) {
                FileWriter toWrite = new FileWriter(newFile);
                toWrite.write(toDownload.getContent());
                toWrite.close();
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
@Override
public ArrayList<LNFile> readFileCSV() throws IOException, ClassNotFoundException {
    try {
        FileInputStream files = new FileInputStream("files.csv");
        ObjectInputStream filesToFiles = new ObjectInputStream(files);
        ArrayList<LNFile> toRead = (ArrayList<LNFile>) filesToFiles.readObject();
        filesToFiles.close();
        return toRead;
    } catch (Exception e) {
        return null;
    }
}
@Override
public boolean writeFileCSV(ArrayList<LNFile> records) throws IOException, ClassNotFoundException {
    File csvFile = new File("files.csv");
        csvFile.createNewFile();
        try {
            FileOutputStream fos = new FileOutputStream(csvFile);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.flush();
            oos.writeObject(records);
            oos.close();
            return true;
        } catch (Exception e) {
            return false;
        }
}


    public int previewFiles() throws ClassNotFoundException, IOException
    {
        ArrayList<LNFile> records = readFileCSV(); 
        if (records != null)
        {
            for (int i = 0; i < records.size(); i++)
            {
                System.out.println("ID:" + records.get(i).getID() + ", Name: " + records.get(i).getName());
            }
            return records.size();
        }
        else
        {
            System.out.println("No files present");
            return 0;
        }
    }

    public ArrayList<LNFile> getFileList() throws ClassNotFoundException, IOException
    {
        ArrayList<LNFile> records = readFileCSV(); 
        return records;
    }

    public int viewFile(File theFile)
    {
        BufferedReader reader = null;
        try
        {
            reader = new BufferedReader(new FileReader(theFile));
            String line;
            while ((line = reader.readLine()) != null)
            {
                System.out.println(line);
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        finally
        {
            try
            {
                if (reader != null)
                {
                    reader.close();
                }
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }
        }
        return 0;
    }
    @Override
    public int getFileID(String name, int folderID, String account) throws ClassNotFoundException, IOException {
        ArrayList<LNFile> records = readFileCSV(); 
        if(records==null){
            return -1;
        }
        LNFile toGet = getFileInternal(records,name,folderID,account);
        if(toGet== null)
        return -1;
        return toGet.getID();
    }
}
