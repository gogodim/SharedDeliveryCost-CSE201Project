#include "BucketDB.h"

double delivery_cost(CompanyDB company,double amount){

    int v=company.options.size();

    for(int i=0; i<v; i++){
        if(amount<company.options[i][0] and amount>company.options[i][1]){
            return company.options[i][2];
        }
    }

    return 0;
}

BucketDB::BucketDB(){
    company=CompanyDB();
    std::list<OrderDBfirst> default_buckets; //empty list
    content=default_buckets;
    completion=false;
    max_cost=0;
    cur_amount=0;
    cur_cost=0;

}

BucketDB::BucketDB(CompanyDB company, std::list<OrderDBfirst> content,double cur_amount,double cur_cost,
               double max_cost,bool completion){


    this->company=company;
    this->content=content;
    this->completion=completion;
    this->max_cost=max_cost;
    this->cur_amount=cur_amount;
    this->cur_cost=cur_cost;
}

void BucketDB::find_and_remove(OrderDBfirst order){ //find an order equal to the input order and removes it from the bucket

    std::list<OrderDBfirst>::iterator i;
    std::list<OrderDBfirst>::iterator final;

    bool found=false;

    for(i=content.begin();i!=content.end();i++){

        if (*i==order){
            final=i;
            found=true;
            content.erase(final);
            break;
        }
    }

    if (found==true){ // if the order is removed, update all bucket data members

        double new_amnt=cur_amount-order.get_value();
        double new_cost=cur_cost-order.get_delivery_cost();
        double new_max=delivery_cost(company,new_amnt);

        cur_amount=new_amnt;
        cur_cost=new_cost;
        max_cost=new_max;

    }
}

void BucketDB::update_parameters(OrderDBfirst order){ //updates bucket parameters after deletion of the input order "order", the deletion is already done (bucket content updated)

    double new_amnt=cur_amount-order.get_value();
    double new_cost=cur_cost-order.get_delivery_cost();
    double new_max=delivery_cost(company,new_amnt);

    cur_amount=new_amnt;
    cur_cost=new_cost;
    max_cost=new_max;

}

void BucketDB::find_and_remove_order_list(std::list<OrderDBfirst> orders){

    std::list<OrderDBfirst>::iterator i;
    std::list<OrderDBfirst>::iterator s;

    for (i=orders.begin();i!=orders.end();i++){
        OrderDBfirst ord=*i;
        s=std::find(content.begin(), content.end(), ord); // return iterator at position of ord in content of bucket

    if (s != content.end()){ //true if ord has been found in bucket content

           content.erase(s); //remove the order in the bucket content
           update_parameters(ord); //update data members of bucket after removal of order

        }
    }

}

void BucketDB::add_order(OrderDBfirst order){

    if(order.get_company().name == company.name){
        //bol = True;
        //while(bol==True){
         //   for(command in bucket_content){
          //      if(radius_overlap(command,order)==False){
         //if(radius_overlap(bucket.area,order)){
             content.push_back(order);
             cur_cost+= order.get_delivery_cost();
             cur_amount+= order.get_value();
             max_cost= delivery_cost(company,cur_amount);
             match_delivery_cost(); // update the completion state and delivery costs of each user
             }
         }

bool  BucketDB::is_compatible(OrderDBfirst order){
    return true;
}

BucketDB copy(BucketDB other){ // crates a clone of the input Bucket

    return BucketDB( other.get_company(), other.get_content(),other.get_cur_amount(),other.get_cur_cost(),other.get_max_cost(), other.get_completion());
}

std::list<BucketDB> generate_buckets(OrderDBfirst new_order,std::list<BucketDB>& buckets){ // generates all valid bucket combinations of existing buckets with new_order

    std::list<BucketDB> res; // res will contain new combinations of buckets with new_order
    std::list<BucketDB>::iterator it;
    for (it = buckets.begin(); it != buckets.end(); it ++){
        BucketDB CurrentBucket = *it;
        if (CurrentBucket.is_compatible(new_order)){

            BucketDB NewBucket=copy(CurrentBucket);// copy the current bucket and add the new_order to the copy
            NewBucket.add_order(new_order);

            buckets.push_back(NewBucket); // update bucket list with the new combination
            res.push_back(NewBucket); // add the combination to res
        }
    }
    return res;
}



void BucketDB::match_delivery_cost(){

    double difference=cur_cost-max_cost;

    if (difference>=0){ //the bucket is overflowing, conditions are met, we just need to redistribute the shared delivery cost

        completion=true;
        cur_cost-=difference;

        double idv=difference/content.size();

        std::list<OrderDBfirst>::iterator i;

        for(i=content.begin();i!=content.end(); ++i) {
            i->delivery_cost-=idv;
        }
      }
}

bool compare(BucketDB b1,BucketDB b2){ // comparing buckets for sorting in the bucket list, "b1<b2" <=> "b1 has content length greater than b2"

    std::list<OrderDBfirst> c1=b1.get_content();
    std::list<OrderDBfirst> c2=b2.get_content();

    int l1=c1.size();
    int l2=c2.size();

    if (l1>l2){

        return true;
    }
    else{
        return false;
    }
}


std::tuple<bool,BucketDB, std::list<BucketDB>> processOrder(std::list<BucketDB> bucket_list, OrderDBfirst new_order){


    std::list<BucketDB> buckets_to_inspect = generate_buckets(new_order, bucket_list); // generate list of buckets that can satisfy the optimization problem
                                                                                    // these new buckets are the only interesting ones to look at, the other ones can't be complete

    buckets_to_inspect.sort(compare);//sort bucket_list in decreasing order of length

    std::list<BucketDB>::iterator i;

    BucketDB optimal_buc;// will store the optimal bucket, if found

    bool found=false;

    for (i=buckets_to_inspect.begin();i!=buckets_to_inspect.end();i++){
        BucketDB buc=*i;
        if (buc.get_completion()){ //take first completed bucket
            optimal_buc=buc;
            found=true;
            break;
        }
    }

    //removing orders in optimal_buc in all buckets in bucket list

    std::tuple<bool,BucketDB,std::list<BucketDB>> tpl; //tpl is a tuple that will contain the final output

    std::list<OrderDBfirst> orders_to_remove=optimal_buc.get_content();

    if (found==true){ // if an optimal bucket was found, there are orders to delete

     std::list<BucketDB> new_bucket_list;

    for (i=bucket_list.begin();i!=bucket_list.end();i++){
        BucketDB buc=*i;
        buc.find_and_remove_order_list(orders_to_remove);
        if (buc.get_content().size()>0){
            new_bucket_list.push_back(buc);
        }

     }

    tpl=make_tuple(true,optimal_buc,new_bucket_list);
  }

   else{

     tpl=make_tuple(false,optimal_buc,bucket_list);

    }

    return tpl;
}
