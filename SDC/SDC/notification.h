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

class Notification
{
public:
  Notification(int userID, int orderID,double costShare,std::string deliveryLocation,std::vector< std::pair < std::pair <std::string,std::string> , int> > otherOrders);

  int userID; /* The userID of the user for which the notification is dedicated */
  int orderID;
  double costShare;
  std::string deliveryLocation;
  std::vector< std::pair < std::pair <std::string,std::string> , int> > otherOrders;

  template<class Action>
  void persist(Action& a)
  {
    dbo::field(a, orderID, "orderID");
    dbo::field(a, costShare, "costShare");
    dbo::field(a, deliveryLocation, "deliveryLocation");
    dbo::field(a, otherOrders, "otherOrders");
  }
};

DBO_EXTERN_TEMPLATES(Notification);
#endif // NOTIFICATION_H
