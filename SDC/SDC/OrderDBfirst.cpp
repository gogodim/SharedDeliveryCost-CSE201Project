#include "OrderDBfirst.h"

OrderDBfirst::OrderDBfirst(UserDB user,
             CompanyDB company,
             double value,
             double delivery_cost,
             double distance){
        this->user = user;
        this->company = company;
        this->value = value;
        this->delivery_cost = delivery_cost;
        this->distance = distance;
}

bool OrderDBfirst::operator==(OrderDBfirst other){ // we assume orders are equal when the user's identity and company choice are the same
                                    // we assume the user will always group his orders for one company in a single order

    //name_comparison
    std::string name=user.get_username();
    std::string other_name=other.user.get_username();

    bool a=(name==other_name);

    //company_comparison

    std::string comp=company.name;
    std::string other_comp=other.company.name;

    bool b=(comp==other_comp);

    return a&&b;

}

UserDB OrderDBfirst::get_user(){
    return user;
}
CompanyDB OrderDBfirst::get_company(){
    return company;
};
double OrderDBfirst::get_value(){
    return value;
};
double OrderDBfirst::get_delivery_cost(){
    return delivery_cost;
};
double OrderDBfirst::get_distance(){
    return distance;
};


