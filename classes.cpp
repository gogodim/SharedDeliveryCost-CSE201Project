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
    ;
}

bool check_valid_email(std::string email){
    return true;
}

bool check_valid_address(std::string address){
    return true;
}

Coordinate convert_to_coordinates(std::string address){

    return Coordinate(0,0);
}

