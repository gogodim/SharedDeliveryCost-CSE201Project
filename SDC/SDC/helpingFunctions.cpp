#include "helpingFunctions.h"

helpingFunctions::helpingFunctions()
{

}

std::vector< std::vector<double> > splitCompOprions(std::string compOptions)
{
    std::vector< std::vector<double> > for_return;
    std::string delimiter = " ";
    std::string delimiter2 = ",";
    size_t pos = 0;
    std::string token;
    while ((pos = compOptions.find(delimiter)) != std::string::npos) {
        token = compOptions.substr(0, pos);
        size_t pos_temp = 0;
        std::vector<double> tokens;
        while((pos_temp = token.find(delimiter2)) != std::string::npos) {
            tokens.push_back(std::stod(token.substr(0, pos_temp)));
            token.erase(0, pos_temp + delimiter2.length());
        }
        for_return.push_back(tokens);
        compOptions.erase(0, pos + delimiter.length());
    }
    return for_return;
}

std::string compressComOptions(std::vector< std::vector<double> > compOptions)
{
    std::string for_return = "";
    for(auto& row:compOptions){
       for(auto& col:row){
          for_return += std::to_string(col)+",";
       }
       for_return += " ";
    }
    return for_return;

}
std::vector<int> splitOrderIDs(std::string OrderIDs){
    std::vector<int>  for_return;
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token;
    while ((pos = OrderIDs.find(delimiter)) != std::string::npos) {
        token = OrderIDs.substr(0, pos);
        for_return.push_back(std::stod(token));
        OrderIDs.erase(0, pos + delimiter.length());
    }
    return for_return;
}
std::string compressOrderIDs(std::vector< int > OrderIDs){
    std::string for_return = "";
    for(auto& row:OrderIDs){
          for_return += std::to_string(row)+",";
    }
}

