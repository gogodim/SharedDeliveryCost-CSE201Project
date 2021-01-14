#ifndef CLASSES_H
#define CLASSES_H
#include <string>
#include <list>
#include <vector>
#include <Coordinate.h>

using namespace std;



class User{
public:
    //we assume all login details are valid, the check is done before.
    User();
    User(std::string username,
         std::string password,
         std::string name,
         std::string surname,
         Coordinate adresss,
         std::string email);

    std::string get_username();
    std::string get_password();
    std::string get_name();
    std::string get_surname();
    Coordinate get_address();
    std::string get_email();

    void set_username(std::string n);
    void set_password(std::string n);
    void set_name(std::string n);
    void set_surname(std::string n);
    void set_address(Coordinate n);
    void set_email(std::string n);

private:
    std::string username;
    std::string password;
    std::string name;
    std::string surname;
    Coordinate address;
    std::string email;

};


class Company{
public:

    // list of vectors of doubles, each vector of the form:
    // ( minimum amount to pay, maximum amount, delivery fee for amounts in the interval [min_amount, max_mount])

    Company(string name, vector<vector<double> > opts);
    Company();
    std::string get_name();
    vector<vector<double>> get_options();
    void set_options(vector<vector<double> > options);
    void set_name(string name);
private:
    string name;
    vector<vector<double> > options;

};

class Order{
public:
    Order(int orderID,
          User user,
          Company company,
          double value,
          double delivery_cost,
          double distance, // in meters
          Coordinate address = Coordinate());
    int orderID;
    User get_user();
    Company get_company();
    double get_value();
    double get_delivery_cost();
    double get_distance();
    double get_to_pay();
    void set_to_pay(double amount);
    bool operator==(Order other);
    double to_pay;

private:
    User user;
    //final amount to pay for the delivery (once the optimization is solved)
    Company company;
    double value;
    double delivery_cost;
    double distance;
    Coordinate address;
};


double array_of_one_delivery();

Coordinate distance_optimization(double array);


class Bucket{
public:
    Bucket();
    Bucket(Company company,
           list<Order> content,
           double bucket_cur_amount,
           double bucket_cur_cost,
           double bucket_max_cost,
           bool bucket_completion,
           Coordinate inter);
    tuple<bool,Coordinate> is_compatible(Order new_order);

    void add_order(Order order,Coordinate inter=Coordinate()); // adds valid order in bucket_content and updates all data members accordingly
                                                  // also updates the intersection_point with inter

    void match_delivery_cost();//Checks if the contribution of delivery cost of the new order doesn't overflow the max_cost, and distribute the cost
                               // Function is applied after the order has been added to the bucket, to redistribute the cost in the case of an overflow
                              //and update the bucket completion


    void find_and_remove(Order order); //find an order equal to the input order and removes it from the bucket
    void find_and_remove_order_list(list<Order> orders); // remove elements in bucket content that belong to the input list "orders"
    void update_parameters(Order order); // update bucket params after removal of input order "order" (the removal is done prior to the function call)
    void print();
    bool operator==(Bucket other);
    //setters

    void set_company(Company comp){
        company=comp;
    }
    void set_completion(bool b){
        completion=b;
    }
    void set_max_cost(double v){
        max_cost=v;
    }
    void set_cur_cost(double v){
        cur_cost=v;
    }
    void set_cur_amount(double v){
        cur_amount=v;
    }

    void set_intersection_point(Coordinate coord){
        intersection_point=coord;
    }

    //getters

    std::list<Order> get_content(){
        return content;
    }
    Company get_company(){
        return company;
    }
    bool get_completion(){

        return completion;
    }
    double get_max_cost(){
        return max_cost;
    }
    double get_cur_cost(){

        return cur_cost;
    }
    double get_cur_amount(){

        return cur_amount;
    }

    Coordinate get_intersection_point(){

        return intersection_point;
    }

private:

    Company company; // company of the bucket (in one bucket, there can only be one company)
    std::list<Order> content; // list of orders in the bucket
    double cur_amount; // total amount paid for all orders in the bucket
    double cur_cost; // current sum of delivery cost contributions of each user
    double max_cost; // total amount of delivery cost to pay (based on the company, and the current amount to pay for the orders)
    bool completion; // true if the optimization is complete, i.e bucket_max_cost==bucket_cur_cost
    Coordinate intersection_point;
};

void print_bucket_list(list<Bucket> buc_list);

Bucket copy(Bucket other);

bool compare(Bucket b1,Bucket b2);

std::list<Bucket> generate_buckets(Order new_order,list<Bucket>& buckets); // generates all valid bucket combinations of existing buckets with new_order

bool radius_overlap(Order order1, Order order2); // True if there exists a common area between two orders/users

double delivery_cost(Company company,double amount); // returns the delivery cost associated to an order amount, given a company

tuple<bool,Bucket,list<Bucket>,string> processOrder(list<Bucket> bucketList, Order newOrder);
// final optimization function, returns a triple of the form (found, optimal_buc,updated_bucket_list)
// found==true if an optimization bundle exists,
// optimal_buc is the bucket grouping orders satifying this optimization (it could be empty)
// updated_bucket_list is the bucket_list obtained after removing orders of optimal_buc from buckets of bucket_list


//----------------Circle Intersection------------------------

//struct boolPoint
//{
//   Coordinate p;
//   bool has_intersection;
//};

class boolPoint{

public:
    boolPoint();
    boolPoint(Coordinate p,bool has_intersection);
    Coordinate p;
    bool has_intersection;
};


double* convert_to_meters(Coordinate C);

Coordinate convert_to_coordinates(double* array);

std::vector<Coordinate> get_intersection(Order Order1, Order Order2);

bool check_if_inside(Order Order1, Order Order2);

boolPoint check_if_bucket (std::vector<Order> order_vector);
#endif // CLASSES_H
