#ifndef BUCKET_H
#define BUCKET_H

#include "Company.h"
#include "Order.h"
#include <list>

class Bucket{
public:
    Bucket();
    Bucket(Company company, std::list<Order> content,double bucket_cur_amount,double bucket_cur_cost,double bucket_max_cost,bool bucket_completion);
    bool is_compatible(Order order);
    void add_order(Order order); // adds valid order in bucket_content and updates all data members accordingly
    void match_delivery_cost();//Checks if the contribution of delivery cost of the new order doesn't overflow the max_cost, and distribute the cost
                               // Function is applied after the order has been added to the bucket, to redistribute the cost in the case of an overflow
                              //and update the bucket completion

    // functions to modify bucket content
    void append_to_content(Order order){
        content.push_back(order);
    }
    void find_and_remove(Order order); //find an order equal to the input order and removes it from the bucket
    void find_and_remove_order_list(std::list<Order> orders); // remove elements in bucket content that belong to the input list "orders"
    void update_parameters(Order order); // update bucket params after removal of input order "order" (the removal is done prior to the function call)

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

private:

    Company company; // company of the bucket (in one bucket, there can only be one company)
    std::list<Order> content; // list of orders in the bucket
    double cur_amount; // total amount paid for all orders in the bucket
    double cur_cost; // current sum of delivery cost contributions of each user
    double max_cost; // total amount of delivery cost to pay (based on the company, and the current amount to pay for the orders)
    bool completion; // true if the optimization is complete, i.e bucket_max_cost==bucket_cur_cost

};

/*Bucket copy(Bucket other);

std::list<Bucket> generate_buckets(Order new_order,std::list<Bucket> buckets); // generates all valid bucket combinations of existing buckets with new_order

bool radius_overlap(Order order1, Order order2); // True if there exists a common area between two orders/users

double delivery_cost(Company company,double amount); // returns the delivery cost associated to an order amount, given a company

std::tuple<bool,std::list<Bucket>> processOrder(std::vector<Company> companyList, std::vector<Bucket> bucketList, Order newOrder);*/

#endif // BUCKET_H
