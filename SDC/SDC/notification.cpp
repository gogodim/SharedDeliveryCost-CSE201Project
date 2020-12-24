#include "notification.h"

#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Dbo/Impl.h>

DBO_INSTANTIATE_TEMPLATES(Notification);

using namespace Wt::Dbo;

Notification::Notification(){
    userID = 0;
    orderID = 0;
    costShare = 0;
    deliveryLocation = "";
    //std::vector< std::pair < std::pair <std::string,std::string> , int > > vect;
    otherOrders = "";//"username1,contact1,pays1 username2,contact2,pays2 ..."
}
