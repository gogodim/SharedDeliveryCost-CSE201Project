#include "Coordinate.h"
#include <cmath>
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

Coordinate coordinate_from_address(std::string address){
    return Coordinate(0, 0);
}

Coordinate address_to_coordinates(std::string address){
    return Coordinate();
}
std::string coordinate_to_address(Coordinate coordinate){
    return "";
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
