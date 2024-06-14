// Operations for the Notification class
// By Nathan Cerne
// 5/5/24

package Operations;

import CRUDOps.LNNotificationCRUDOps;
import Models.LNAccount;
import Models.LNNotification;

public class LNNotificationOperations extends LNNotificationCRUDOps
{

    private static LNNotificationCRUDOps notifOps = null;

    public static LNNotificationCRUDOps getLNNotificationOperationsInstance()
    {
        if (notifOps == null)
            notifOps = new LNNotificationOperations();
        return notifOps;
    }

    public boolean createNotification(int notifID, String titleText, String bodyText, LNAccount account)
    {
        LNNotification notif = new LNNotification(notifID, bodyText, titleText, account);
        return true;
    }

    public boolean deleteNotification(LNNotification notif)
    {
        notif = null;
        return false;
    }

}
