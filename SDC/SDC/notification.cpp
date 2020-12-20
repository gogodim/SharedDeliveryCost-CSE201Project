#include "notification.h"

#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Dbo/Impl.h>

DBO_INSTANTIATE_TEMPLATES(Notification);

using namespace Wt::Dbo;

Notification::Notification(int userID1, int orderID1,double costShare1,std::string deliveryLocation1,std::vector< std::pair < std::pair <std::string,std::string> , int> > otherOrders1){
    userID = userID1;
    orderID = orderID1;
    costShare = costShare1;
    deliveryLocation = deliveryLocation1;
    otherOrders = otherOrders1;
}
