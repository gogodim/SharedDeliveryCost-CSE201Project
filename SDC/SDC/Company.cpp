#include "Company.h"

Company::Company(std::string name, std::vector<std::vector<double>> opts){
    this->name = name;
    this->options = opts;
}
Company::Company(){
    this->name = "Default Company";
    this->options = std::vector<std::vector<double>>();
}

void Company::set_options(std::vector<std::vector<double>> options){
    this->options = options;
}
void Company::set_name(std::string name){
    this->name = name;
}
