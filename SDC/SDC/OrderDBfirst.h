#ifndef ORDER_H
#define ORDER_H

#include "UserDB.h"
#include "CompanyDB.h"

class OrderDBfirst{
public:
    OrderDBfirst(UserDB user,
          CompanyDB company,
          double value,
          double delivery_cost,
          double distance);
    UserDB get_user();
    CompanyDB get_company();
    double get_value();
    double get_delivery_cost();
    double get_distance();
    bool operator==(OrderDBfirst other);


//private:
    UserDB user;
    CompanyDB company;
    double value;
    double delivery_cost;
    double distance;

};

#endif // ORDER_H
