#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>
#include <vector>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <Wt/WApplication.h>

namespace dbo = Wt::Dbo;


class CompanyDB{
public:

    // list of vectors of doubles, each vector of the form:
    // ( minimum amount to pay, maximum amount, delivery fee for amounts in the interval [min_amount, max_mount])

    CompanyDB(std::string name, std::vector<std::vector<double> > opts);
    CompanyDB();
    void set_options(std::vector<std::vector<double> > options);
    void set_name(std::string name);

    std::string name;
    std::vector<std::vector<double> > options;
    std::string compressedOptions;
    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, name, "name");
        dbo::field(a, compressedOptions,"options");
    }

};

#endif // COMPANY_H
