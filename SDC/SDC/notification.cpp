#include "notification.h"

#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Dbo/Impl.h>

DBO_INSTANTIATE_TEMPLATES(Notification);

using namespace Wt::Dbo;

Notification::Notification(){
    username = "";
    orderID = 0;
    costShare = 0;
    deliveryLocation = "";
    otherOrders = "";//format: "username1,contact1,pays1 username2,contact2,pays2 ..."
}
