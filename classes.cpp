# include "classes.h"
# include <math.h>
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>




//--------------------------Coordinate-------------------------------


//Coordinate Constructor
Coordinate::Coordinate(double latitude,
                       double longitude){
    this->latitude = latitude;
    this->longitude = longitude;
    }
Coordinate::Coordinate(){
    latitude = 0;
    longitude = 0;
    }
//Coordinate, Getters
    double Coordinate::get_latitude(){
        return latitude;
    }
    double Coordinate::get_longitude(){
        return longitude;
    }
//Coordinate, Setters
    void Coordinate::set_latitude(double latitude){
        this->latitude = latitude;
    }
    void Coordinate::set_longitude(double longitude){
        this->longitude = longitude;
    }
    void Coordinate::set_coordinate(double latitude,
                                    double longitude){
        this->latitude = latitude;
        this->longitude = longitude;
    }

bool Coordinate::operator==(Coordinate other){ // two coords are equal when lat = long
        return ((get_latitude() == other.get_latitude()) && (get_longitude() == other.get_longitude()));
    }

double Coordinate::get_distance(Coordinate other){

    const int R=6371; //radius of the earth in km
    const double PI=3.14159265358;
    // all angles converted to radians
    double lat1=latitude*PI/180;
    double lon1=longitude*PI/180;
    double lat2=other.latitude*PI/180;
    double lon2=other.longitude*PI/180;

    double latDist = (lat2 - lat1);
    double lonDist =(lon2 - lon1);

    double a = sin(latDist/2) * sin(latDist/2) + cos(lat1) * cos(lat2)* sin(lonDist / 2) * sin(lonDist / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    return distance; // in km

}


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

Order::Order(User user,
             Company company,
             double value,
             double delivery_cost,
             double distance,
             Coordinate address){
        this->user = user;
        this->company = company;
        this->value = value;
        this->delivery_cost = delivery_cost;
        this->distance = distance;
        to_pay = 0;
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

    return a&&b;

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

}

Bucket::Bucket(Company company, std::list<Order> content,double cur_amount,double cur_cost,
               double max_cost,bool completion){


    this->company=company;
    this->content=content;
    this->completion=completion;
    this->max_cost=max_cost;
    this->cur_amount=cur_amount;
    this->cur_cost=cur_cost;
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

void Bucket::add_order(Order order){

        //bol = True;
        //while(bol==True){
         //   for(command in bucket_content){
          //      if(radius_overlap(command,order)==False){
         //if(radius_overlap(bucket.area,order)){
             content.push_back(order);
             cur_cost+= order.get_delivery_cost();
             cur_amount+= order.get_value();
             max_cost= delivery_cost(company,cur_amount);
             match_delivery_cost(); // update the completion state and amount each user has to pay

         }

tuple<bool,Coordinate>  Bucket::is_compatible(Order new_order){

    //----------- checking company---------------

    Coordinate coord;

    tuple<bool,Coordinate> tpl=make_tuple(false,coord);

    if(new_order.get_company().get_name() == company.get_name()){ // if the order is from the same company as the bucket

        //----------- checking intersection---------------

        bool inter; // inter will be true if the intersection exists

        list<Order> new_content(content); // copy of bucket content

        new_content.push_back(new_order); // new_content adds the new_order to it

        vector<Order> order_vector;
        order_vector.reserve(new_content.size());
        copy(begin(new_content), end(new_content), back_inserter(order_vector)); // converts new_content to vector type


        boolPoint bp=check_if_bucket(order_vector); // return an intersection point based on the addition of the new order

        inter=bp.has_intersection; //  sets inter

        if (inter){ // if inter is true <=> the intersection point exists

            coord=bp.p; // coord will be used in generate_buckets to set the bucket intersection point

            tpl=make_tuple(inter,coord);

            return tpl;
        }

        else{
            return tpl;
        }
    }

    else{

        return tpl;
    }
}

Bucket copy(Bucket other){ // crates a clone of the input Bucket

    return Bucket( other.get_company(), other.get_content(),other.get_cur_amount(),other.get_cur_cost(),other.get_max_cost(), other.get_completion());
}

list<Bucket> generate_buckets(Order new_order,list<Bucket>& buckets){ // generates all valid bucket combinations of existing buckets with new_order

    list<Bucket> res; // res will contain new combinations of buckets with new_order
    list<Bucket>::iterator it;
    for (it = buckets.begin(); it != buckets.end(); it ++){
        Bucket CurrentBucket = *it;

        tuple<bool, Coordinate> tpl=CurrentBucket.is_compatible(new_order);

        bool compat=get<0>(tpl); // get first entry of tuple (true if there exists an intersection)

        if (compat){

            Bucket NewBucket=copy(CurrentBucket);// copy the current bucket and add the new_order to the copy

            Coordinate coord=get<1>(tpl); //get second entry of tuple (coordinate of intersection_point)

            NewBucket.add_order(new_order); // update NewBucket by adding the new_order
            NewBucket.set_intersection_point(coord);

            buckets.push_back(NewBucket); // update bucket list with the new combination
            res.push_back(NewBucket); // add the combination to res
        }
    }
    return res;
}


double delivery_cost(Company company,double amount){

    int v = company.get_options().size();

    for(int i=0; i<v; i++){
        if(amount < company.get_options()[i][0] and amount > company.get_options()[i][1]){
            return company.get_options()[i][2];
        }
    }

    return 0;
}

void Bucket::match_delivery_cost(){

    double difference=cur_cost-max_cost;

    if (difference>=0){ //the bucket is overflowing, conditions are met, we just need to redistribute the shared delivery cost

        completion=true;
        cur_cost-=difference;

        double idv=difference/content.size();

        list<Order>::iterator i;

        for(i = content.begin(); i != content.end(); ++i) {
            i->set_to_pay(i->get_delivery_cost() - idv);

        }
      }
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


tuple<bool,Bucket,list<Bucket>> processOrder(list<Bucket> bucket_list, Order new_order){


    std::list<Bucket> buckets_to_inspect=generate_buckets(new_order, bucket_list); // generate list of buckets that can satisfy the optimization problem
                                                                                    // these new buckets are the only interesting ones to look at, the other ones can't be complete

    buckets_to_inspect.sort(compare);//sort bucket_list in decreasing order of length

    std::list<Bucket>::iterator i;

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

    tuple<bool,Bucket,list<Bucket>> tpl; //tpl is a tuple that will contain the final output

    list<Order> orders_to_remove=optimal_buc.get_content();

    if (found==true){ // if an optimal bucket was found, there are orders to delete

     list<Bucket> new_bucket_list;

    for (i=bucket_list.begin();i!=bucket_list.end();i++){
        Bucket buc=*i;
        buc.find_and_remove_order_list(orders_to_remove);
        if (buc.get_content().size()>0){
            new_bucket_list.push_back(buc);
        }

     }

    tpl=make_tuple(true,optimal_buc,new_bucket_list);
  }

   else{

     tpl=make_tuple(false,optimal_buc,bucket_list); // in this case, optimal buc is empty

    }

    return tpl;
}

//------------------Circle Intersection--------------------


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

std::vector<Coordinate> get_intersection(Order Order1, Order Order2)

{
    Coordinate C1= Order1.get_user().get_address();
    Coordinate C2= Order2.get_user().get_address();
    double* c1= convert_to_meters(C1);
    double* c2= convert_to_meters(C2);
    double r1=Order1.get_distance();
    double r2=Order2.get_distance();
    double d= C1.get_distance(C2);
    if (d > r1+ r2)
        return std::vector<Coordinate>();

    double a=(r1*r1-r2*r2+d*d)/(2*d);
    double h=sqrt(r1*r1-a*a);
    double b=d-a;
    double c3x= c1[0] + a*( c2[0] - c1[0] )/d;
    double c3y= c1[1] + a*( c2[1] - c1[1] )/d;
    double c4x = c3x + h*(c2[1] -c1[1]) /d;
    double c4y = c3y - h*( c2[0] - c1[0] )/d;
    double c5x = c3x - h*(c2[1] -c1[1]) /d;
    double c5y = c3y + h*( c2[0] - c1[0] )/d;
    double c4[2]={c4x, c4y};
    double c5[2]={c5x, c5y};

    Coordinate Intersection1= convert_to_coordinates(c4);
    Coordinate Intersection2= convert_to_coordinates(c5);
    std::vector<Coordinate> vect;
              vect.push_back(Intersection1);
              vect.push_back(Intersection2);
              return vect;
}

bool check_if_inside(Order Order1, Order Order2){
    Coordinate C1= Order1.get_user().get_address();
    Coordinate C2= Order2.get_user().get_address();
    double* c1= convert_to_meters(C1);
    double* c2= convert_to_meters(C2);
    double r1=Order1.get_distance();
    double r2=Order2.get_distance();
    double d= C1.get_distance(C2);
    if (d<=abs(r1-r2))
        return true;
    return false;
}


boolPoint check_if_bucket (std::vector <Order> order_vector)
{
    struct boolPoint p3 = {Coordinate(), false};
    int count0=0;
    for (int i = 0; i < int(order_vector.size()); i++){
        Order order1 = order_vector[i];
        for (int j = i+1; j < int(order_vector.size()); j++){
            Order order2 = order_vector[j];
            std::vector <Coordinate> intersection_vector=get_intersection(order1, order2);
            if (intersection_vector.size()== 0 && !check_if_inside(order1, order2))
                return p3;
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
                if (intersection1.get_distance(order_vector[k].get_user().get_address()) <= order_vector[k].get_distance())
                        count1++;
                if (intersection2.get_distance(order_vector[k].get_user().get_address()) <= order_vector[k].get_distance())
                        count2++;
            }
            if (int(order_vector.size())==count1)
            {
                struct boolPoint p1 = {intersection1, true};
                return p1;
            }
            if (int(order_vector.size())==count2)
            {
                struct boolPoint p2 = {intersection2, true};
                return p2;
            }

    }}
    if (count0==(order_vector.size()*order_vector.size()-order_vector.size())/2)
    {
        struct boolPoint p4 = {order_vector[0].get_user().get_address(), true};
                return p4;
    }
    return p3;
}
