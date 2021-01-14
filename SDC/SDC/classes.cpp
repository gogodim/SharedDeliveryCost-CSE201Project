# include "classes.h"
# include <math.h>
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>


//-----------------------------User--------------------------------

//User Constructor
User::User(){
    username = "Default User";
    name = "";
    surname = "";
    email = "";
    address = Coordinate();
}
User::User(std::string username,
           std::string password,
           std::string name,
           std::string surname,
           Coordinate address,
           std::string email){
    this->username = username;
    this->name = name;
    this->surname = surname;
    this->email = email;
    this->address = address;
    this->password = password;
};

// User, Gettters
std::string User::get_username(){
    return username;
}
std::string User::get_password(){
    return password;
};
std::string User::get_name(){
    return name;
};
std::string User::get_surname(){
    return surname;
};
Coordinate User::get_address(){
    return address;
};
std::string User::get_email(){
    return email;
};

//User, Setters
void User::set_username(std::string username){
    this->username = username;
}
void User::set_password(std::string password){
    this->password = password;
};
void User::set_name(std::string name){
    this->name = name;
};
void User::set_surname(std::string surname){
    this->surname = surname;
};
void User::set_address(Coordinate address){
    this->address = address;
};
void User::set_email(std::string email){
    this->email = email;
};


//-------------------------Company-------------------------------

Company::Company(std::string name, std::vector<std::vector<double>> opts){
    this->name = name;
    this->options = opts;
}
Company::Company(){
    this->name = "Default Company";
    this->options = std::vector<std::vector<double>>();
}

std::string Company::get_name(){
    return name;
}
vector<vector<double> > Company::get_options(){
    return options;
}

void Company::set_options(std::vector<std::vector<double>> options){
    this->options = options;
}
void Company::set_name(std::string name){
    this->name = name;
}

//---------Order-----------

Order::Order(int orderID,
             User user,
             Company company,
             double value,
             double delivery_cost,
             double distance,
             Coordinate address){
        to_pay=0;
        this->orderID = orderID;
        this->user = user;
        this->company = company;
        this->value = value;
        this->delivery_cost = delivery_cost;
        this->distance = distance; // in meters
        if (address == Coordinate()){ //if another address isn't given, we use the default address
            this->address = user.get_address();}
        else {
            this->address = address;}
}

bool Order::operator==(Order other){ // we assume orders are equal when the user's identity and company choice are the same
                                    // we assume the user will always group his orders for one company in a single order

    //name_comparison
    std::string name=user.get_username();
    std::string other_name=other.user.get_username();

    bool a=(name==other_name);

    //company_comparison
    std::string comp= company.get_name();
    std::string other_comp=other.company.get_name();

    bool b=(comp==other_comp);

    //address comparison

    bool c=(address==other.address);

    return a&&b&&c;

}

    User Order::get_user(){
        return user;
    }
    Company Order::get_company(){
        return company;
    };
    double Order::get_value(){
        return value;
    };
    double Order::get_delivery_cost(){
        return delivery_cost;
    };
    double Order::get_distance(){
        return distance;
    };
    double Order::get_to_pay(){
        return to_pay;
    }

    void Order::set_to_pay(double amount){
        to_pay = amount;
    }

//---------------------Bucket--------------------------

Bucket::Bucket(){
    company=Company();
    std::list<Order> default_buckets; //empty list
    content=default_buckets;
    completion=false;
    max_cost=0;
    cur_amount=0;
    cur_cost=0;
    intersection_point=Coordinate();

}

Bucket::Bucket(Company company, std::list<Order> content,double cur_amount,double cur_cost,
               double max_cost,bool completion,Coordinate inter){


    this->company=company;
    this->content=content;
    this->completion=completion;
    this->max_cost=max_cost;
    this->cur_amount=cur_amount;
    this->cur_cost=cur_cost;
    this->intersection_point=inter;
}

