#include "classes.h"
#include <math.h>

Coordinate::Coordinate(double lat, double lo){

latitude=lat;
longitude=lo;

}

Coordinate::Coordinate(){

latitude=0;
longitude=0;

}




Company::Company(std::string name, std::list<std::vector<int>> opts){
    this->name = name;
    this->options = opts;
}

Company::Company(){
    this->name = "Default Company";
    this->options = std::list<std::vector<int>>();
}

void Company::set_options(std::list<std::vector<int>> options){
    this->options = options;
}

void Company::set_name(std::string name)
{

    this->name = name;
}

bool check_valid_email(std::string email){
    return true;
}

bool check_valid_address(std::string address){
    return true;
}



Order::Order(User user,
             Company company,
             double value,
             double delivery_cost,
             double distance){
        this->user = user;
        this->company = company;
        this->value = value;
        this->delivery_cost = delivery_cost;
        this->distance = distance;
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

Coordinate convert_to_coordinates(std::string address){

    return Coordinate(0,0);
}



User::User(std::string usernam,std::string mp,std::string nam,std::string surnam,std::string adres,std::string mai, Coordinate coords){
    username = usernam;
    name = nam;
    surname = surnam;
    email = mai;
    address = adres;
    password = mp;
    coordinates = coords;
};

// SET
void User::set_coordinates(int latitude,int longitude){
    coordinates = Coordinate(latitude, longitude);
};
void User::set_name(std::string n){
    name = n;
    //return void;
};
void User::set_username(std::string n){
    username = n;
};
void User::set_email(std::string n){
    email = n;
};
void User::set_surname(std::string n){
    surname = n;
};

void User::set_password(std::string n){
    password = n;
};
void User::set_address(std::string n){
    address = n;
};

// GET

std::string User::get_address(){
    return address;
};
std::string User::get_password(){
    return password;
};
std::string User::get_surname(){
    return surname;
};
std::string User::get_email(){
    return email;
};
std::string User::get_username(){
    return username;
};
std::string User::get_name(){
    return name;
};
Coordinate User::get_coordinates(){
    return coordinates;
};


std::vector<Bucket> generate_buckets(Order new_order,
                                   std::list<Bucket> buckets){
    std::vector<Bucket> res;
    std::list<Bucket>::iterator it;
    for (it = buckets.begin(); it != buckets.end(); it ++){
        Bucket CurrentBucket = *it;
        if (CurrentBucket.is_compatible(new_order)){
            res.push_back(CurrentBucket);
        }
    }
    return res;
} // generates all valid bucket combinations of existing buckets with new_order


double array_of_one_delivery(){ // This function creates the array of all the orders concerned by the delivery, idk how to do it because linked to the database?
    double arr = 0;
    Coordinate c = order.get_user().get_coordinates()
    double weight = oder.get_delivery_cost() //or get_value()?

};


Coordinate distance_optimization(double array_of_one_delivery()){  //arr has elements of type (lat, lon, weight) and it is the array of all the orders concerned by this delivery
    double lat = 0;
    double lon = 0;
    for(int i, array_of_one_delivery().size(), i++){
        if(i!=()){
            lat = lat + i[0]*i[2];
            lon = lon + i[1]*i[2];
        };

    };
    return Coordinate(lat/array_of_one_delivery().size(),lon/array_of_one_delivery().size());
};


 Bucket::Bucket(){


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

Bucket::Bucket(){
    bucket_company="None";
    std::list<Order> default_buckets; //empty list
    bucket_content=default_buckets;
    bucket_completion=false;
    bucket_max_cost=0;
    bucket_cur_amount=0;
    bucket_cur_cost=0;

}

void Bucket::set_company(std::string company){

    bucket_company=company;
};

void Bucket::add_order(Order order){
    if(order.get_company()==bucket_company){
        //bol = True;
        //while(bol==True){
         //   for(command in bucket_content){
          //      if(radius_overlap(command,order)==False){
         if(radius_overlap(bucket.area,order)){
             bucket_content.append(order);
             bucket_cur_cost+= order.get_delivery_cost();
             bucket_cur_amount+= order.get_value();
             bucket_max_cost= delivery_cost(bucket_company,bucket_cur_amount);
             if(bucket_max_cost==bucket_cur_cost){
                 bucket_completion = True;
             };
         };
    };
};

double delivery_cost(Company company,double amount){
    for(int i, i<=company.options.size, i++){
        if(amount<company.options[i][0] and amount>company.options[1]){
            return company.options[2];
        };
    };
};


