#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <Wt/WDateTime.h>
#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/Auth/Dbo/AuthInfo.h>

#include <string>
#include <vector>


using namespace Wt;

namespace dbo = Wt::Dbo;

class Notification;
typedef dbo::collection< dbo::ptr<Notification> > Notifications;

/*
Class that represents individual notifications and the way theiy are stored in the darabase.
*/
class Notification
{
public:
  Notification();

  int userID; // The userID of the user for whom the notification is dedicated
  int orderID; // The orderID of the order for which the notification is dedicated
  double costShare; // The amount that the user with userID needs to pay for the order with orderID
  std::string deliveryLocation; // The location at which thet order should be delivered
  //std::vector< std::pair < std::pair <std::string,std::string> , int> > otherOrders;
  std::string otherOrders; //String that needs to be decomposed and contains information about the other users with which the user needs to share the order
  // format of otherOrders: "username1,contact1,pays1 username2,contact2,pays2 ..."

  template<class Action>
  void persist(Action& a)
  {
    dbo::field(a, userID, "userID");
    dbo::field(a, orderID, "orderID");
    dbo::field(a, costShare, "costShare");
    dbo::field(a, deliveryLocation, "deliveryLocation");
    dbo::field(a, otherOrders, "otherOrders");
  }
};

DBO_EXTERN_TEMPLATES(Notification);
#endif // NOTIFICATION_H