bool Bucket::operator==(Bucket other){ // 2 buckets are equal when their contents are equal, we know that their contents are sorted based on willingness of delivery
    list<Order>::iterator i;

    if (other.content.size()!=content.size()){
        return false;
    }

    // build vectors from content and other.content

    vector<Order> v1;
    vector<Order> v2;

    for (i=content.begin();i!=content.end();i++){
        v1.push_back(*i);
    }

    for (i=other.content.begin();i!=other.content.end();i++){
        v2.push_back(*i);
    }

    // compare entries one by one (knowing that the contents are sorted)

    int max=v1.size();
    bool found=true;

    int j;
    for (j=0;j<max;j++){

        if ((v1[j]==v2[j])==false){ // we found an entry that doesn't match, the buckets cannot be equal
            found=false;
        }
    }
    return found;
}

void Bucket::print(){

    if(content.size()>0){

    list<Order>::iterator iter2;

    cout << "\n"<<"Current cost:"<< cur_cost << "\n";
    cout << "Max cost:"<< max_cost << "\n";

    if(intersection_point==Coordinate(0,0)){

    cout << "Meeting point: nowhere"<<"\n";

    }
    else{
    cout << "Meeting point:"<< "with lat " << intersection_point.get_latitude() << " and lon "<<intersection_point.get_longitude()<<"\n";
    }

    for (iter2=content.begin();iter2!=content.end();iter2++){

        Order order=*iter2;
        cout << "User " << order.get_user().get_name() << " will pay "<< order.get_to_pay() << "\n";
    }

    }
    else{
         cout<<"Empty Bucket"<<"\n";
    }
}

//void Bucket::find_and_remove(Order order){ //find an order equal to the input order and removes it from the bucket

//    std::list<Order>::iterator i;
//    std::list<Order>::iterator final;

//    bool found=false;

//    for(i=content.begin();i!=content.end();i++){

//        if (*i==order){
//            final=i;
//            found=true;
//            content.erase(final);
//            break;
//        }
//    }

//    if (found==true){ // if the order is removed, update all bucket data members

//        double new_amnt=cur_amount-order.get_value();
//        double new_cost=cur_cost-order.get_delivery_cost();
//        double new_max=delivery_cost(company,new_amnt);

//        cur_amount=new_amnt;
//        cur_cost=new_cost;
//        max_cost=new_max;

//    }
//}

void Bucket::update_parameters(Order order){ //updates bucket parameters after deletion of the input order "order", the deletion is already done (bucket content updated)

    double new_amnt=cur_amount-order.get_value();
    double new_cost=cur_cost-order.get_delivery_cost();
    double new_max=delivery_cost(company,new_amnt);

    cur_amount=new_amnt;
    cur_cost=new_cost;
    max_cost=new_max;
    intersection_point=Coordinate();

}

void Bucket::find_and_remove_order_list(list<Order> orders){

    list<Order>::iterator i;
    list<Order>::iterator s;

    for (i=orders.begin();i!=orders.end();i++){
        Order ord=*i;
        s=std::find(content.begin(), content.end(), ord); // return iterator at position of ord in content of bucket

    if (s != content.end()){ //true if ord has been found in bucket content

           content.erase(s); //remove the order in the bucket content
           update_parameters(ord); //update data members of bucket after removal of order

        }
    }

}


bool compare_willingness(Order order1, Order order2){

    if (order1.get_delivery_cost()==order2.get_delivery_cost()){ // if both have the same willingness

        return order1.get_user().get_name()<order1.get_user().get_name(); // sort by alphabetical order of first name
    }

    return order1.get_delivery_cost()<order2.get_delivery_cost();
}

void Bucket::match_delivery_cost(){

    double difference=cur_cost-max_cost;

    if (difference>=0){ //the bucket is overflowing, conditions are met, we just need to redistribute the shared delivery cost

        completion=true;
        cur_cost-=difference;

        double idv=difference/content.size(); // the difference will be removed in equal parts (idv) among the users
        double extra=0;

        list<Order>::iterator i;

        //content.sort(compare_willingness);

        for(i = content.begin(); i != content.end(); ++i) { // we iterate through the orders of the bucket

            Order ord=*i;

            double q=ord.get_delivery_cost() - idv; // remove the individual difference

            // q will be the final cost to pay for the order, if q is positive

            if (q>=0){

                double new_q=q+extra;

                if (new_q>=0){
                    i->to_pay=new_q;
                    extra=0;
                }
                else{
                    i->to_pay=q;
                }

            }
            else{

                extra+=q;
                i->to_pay=0;

            }

        }

      }
}

