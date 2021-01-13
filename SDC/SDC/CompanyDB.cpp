#include "CompanyDB.h"

CompanyDB::CompanyDB(std::string name, std::vector<std::vector<double>> opts){
    this->name = name;
    this->options = opts;
}
CompanyDB::CompanyDB(){
    this->name = "Default Company";
    this->options = std::vector<std::vector<double>>();
}

void CompanyDB::set_options(std::vector<std::vector<double>> options){
    this->options = options;
}
void CompanyDB::set_name(std::string name){
    this->name = name;
}
