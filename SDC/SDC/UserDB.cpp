#include "UserDB.h"
#include "OrderDBfirst.h"
#include <string>
#include "Database.h"

//User Constructor
UserDB::UserDB(){
    username = "Default User";
    name = "";
    surname = "";
    email = "";
    address = "";
}

UserDB::UserDB(std::string username,
           std::string password,
           std::string name,
           std::string surname,
           std::string address,
           std::string email){
    this->username = username;
    this->name = name;
    this->surname = surname;
    this->email = email;
    this->address = address;
    this->password = password;
    set_coordinates(coordinate_from_address(address));
};

// User, Gettters
std::string UserDB::get_username(){
    return this->username;
}
std::string UserDB::get_password(){
    return this->password;
};
std::string UserDB::get_name(){
    return this->name;
};
std::string UserDB::get_surname(){
    return this->surname;
};
std::string UserDB::get_address(){
    return this->address;
};
std::string UserDB::get_email(){
    return this->email;
};
Coordinate UserDB::get_coordinates(){
    return this->coordinates;
};

std::string UserDB::get_password() const{
    return this->password;
}

std::string UserDB::get_address_second() const{
    return this->address;
}


//User, Setters
void UserDB::set_username(std::string username){
    this->username = username;
}
std::hash <std::string> hash;

void UserDB::set_password(std::string password){
    this->password = std::to_string(hash(password));
};
void UserDB::set_name(std::string name){
    this->name = name;
};
void UserDB::set_surname(std::string surname){
    this->surname = surname;
};
void UserDB::set_address(std::string address){
    this->address = address;
};
void UserDB::set_email(std::string email){
    this->email = email;
};
void UserDB::set_coordinates(Coordinate coordinates){
    this->coordinates = coordinates;
};

/*double array_of_one_delivery(){ // This function creates the array of all the orders concerned by the delivery, idk how to do it because linked to the database?
    double arr = 0;
    Coordinate c = order.get_user().get_coordinates();
    double weight = order.get_delivery_cost(); //or get_value()?

};*/


/*Coordinate distance_optimization(double array_of_one_delivery()){  //arr has elements of type (lat, lon, weight) and it is the array of all the orders concerned by this delivery
    double lat = 0;
    double lon = 0;
    for(int i;array_of_one_delivery().size(); i++){
        if(i!=()){
            lat = lat + i[0]*i[2];
            lon = lon + i[1]*i[2];
        };

    };
    return Coordinate(lat/array_of_one_delivery().size(),lon/array_of_one_delivery().size());
};*/
