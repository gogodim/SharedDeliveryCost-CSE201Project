#include "OrderDB.h"
#include <Wt/Dbo/Impl.h>

DBO_INSTANTIATE_TEMPLATES(OrderDB);

OrderDB::OrderDB(std::string username,
             std::string companyname,
             double value,
             double delivery_cost,
             double distance,
             std::string address,
             double latitude, double longitude){
        this->username = username;
        this->companyname = companyname;
        this->value = value;
        this->delivery_cost = delivery_cost;
        this->distance = distance;
        this->address = address;
        this->latitude = latitude;
        this->longitude = longitude;
}
OrderDB::OrderDB(){
  username = "";
  companyname="";
  value =0;
  delivery_cost =0;
  distance =0;
  address="";
  latitude = 0;
  longitude = 0;
}


std::string OrderDB::get_username(){
    return username;
}
std::string OrderDB::get_companyname(){
    return companyname;
};
double OrderDB::get_value(){
    return value;
};
double OrderDB::get_delivery_cost(){
    return delivery_cost;
};
double OrderDB::get_distance(){
    return distance;
};