void Bucket::add_order(Order order,Coordinate inter){

             intersection_point=inter; // sets new intersection point
             content.push_back(order);
             company=order.get_company();
             cur_cost+= order.get_delivery_cost();
             cur_amount+= order.get_value();
             max_cost= delivery_cost(company,cur_amount);
             content.sort(compare_willingness);
             match_delivery_cost();
}

tuple<bool,Coordinate>  Bucket::is_compatible(Order new_order){

    //----------- checking company---------------


    tuple<bool,Coordinate> tpl=make_tuple(false,Coordinate());

    if(new_order.get_company().get_name() == company.get_name()){ // if the order is from the same company as the bucket

        //----------- checking intersection---------------

        bool inter; // inter will be true if the intersection exists

        vector<Order> order_vector;
        list<Order>::iterator i;

        for (i=content.begin();i!=content.end();i++){

            order_vector.push_back(*i);
        }

        order_vector.push_back(new_order); // create order vector that contains the current bucket content + new order

        boolPoint bp=check_if_bucket(order_vector); // return an intersection point based on the addition of the new order

        inter=bp.has_intersection; //  sets inter

        if (inter){ // if inter is true <=> the intersection point exists

            Coordinate coord=bp.p; // coord will be used in generate_buckets to set the bucket intersection point

            tuple<bool,Coordinate> tpl2=make_tuple(inter,coord);

            return tpl2;
        }

        else{
            return tpl;
        }
    }

    else{

        return tpl;
    }
}


void print_bucket_list(list<Bucket> buc_list){

    int cnt=0;

    list<Bucket>::iterator iter;

    for (iter=buc_list.begin();iter!=buc_list.end();iter++){

                cnt+=1;

                Bucket buc=*iter;

                cout << "Bucket " << cnt << " :";

                buc.print();

            }
}

Bucket copy(Bucket other){ // crates a clone of the input Bucket

    return Bucket( other.get_company(), other.get_content(),other.get_cur_amount(),other.get_cur_cost(),other.get_max_cost(), other.get_completion(),other.get_intersection_point());
}

list<Bucket> generate_buckets(Order new_order,list<Bucket>& buckets){ // generates all valid bucket combinations of existing buckets with new_order

    list<Bucket> res; // res will contain new combinations of buckets with new_order
    list<Bucket>::iterator it;

    // first, we create and add the bucket made only of new_order

     Bucket B=Bucket();
     B.add_order(new_order); // adds new_order to an empty bucket B (with no intersection)
     res.push_back(B);

     // iterate through existing list of buckets to see if new_order can be added

    for (it = buckets.begin(); it != buckets.end(); it++){
        Bucket CurrentBucket = *it;

        tuple<bool, Coordinate> tpl=CurrentBucket.is_compatible(new_order);

        bool compat=get<0>(tpl); // get first entry of tuple (true if there exists an intersection)

        if (compat){

            Bucket NewBucket=copy(CurrentBucket);// copy the current bucket and add the new_order to the copy

            Coordinate coord=get<1>(tpl); //get second entry of tuple (coordinate of intersection_point)

            NewBucket.add_order(new_order,coord); // update NewBucket by adding the new_order

            res.push_back(NewBucket); // add the combination to res
        }
    }

    for (it = res.begin(); it != res.end(); it++){ // update initial bucket list with the new combinations
        buckets.push_back(*it);
    }
    return res;
}


double delivery_cost(Company company,double amount){

    int v = company.get_options().size();

    for(int i=0; i<v; i++){
        if(amount > company.get_options()[i][0] and amount < company.get_options()[i][1]){
            return company.get_options()[i][2];
        }
    }

    return 0;
}


//double array_of_one_delivery(){ // This function creates the array of all the orders concerned by the delivery, idk how to do it because linked to the database?
//    double arr = 0;
//    Coordinate c = order.get_user().get_coordinates();
//    double weight = order.get_delivery_cost(); //or get_value()?

//};


//Coordinate distance_optimization(double array_of_one_delivery()){  //arr has elements of type (lat, lon, weight) and it is the array of all the orders concerned by this delivery
//    double lat = 0;
//    double lon = 0;
//    for(int i;array_of_one_delivery().size(); i++){
//        if(i!=()){
//            lat = lat + i[0]*i[2];
//            lon = lon + i[1]*i[2];
//        };

