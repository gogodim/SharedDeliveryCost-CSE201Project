#include "classes.h"

Coordinate::Coordinate(int lat, int lo){

latitude=lat;
longitude=lo;

}

Coordinate::Coordinate(){

latitude=0;
longitude=0;

}

User::User(std::string username,std::string password,std::string name,std::string surname,std::string address,std::string email,Coordinate coords){
 ;
}


Company::Company(std::string name, std::list<std::vector<int>> opts){
    this->name = name;
    this->options = opts;
}

Company::Company(){
    this->name = "Default Company";
    this->options = std::list<std::vector<int>>();
}

void Company::set_options(std::list<std::vector<int>> options){
    this->options = options;
}

void Company::set_name(std::string name)
{
	this->name = name; 
}

bool check_valid_email(std::string email){
    return true;
}

bool check_valid_address(std::string address){
    return true;
}




Order::Order(User user,
             Company company,
             double value,
             double delivery_cost,
             double distance){
        this->user = user;
        this->company = company;
        this->value = value;
        this->delivery_cost = delivery_cost;
        this->distance = distance;
}

    User Order::get_user(){
        return user;
    }
    Company Order::get_company(){
        return company;
    };
    double Order::get_value(){
        return value;
    };
    double Order::get_delivery_cost(){
        return delivery_cost;
    };
    double Order::get_distance(){
        return distance;
    };

Coordinate convert_to_coordinates(std::string address){

    return Coordinate(0,0);
}

