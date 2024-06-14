// The operations factory
// By Jackson Clark, Joseph Vlastnik, Derek Kmieciak, Nathan Cerne, & Matthew Cox
// 5/5/24

package OperationsFactory;

import CRUDOps.LNAccountCRUDOps;
import CRUDOps.LNCommentCRUDOps;
import CRUDOps.LNFileCRUDOps;
import CRUDOps.LNFolderCRUDOps;
import CRUDOps.LNNotificationCRUDOps;
import Operations.LNAccountOperations;
import Operations.LNCommentOperations;
import Operations.LNFileOperations;
import Operations.LNFolderOperations;
import Operations.LNNotificationOperations;

public class OperationsFactory
{
    public static LNAccountCRUDOps getAcctOps()
    {
        return LNAccountOperations.getLNAccountOperationsInstance();
    }

    public static LNFileCRUDOps getFileOps() {
        return LNFileOperations.getLNFileOperationsInstance();
    }

    public static LNNotificationCRUDOps getNotifOps()
    {
        return LNNotificationOperations.getLNNotificationOperationsInstance();
    }

    public static LNCommentCRUDOps getCommOps()
    {
        return LNCommentOperations.getLNCommentOperationsInstance();
    }

    public static LNFolderCRUDOps getFolOps()
    {
        return LNFolderOperations.getLNFolderOperationsInstance();
    }
}
