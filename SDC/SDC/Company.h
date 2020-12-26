#ifndef COMPANY_H
#define COMPANY_H

#include <string>
#include <vector>

class Company{
public:

    // list of vectors of doubles, each vector of the form:
    // ( minimum amount to pay, maximum amount, delivery fee for amounts in the interval [min_amount, max_mount])

    Company(std::string name, std::vector<std::vector<double> > opts);
    Company();
    void set_options(std::vector<std::vector<double> > options);
    void set_name(std::string name);
//private:
    std::string name;
    std::vector<std::vector<double> > options;

};

#endif // COMPANY_H
