// Operations for the Comment class
// By Nathan Cerne, Matthew Cox, & Derek Kmieciak
// 5/5/24

package Operations;

import java.util.ArrayList;

import CRUDOps.LNCommentCRUDOps;
import Models.LNAccount;
import Models.LNComment;
import Models.LNFile;

public class LNCommentOperations extends LNCommentCRUDOps
{

    private static LNCommentCRUDOps commOps = null;

    public static LNCommentCRUDOps getLNCommentOperationsInstance()
    { // Gets the abstract account CRUDOps object
        if (commOps == null)
            commOps = new LNCommentOperations();
        return commOps;
    }

    public boolean saveComment(int commentID, String commentText, LNAccount owner, LNFile file,
            ArrayList<LNComment> replies)
    {
        return commOps.saveComment(commentID, commentText, owner, file, replies);
    }

    public boolean deleteComment(int commentID)
    {
        return deleteComment(commentID);
    }

    public LNComment retreiveComment(int commentID)
    {
        return commOps.retreiveComment(commentID);
    }

    public boolean updateComment(int commentID, String newData)
    {
        return commOps.updateComment(commentID, newData);
    }

}
