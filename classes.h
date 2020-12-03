#ifndef CLASSES_H
#define CLASSES_H
#include <string>
#include <list>
#include <vector>

#endif // CLASSES_H



class Coordinate{

public:

    Coordinate();

    Coordinate(double lat,double lo);

    double get_distance( Coordinate other);

    double latitude; //given in degrees (western latitudes are negative angles)

    double longitude; // given in degrees (southern longtidues are negative angles)

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
public:

    // list of vectors of ints, each vector of the form:
    // ( minimum amount to pay, maximum amount, delivery fee for amounts in the interval [min_amount, max_mount])

    Company(std::string name, std::list<std::vector<int>> opts);
    Company();
    void set_options(std::list<std::vector<int>> options);
    void set_name(std::string name);
private:
    std::string name;

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

class Bucket{

    Bucket();
    void set_company(std::string company);

    std::string bucket_company; // company ID (in one bucket, there can only be one company)
    std::list<Order> bucket_content; // list of orders in the bucket
    double bucket_cur_amount; // total amount paid for all orders in the bucket
    double bucket_cur_cost; // current sum of delivery cost contributions of each user
    double bucket_max_cost; // total amount of delivery cost to pay (based on the company, and the current amount to pay for the orders)
    bool bucket_completion; // true if the optimization is complete, i.e bucket_max_cost==bucket_cur_cost

    bool is_compatible(Order order);
    void add_order(Order order); // adds valid order in bucket_content and updates all data members accordingly

};

std::list<Bucket> generate_buckets(Order new_order,std::list<Bucket> buckets); // generates all valid bucket combinations of existing buckets with new_order

bool radius_overlap(Order order1, Order order2); // True if there exists a common area between two orders/users

bool match_delivery_cost(Bucket bucket, Order new_order); //True if the contribution of delivery cost of the new order doesn't overflow the max_cost
