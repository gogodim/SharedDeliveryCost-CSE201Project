#include "User.h"
#include "Order.h"
#include <string>
#include "Database.h"

//User Constructor
User::User(){
    username = "Default User";
    name = "";
    surname = "";
    email = "";
    address = "";
}

User::User(std::string username,
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
    //set_coordinates(coordinate_from_address(address));
};

// User, Gettters
Address User::get_useraddress(){
    return this->useraddress;
}
std::string User::get_username(){
    return this->username;
}
std::string User::get_password(){
    return this->password;
};
std::string User::get_name(){
    return this->name;
};
std::string User::get_surname(){
    return this->surname;
};
std::string User::get_address(){
    return this->address;
};
std::string User::get_email(){
    return this->email;
};
Coordinate User::get_coordinates(){
    return this->coordinates;
};

std::string User::get_password() const{
    return this->password;
}

std::string User::get_username() const{
    return this->username;
}

//User, Setters
void User::set_username(std::string username){
    this->username = username;
}
std::hash <std::string> hash;

void User::set_password(std::string password){
    this->password = std::to_string(hash(password));
}
void User::set_name(std::string name){
    this->name = name;
}
void User::set_surname(std::string surname){
    this->surname = surname;
}
void User::set_address(std::string address){
    this->address = address;
}
void User::set_email(std::string email){
    this->email = email;
}
void User::set_useraddress(Address add){
    this->useraddress.set_postalcode(add.get_postalcode());
    this->useraddress.set_city(add.get_city());
    this->useraddress.set_street(add.get_street());
}
void User::set_coordinates(Coordinate coordinates){
    this->coordinates = coordinates;
}

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
