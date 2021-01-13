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
    bool operator==(Coordinate other);
private:
    double latitude; //given in degrees (western latitudes are negative angles)
    double longitude; // given in degrees (southern longtidues are negative angles)

};
class Address
{
public:
    Address(){
        this->Postalcode ="91120";
        this->City = "Palaiseau";
        this->Street = "Route de Saclay";
    }
    Address(std::string postalcode, std::string city, std::string street){
        this->Postalcode = postalcode;
        this->City = city;
        this->Street = street;
    };
    std::string get_postalcode(){return Postalcode;}
    std::string get_city(){return City;}
    std::string get_street(){return Street;}
    std::string get_address(){return Postalcode + "," + City +"," + Street;}
    void set_postalcode(std::string postalcode){this->Postalcode = postalcode;};
    void set_city(std::string city){this->City = city;}
    void set_street(std::string street){this->Street = street;}

private:
    std::string Postalcode;
    std::string City;
    std::string Street;

};
Coordinate address_to_coordinates(int argc, char** argv, Address address);
//Coordinate coordinate_from_address(std::string address);

#endif // COORDINATE_H
