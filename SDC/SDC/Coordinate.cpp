#include "Coordinate.h"

#include <iostream>
#include <QApplication>
#include <QGeoAddress>
#include <QGeoCodingManager>
#include <QGeoCoordinate>
#include <QGeoLocation>
#include <QGeoServiceProvider>
#include <QSslSocket>
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

bool Coordinate::operator==(Coordinate other){ // two coords are equal when lat = long
        return ((get_latitude() == other.get_latitude()) && (get_longitude() == other.get_longitude()));
    }
Coordinate coordinate_from_address(std::string address){
    return Coordinate(0, 0);
}

Coordinate address_to_coordinates(int argc, char** argv, std::string postalcode, std::string city, std::string street){
    #undef qApp
    QCoreApplication qApp(argc, argv);
    // we use an api call to osm
    QGeoServiceProvider qGeoService("osm");
    QGeoCodingManager *pQGeoCoder = qGeoService.geocodingManager();
    QLocale qLocaleC(QLocale::C, QLocale::France);
    pQGeoCoder->setLocale(qLocaleC);
    // build address
    QGeoAddress qGeoAddr;
    qGeoAddr.setPostalCode(QString::fromUtf8(postalcode.c_str()));
    qGeoAddr.setCity(QString::fromUtf8(city.c_str()));
    qGeoAddr.setStreet(QString::fromUtf8(street.c_str()));
    QGeoCodeReply *pQGeoCode = pQGeoCoder->geocode(qGeoAddr);

    Coordinate res;

    QObject::connect(pQGeoCode, &QGeoCodeReply::finished,
      [&qApp, &qGeoAddr, pQGeoCode, &res](){
        if (pQGeoCode->error() != QGeoCodeReply::NoError) {
            std::cout << "an error occured!" << std::endl;
            return;}
        // eval. result
        QList<QGeoLocation> qGeoLocs = pQGeoCode->locations();
        for (QGeoLocation &qGeoLoc : qGeoLocs) {
          qGeoLoc.setAddress(qGeoAddr);
          res = Coordinate(qGeoLoc.coordinate().latitude(), qGeoLoc.coordinate().longitude());
        }
        qApp.exit(0);
      });
  qApp.exec();
  return res;
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
    double distance = R * c; // in km

    distance=distance*1000; // distance is now in meters

    return distance; // in meters

}
