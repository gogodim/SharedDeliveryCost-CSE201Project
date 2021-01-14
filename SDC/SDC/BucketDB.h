#ifndef BUCKET_H
#define BUCKET_H

#include "CompanyDB.h"
#include "OrderDBfirst.h"
#include <list>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <Wt/WApplication.h>


namespace dbo = Wt::Dbo;

class BucketDB{
public:
    BucketDB();
    BucketDB(std::string companyname,
             std::string orderIDs,
             double bucket_cur_amount,
             double bucket_cur_cost,
             double bucket_max_cost,
             bool bucket_completion,
             double lat,
             double lo);


    std::string companyname; // company of the bucket (in one bucket, there can only be one company)
    std::string orderIDs; // list of orders in the bucket
    double cur_amount; // total amount paid for all orders in the bucket
    double cur_cost; // current sum of delivery cost contributions of each user
    double max_cost; // total amount of delivery cost to pay (based on the company, and the current amount to pay for the orders)
    bool completion; // true if the optimization is complete, i.e bucket_max_cost==bucket_cur_cost
    double lat;
    double lo;
    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, companyname, "companyname");
        dbo::field(a, orderIDs,     "orderIDs");
        dbo::field(a, cur_amount,  "cur_amount");
        dbo::field(a, cur_cost, "cur_cost");
        dbo::field(a, max_cost,    "max_cost");
        dbo::field(a, completion,  "completion");
        dbo::field(a, lat,  "lat");
        dbo::field(a, lo,  "lo");
    }
};

#endif // BUCKET_H
