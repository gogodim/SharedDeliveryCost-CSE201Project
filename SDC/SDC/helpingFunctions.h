#ifndef HELPINGFUNCTIONS_H
#define HELPINGFUNCTIONS_H
#include <iostream>
#include <string>
#include <vector>
#include<list>


class helpingFunctions
{
public:
    helpingFunctions();
};

std::string compressComOptions(std::vector< std::vector<double> > compOptions);
std::vector< std::vector<double> > splitCompOprions(std::string compOptions);
std::vector<int> splitOrderIDs(std::string OrderIDs);
std::string compressOrderIDs(std::vector< int > OrderIDs);



#endif // HELPINGFUNCTIONS_H
