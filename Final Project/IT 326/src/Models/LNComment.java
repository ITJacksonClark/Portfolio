// The Comment class
// By Nathan Cerne, Matthew Cox, & Derek Kmieciak
// 5/5/24

package Models;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Random;

public class LNComment implements Serializable
{
    private LNAccount owner;
    private int commentID;
    private String text;
    private LNFile file; //The file the comment is attached to
    private ArrayList<LNComment> replies;

    //TODO: Placeholder constructor - edit parameters as convenient
    public LNComment(String text, LNFile attachedTo, LNAccount creator) 
    {
        Random rand = new Random();
        this.commentID = rand.nextInt(1000);
        this.owner = creator;
        this.text = text;
        this.file = attachedTo;
        this.replies = new ArrayList<LNComment>();
    }

    public LNAccount getOwner()
    {
        return this.owner;
    }

    public void setOwner(LNAccount owner)
    {
        this.owner = owner;
    }

    public int getID()
    {
        return this.commentID;
    }

    public void setID(int id) //This is probably not needed
    {
        this.commentID = id;
    }

    public String getText()
    {
        return this.text;
    }

    public void setText(String text)
    {
        this.text = text;
    }

    public LNFile getFile()
    {
        return this.file;
    }

    public void setFile(LNFile attachedTo) 
    {
        this.file = attachedTo;
    }

    public ArrayList<LNComment> getReplies()
    {
        return this.replies;
    }

    public void setReplies(ArrayList<LNComment> replies)
    {
        this.replies = replies;
    }
}
