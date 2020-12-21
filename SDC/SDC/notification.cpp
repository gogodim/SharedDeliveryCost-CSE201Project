#include "notification.h"

#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Dbo/Impl.h>

DBO_INSTANTIATE_TEMPLATES(Notification);

using namespace Wt::Dbo;

Notification::Notification(){
    userID = 123;
    orderID = 123;
    costShare = 123;
    deliveryLocation = "123";
    //std::vector< std::pair < std::pair <std::string,std::string> , int > > vect;
    otherOrders = "123";
}
