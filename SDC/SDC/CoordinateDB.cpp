#include "CoordinateDB.h"
#include <cmath>
CoordinateDB::CoordinateDB(double latitude,
                       double longitude){
    this->latitude = latitude;
    this->longitude = longitude;
    }
CoordinateDB::CoordinateDB(){
    latitude = 0;
    longitude = 0;
    }
//Coordinate, Getters
    double CoordinateDB::get_latitude(){
        return latitude;
    }
    double CoordinateDB::get_longitude(){
        return longitude;
    }
//Coordinate, Setters
    void CoordinateDB::set_latitude(double latitude){
        this->latitude = latitude;
    }
    void CoordinateDB::set_longitude(double longitude){
        this->longitude = longitude;
    }
    void CoordinateDB::set_coordinate(double latitude,
                                    double longitude){
        this->latitude = latitude;
        this->longitude = longitude;
    }

CoordinateDB coordinate_from_address(std::string address){
    return CoordinateDB(0, 0);
}

CoordinateDB address_to_coordinates(std::string address){
    return CoordinateDB();
}
std::string coordinate_to_address(CoordinateDB coordinate){
    return "";
}

double CoordinateDB::get_distance(CoordinateDB other){

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
