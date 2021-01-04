#ifndef SESSION_H_
#define SESSION_H_

#include <vector>

#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include "notification.h"

using namespace Wt;

// Session Class used to hold users that connect to this website

/*
Represents all the functions needed for one session.
*/
class Session
{
public:

  Session();
  ~Session();
  std::string userName() const;

  std::vector<Notification> readAllNotifications();
  void addNotification(int userID,int orderID,double costShare,std::string deliveryLocation,std::string otherOrders);
private:
  mutable Dbo::Session session_;
  Dbo::ptr<Notification> notification() const;
};

#endif //SESSION_H_
