#include "BucketDB.h"


BucketDB::BucketDB(){
    companyname="";
    orderIDs="";
    completion=false;
    max_cost=0;
    cur_amount=0;
    cur_cost=0;
    lat=0;
    lo=0;

}

BucketDB::BucketDB(std::string companyname, std::string orderIDs,double cur_amount,double cur_cost,
               double max_cost,bool completion,double lat,double lo){


    this->companyname=companyname;
    this->orderIDs=orderIDs;
    this->completion=completion;
    this->max_cost=max_cost;
    this->cur_amount=cur_amount;
    this->cur_cost=cur_cost;
    this->lat=lat;
    this->lo=lo;
}
