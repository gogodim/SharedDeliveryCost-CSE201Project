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

std::string compressComOptions(std::vector< std::vector<double> > compOptions); //creates a string to be saved in the DB from a 2D vector of orpitons
std::vector< std::vector<double> > splitCompOprions(std::string compOptions); //decompress the string given by the above function back to a 2D vecor of options
std::string compressOrderIDs(std::vector< int > OrderIDs); //creates a string to be saved in the DB from a vector of ints
std::vector<int> splitOrderIDs(std::string OrderIDs); //decompress the string given by the above function to a vector of ints
std::string precision_2(float number);//creates a string representing a floating point integer with only 2 decimal points
std::string precision_2(std::string number); //same as above but takes a string instead of a floating point int
#endif // HELPINGFUNCTIONS_H
