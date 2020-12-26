#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>
class Coordinate
{
public:
    Coordinate();
    Coordinate(double lat,double lo);
    double get_distance(Coordinate other);
    double get_latitude();
    double get_longitude();
    void set_latitude(double latitude);
    void set_longitude(double longitude);
    void set_coordinate(double latitude, double longitude);

private:
    double latitude; //given in degrees (western latitudes are negative angles)
    double longitude; // given in degrees (southern longtidues are negative angles)

};

Coordinate coordinate_from_address(std::string address);

#endif // COORDINATE_H
