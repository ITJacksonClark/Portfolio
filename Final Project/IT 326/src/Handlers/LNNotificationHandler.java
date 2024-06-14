// Handler for the Notification class
// By Nathan Cerne
// 5/5/24

package Handlers;

import CRUDOps.LNNotificationCRUDOps;
import Models.LNAccount;
import Models.LNNotification;
import OperationsFactory.OperationsFactory;

public class LNNotificationHandler
{
    private boolean verify(String verifyStr)
    {
        return verifyStr instanceof String;
    }

    public LNNotificationCRUDOps getNotifOps()
    {
        return OperationsFactory.getNotifOps();
    }

    public boolean createNotification(int notifID, String titleText, String bodyText, LNAccount account)
    {
        return getNotifOps().createNotification(notifID, titleText, bodyText, account);
    }

    public boolean deleteNotification(LNNotification notif)
    {
        if (!notif.getUnread())
        {
            return getNotifOps().deleteNotification(notif);
        }
        return false;
    }

}