//    };
//    return Coordinate(lat/array_of_one_delivery().size(),lon/array_of_one_delivery().size());
//};

bool compare(Bucket b1,Bucket b2){ // comparing buckets for sorting in the bucket list, "b1<b2" <=> "b1 has content length greater than b2"

    list<Order> c1=b1.get_content();
    list<Order> c2=b2.get_content();

    int l1=c1.size();
    int l2=c2.size();

    if (l1>l2){

        return true;
    }
    else{
        return false;
    }
}

tuple<bool,Bucket,list<Bucket>,string> processOrder(list<Bucket> bucket_list, Order new_order){


    std::list<Bucket> buckets_to_inspect=generate_buckets(new_order, bucket_list); // generate list of buckets that can satisfy the optimization problem
                                                                                        // these new buckets are the only interesting ones to look at, the other ones can't be complete

    string final_link="No link available"; // final link will send us to a google maps page where the users can see the intersection

    buckets_to_inspect.sort(compare);//sort bucket_list in decreasing order of length

    std::list<Bucket>::iterator i;

    std::list<Bucket>::iterator it;

    Bucket optimal_buc;// will store the optimal bucket, if found

    bool found=false;

    for (i=buckets_to_inspect.begin();i!=buckets_to_inspect.end();i++){
        Bucket buc=*i;
        if (buc.get_completion()){ //take first completed bucket
            optimal_buc=buc;
            found=true;
            break;
        }
    }

    //removing orders in optimal_buc in all buckets in bucket list

    tuple<bool,Bucket,list<Bucket>,string> tpl; //tpl is a tuple that will contain the final output

    list<Order> orders_to_remove=optimal_buc.get_content();

    if (found==true){ // if an optimal bucket was found, there are orders to delete

     list<Bucket> new_bucket_list;

    for (i=bucket_list.begin();i!=bucket_list.end();i++){
        Bucket buc=*i;
        buc.find_and_remove_order_list(orders_to_remove);
        if (buc.get_content().size()>0){

            bool push=true; // we now check for duplicates
            for (it=new_bucket_list.begin();it!=new_bucket_list.end();it++){ // seeing if the obtained bucket is already in the bucket list
                Bucket buc2=*it;
                if (buc2==buc){
                    push=false;
                    break;
                }
            }
            if (push){ // if buc is not already in the new list, we can add it
            new_bucket_list.push_back(buc);
            }
        }
    }

    string lat=to_string(optimal_buc.get_intersection_point().get_latitude());
    string lon=to_string(optimal_buc.get_intersection_point().get_longitude());

    final_link="http://www.google.com/maps/place/"+lat+","+lon;
    tpl=make_tuple(true,optimal_buc,new_bucket_list, final_link);
  }

   else{

     tpl=make_tuple(false,optimal_buc,bucket_list,final_link); // in this case, optimal buc is empty

    }

    return tpl;
}

//------------------Circle Intersection-------------------- (all distances are in meters)


boolPoint::boolPoint(){

    has_intersection=false;
    p=Coordinate();

}

boolPoint::boolPoint(Coordinate s, bool has_inter){
    p=s;
    has_intersection=has_inter;
}


