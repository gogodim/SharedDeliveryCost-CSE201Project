#ifndef ORDER_H
#define ORDER_H

#include "User.h"
#include "Company.h"

class Order{
public:
    Order(User user,
          Company company,
          double value,
          double delivery_cost,
          double distance);
    User get_user();
    Company get_company();
    double get_value();
    double get_delivery_cost();
    double get_distance();
    bool operator==(Order other);


//private:
    User user;
    Company company;
    double value;
    double delivery_cost;
    double distance;

};

#endif // ORDER_H
