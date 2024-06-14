// Controller for the Comment class
// By Nathan Cerne, Matthew Cox, & Derek Kmieciak
// 5/5/24

package Controllers;

import Handlers.LNCommentHandler;
import Models.LNAccount;
import Models.LNComment;
import Models.LNFile;

public class LNCommentController
{
    private static LNCommentHandler commHandler = null;

    private static LNCommentHandler getLNCommentHandlerInstance()
    { // Gets the comment handler object
        if (commHandler == null)
            commHandler = new LNCommentHandler();
        return commHandler;
    }

    public static boolean leaveComment(String text, LNFile file, LNAccount owner, LNAccount fileOwner)
    {
        return getLNCommentHandlerInstance().leaveComment(text, file, owner, fileOwner);
    }

    public static boolean replyToComment(String text, LNComment comment, LNAccount owner)
    {
        return getLNCommentHandlerInstance().replyToComment(text, comment, owner);
    }
}
