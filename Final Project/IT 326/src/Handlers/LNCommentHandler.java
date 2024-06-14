// Handler for the Comment class
// By Nathan Cerne, Matthew Cox, & Derek Kmieciak
// 5/5/24

package Handlers;

import CRUDOps.LNCommentCRUDOps;
import Models.LNAccount;
import Models.LNComment;
import Models.LNFile;
import OperationsFactory.OperationsFactory;
import java.util.ArrayList;

public class LNCommentHandler
{

    private boolean verify(String verifyStr) // verifies that the parameter is a string
    {
        return verifyStr instanceof String;
    }

    private boolean verify(int verifyInt) // Verifies parameter is an integer
    {
        try
        {
            Integer temp = (Integer) verifyInt;
            return true; // Cast succeeded, we have an integer. (instanceof doesnt work on primitves)
        }
        catch (Exception e)
        {
            return false; // Cast failed - not int
        }
    }

    public static LNCommentCRUDOps getCommOps()
    {
        return OperationsFactory.getCommOps();
    }

    /**
     * Leaves a comment on a file
     * @param text contents of the comment
     * @param file the file
     * @param owner owner of the comment
     * @param fileOwner
     * @return true if the comment if left
     */
    public boolean leaveComment(String text, LNFile file, LNAccount owner, LNAccount fileOwner)
    {
        if(verify(text))
        {
            for(int i = 0; i < fileOwner.getBlockedUsers().size(); i++)
            {
                if(fileOwner.getBlockedUsers().get(i) == owner.getAcctID())
                    return false;
            }
            LNComment newCom = new LNComment(text, file, owner);
            getCommOps().saveComment(newCom.getID(), newCom.getText(), newCom.getOwner(), newCom.getFile(), newCom.getReplies());
            return true;
        }
        else
            return false;
    }

    /**
     * Replys to a comment
     * @param text content of the reply
     * @param comment the comment being replied to
     * @param owner owner of the reply
     * @return True when the comment is left
     */
    public boolean replyToComment(String text, LNComment comment, LNAccount owner)
    {
        if(verify(text))
        {
            for(int i = 0; i < comment.getOwner().getBlockedUsers().size(); i++)
            {
                if(comment.getOwner().getBlockedUsers().get(i) == owner.getAcctID())
                    return false;
            }
            LNComment newReply = new LNComment(text, comment.getFile(), owner);
            ArrayList<LNComment> replies = comment.getReplies();
            replies.add(newReply);
            comment.setReplies(replies);
            return true;
        }
        else
            return false;
    }
}
