#ifndef USER_H
#define USER_H

#include <string>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <Wt/WApplication.h>

#include "Coordinate.h"

namespace dbo = Wt::Dbo;

class User {
public:
    /*Constructors*/
    User();
    User(const User &u){
        this->username    = u.username;
        this->password    = u.password;
        this->name        = u.name;
        this->surname     = u.surname;
        this->email       = u.email;
        this->address     = u.address;
        //Three element: 91120, Palaiseau, Avenue Henri Becquerel 103

        this->coordinates = u.coordinates;
    };
    User(std::string username,
             std::string password,
             std::string name,
             std::string surname,
             std::string adresss,
             std::string email);

    /*get_information function*/
    std::string get_username();
    std::string get_password();
    std::string get_name();
    std::string get_surname();
    std::string get_address();
    std::string get_email();
    Coordinate get_coordinates();

    std::string get_password()const;
    std::string get_address_second()const;

    void set_username(std::string n);
    void set_password(std::string n);
    void set_name(std::string n);
    void set_surname(std::string n);
    void set_address(std::string n);
    void set_email(std::string n);
    void set_coordinates(Coordinate coord);
    void Address2Coordinate(std::string address);
    void Coordinate2Address(Coordinate coord);


    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, username, "username");
        dbo::field(a, name,     "name");
        dbo::field(a, surname,  "surname");
        dbo::field(a, password, "password");
        dbo::field(a, email,    "email");
        dbo::field(a, address,  "address");
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user){
        os << user.name << " is user's name";
        return os;
    }

private:
    std::string  username;
    std::string  password;
    std::string  name;
    std::string  surname;
    std::string  email;
    std::string  address;
    Coordinate   coordinates;

};

/*bool check_valid_email(std::string email);

bool check_valid_address(std::string address);

double array_of_one_delivery();

Coordinate distance_optimization(double array);

Coordinate convert_to_coordinates(std::string address);*/

#endif // USER_H
