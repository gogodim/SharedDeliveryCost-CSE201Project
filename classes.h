#ifndef CLASSES_H
#define CLASSES_H
#include <string>
#include <list>
#include <vector>

#endif // CLASSES_H

class Coordinate{

public:

    Coordinate();

    Coordinate(int lat,int lo);

    double latitude;

    double longitude;

};

class User{

public:

    //we assume all login details are valid, the check is done before.

    User(std::string username,std::string password,std::string name,std::string surname,std::string address,std::string email,Coordinate coords);

    std::string username;

    std::string name;

    std::string surname;

    std::string address;

    std::string email;

    Coordinate coordinates;

private:

    std::string password;

};


class Company{

    // list of vectors of ints, each vector of the form:
    // ( minimum amount to pay, maximum amount, delivery fee for amounts in the interval [min_amount, max_mount])

    Company(std::string name, std::list<std::vector<int>> opts);

    std::string company_name;

    std::list<std::vector<int>> options;

};

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
private:
    User user;
    Company company;
    double value;
    double delivery_cost;
    double distance;
   
};

bool check_valid_email(std::string email);

bool check_valid_address(std::string address);

Coordinate convert_to_coordinates(std::string address);


