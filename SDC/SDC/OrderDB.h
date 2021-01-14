#ifndef ORDERDB_H
#define ORDERDB_H

#include <Wt/WDateTime.h>
#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include "UserDB.h"
#include "CompanyDB.h"
using namespace Wt;

namespace dbo = Wt::Dbo;


class OrderDB;
typedef dbo::collection< dbo::ptr<OrderDB> > OrderDBs;

class OrderDB{
public:
    OrderDB();
    OrderDB(int orderID,
          std::string username,
          std::string companyname,
          double value,
          double delivery_cost,
          double distance,
          std::string address,
          double latitude,double longitude);
    std::string get_username();
    std::string get_companyname();
    double get_value();
    double get_delivery_cost();
    double get_distance();

    int orderID;
    std::string username;
    std::string companyname;
    double value;
    double delivery_cost;
    double distance;
    std::string address;
    double latitude;
    double longitude;

    template<class Action>
    void persist(Action& a)
    {
      dbo::field(a, orderID, "orderID");
      dbo::field(a, username, "username");
      dbo::field(a, companyname, "companyname");
      dbo::field(a, value, "value");
      dbo::field(a, delivery_cost, "delivery_cost");
      dbo::field(a, distance, "distance");
      dbo::field(a, address, "address");
      dbo::field(a, latitude, "latitude");
      dbo::field(a, longitude, "longitude");
    }


};

DBO_EXTERN_TEMPLATES(OrderDB);

#endif // ORDERDB_H
