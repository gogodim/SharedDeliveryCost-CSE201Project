#ifndef DATABASE_H
#define DATABASE_H

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <string>
#include "CoordinateDB.h"
#include "UserDB.h"
#include "notification.h"
#include "CompanyDB.h"
#include "OrderDB.h"

namespace dbo = Wt::Dbo;

class Database
{
public:
    Database();
    bool add_user(const UserDB*);
    bool find_user(const UserDB*);
    bool valid_user(const UserDB*);
    std::vector<Notification> readAllNotifications();
    void addNotification(std::string username,int orderID,double costShare,std::string deliveryLocation,std::string otherOrders);
    dbo::Session session;
    bool addOrder(std::string username, double maxDeliveryCost, std::string deliveryLocation,
                  double orderCost, double radius, std::string store);

private:
    mutable Dbo::Session session_;
    dbo::ptr<Notification> notification() const;

};

#endif // DATABASE_H
