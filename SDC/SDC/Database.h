#ifndef DATABASE_H
#define DATABASE_H

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <string>
#include "Coordinate.h"
#include "User.h"
#include "notification.h"
#include "Order.h"
#include "OrderDB.h"
#include "Company.h"

namespace dbo = Wt::Dbo;

class Database
{
public:
    Database();
    bool add_user(const User*);
    bool find_user(const User*);
    bool valid_user(const User*);
    std::vector<Notification> readAllNotifications();
    void addNotification(std::string username,int orderID,double costShare,
                         std::string deliveryLocation,std::string otherOrders);
    dbo::Session session;
    bool addOrder(std::string username, double maxDeliveryCost, std::string deliveryLocation,
                  double orderCost, double radius, std::string store);

private:
    mutable Dbo::Session session_;
    dbo::ptr<Notification> notification() const;
    dbo::ptr<OrderDB> orderDB() const;

};

#endif // DATABASE_H
