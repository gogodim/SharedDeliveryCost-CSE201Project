#include "classes.h"
#include <math.h>

Coordinate::Coordinate(double lat, double lo){

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




//Order::Order(User user,
//             Company company,
//             double value,
//             double delivery_cost,
//             double distance){
//        this->user = user;
//        this->company = company;
//        this->value = value;
//        this->delivery_cost = delivery_cost;
//        this->distance = distance;
//}

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

double Coordinate::get_distance(Coordinate other){

    const int R=6371; //radius of the earth in km
    const double PI=3.14159265358;
    // all angles converted to radians
    double lat1=latitude*PI/180;
    double lon1=longitude*PI/180;
    double lat2=other.latitude*PI/180;
    double lon2=other.longitude*PI/180;

    double latDist = (lat2 - lat1);
    double lonDist =(lon2 - lon1);

    double a = sin(latDist/2) * sin(latDist/2) + cos(lat1) * cos(lat2)* sin(lonDist / 2) * sin(lonDist / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    return distance; // in km


}

Bucket::Bucket(){
    bucket_company="None";
    std::list<Order> default_buckets; //empty list
    bucket_content=default_buckets;
    bucket_completion=false;
    bucket_max_cost=0;
    bucket_cur_amount=0;
    bucket_cur_cost=0;

}

void Bucket::set_company(std::string company){

    bucket_company=company;
}