double* convert_to_meters(Coordinate C)
{
    double y=C.get_latitude()*111000;
    double x=C.get_longitude()*111000*cos(C.get_latitude()*M_PI/180);
    static double array [2] = { x, y };

    return array;
}

 Coordinate convert_to_coordinates(double* array)
{
    double latitude=array[1]/111000;
    double longitude=array[0]/(111000*cos(latitude*M_PI/180));
    return Coordinate (latitude, longitude);
}

 std::vector<Coordinate> get_intersection(Order Order1, Order Order2){
// this function is the mathematical way to get the intersection of the radius between two orders, this is necessary in order for the next one to be able to take in a vector of orders, and say wether or not they can all fit in one bucket.
    Coordinate C1= Order1.get_user().get_address();
    Coordinate C2= Order2.get_user().get_address();
    //double* c1= convert_to_meters(C1);
    double y1=C1.get_latitude()*111000;
    double x1=C1.get_longitude()*111000*cos(C1.get_latitude()*M_PI/180);
    double y2=C2.get_latitude()*111000;
    double x2=C2.get_longitude()*111000*cos(C2.get_latitude()*M_PI/180);

    //double* c2= convert_to_meters(C2);
    double r1=Order1.get_distance();
    double r2=Order2.get_distance();
    double d= C1.get_distance(C2);
    if (d > r1+ r2){
        return std::vector<Coordinate>();}

    if (d<=abs(r1-r2)){
        return std::vector<Coordinate>();}
    double a=(r1*r1-r2*r2+d*d)/(2*d);
    double h=sqrt(r1*r1-a*a);
    double b=d-a;
    double c3x= x1 + a*( x2 - x1 )/d;
    double c3y= y1 + a*( y2 - y1 )/d;
    double c4x = c3x + h*(y2 -y1) /d;
    double c4y = c3y - h*( x2 - x1 )/d;
    double c5x = c3x - h*(y2 -y1) /d;
    double c5y = c3y + h*( x2 - x1 )/d;
    double c4[2]={c4x, c4y};
    double c5[2]={c5x, c5y};

    Coordinate Intersection1= convert_to_coordinates(c4);
    Coordinate Intersection2= convert_to_coordinates(c5);
    std::vector<Coordinate> vect;
    vect.push_back(Intersection1);
    vect.push_back(Intersection2);
    return vect;
}

bool check_if_inside(Order Order1, Order Order2){ // this one simply checks if an order is inside another order when there is no intersection.

    Coordinate C1= Order1.get_user().get_address();
    Coordinate C2= Order2.get_user().get_address();
    double r1=Order1.get_distance();
    double r2=Order2.get_distance();
    double d= C1.get_distance(C2);
    if (d<=abs(r1-r2)){
        return true;
    }
    return false;
}


boolPoint check_if_bucket (std::vector<Order> order_vector){
// This function takes in a vector of orders, so a potential bucket, and says whether or not they could all fit in a bucket, and returns the intersection where to deliver if it is true.
//If it its false it will return an empty coordinate and false.
//In order to check if an other order can be added to a bucket we could simply take the vector and pushback the new order. And say if check_if_bucket then its good.
    //struct boolPoint p3 = {Coordinate(), false};
    boolPoint p3=boolPoint();
    int count0=0;
    for (int i = 0; i < int(order_vector.size()); i++){
        Order order1 = order_vector[i];
        for (int j = i+1; j < int(order_vector.size()); j++){
            Order order2 = order_vector[j];
            std::vector <Coordinate> intersection_vector=get_intersection(order1, order2);
            if (intersection_vector.size()== 0 && !check_if_inside(order1, order2))
            {
                return p3;}
            if (intersection_vector.size()== 0 && check_if_inside(order1, order2))
            {
                count0++;
                continue;
            }
            Coordinate intersection1=intersection_vector[0];
            Coordinate intersection2=intersection_vector[1];
            int count1= 0;
            int count2=0;
            for (int k = 0; k < int(order_vector.size()); k++)
            {
                if (k == i || k == j) {
                        count1++;
                        count2++;  }


                else  { if ((order_vector[k].get_user().get_address()==order1.get_user().get_address() and order_vector[k].get_distance()==order1.get_distance()) || (order_vector[k].get_user().get_address()==order2.get_user().get_address() and order_vector[k].get_distance()==order2.get_distance())) {
                            count1++;
                            count2++;  }

                        else {   if (intersection1.get_distance(order_vector[k].get_user().get_address()) <= order_vector[k].get_distance()){
                            count1++;}
                            if (intersection2.get_distance(order_vector[k].get_user().get_address()) <= order_vector[k].get_distance()){
                            count2++;}
              }}}
            if (int(order_vector.size())==count1)
            {
                //struct boolPoint p1 = {intersection1, true};
                boolPoint p1=boolPoint(intersection1,true);
                return p1;
            }
            if (int(order_vector.size())==count2)
            {
                //struct boolPoint p2 = {intersection2, true};
                boolPoint p2=boolPoint(intersection2,true);
                return p2;
            }

    }}
    if (count0==(order_vector.size()*order_vector.size()-order_vector.size())/2)
    {
        //struct boolPoint p4 = {order_vector[0].get_user().get_address(), true};
        boolPoint p4=boolPoint(order_vector[0].get_user().get_address(), true);
        return p4;
    }
    return p3;
}
