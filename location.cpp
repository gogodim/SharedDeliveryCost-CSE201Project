// standard C++ header:
#include <iostream>
#include <string>

// Qt header:
#include <QApplication>
#include <QGeoAddress>
#include <QGeoServiceProvider>
#include <QGeoCodingManager>
#include <QGeoCoordinate>
#include <QGeoLocation>

# include "location.h"

Coordinate AddressToCoordinate(int argc, char **argv,
                               char* PostalCode, char* City, char* StreetNo){
    #undef qApp
    QCoreApplication qApp(argc, argv);
    // we use an api call to osm
    QGeoServiceProvider qGeoService("osm");
    QGeoCodingManager *pQGeoCoder = qGeoService.geocodingManager();
    QLocale qLocaleC(QLocale::C, QLocale::France);
    pQGeoCoder->setLocale(qLocaleC);
    // build address
    QGeoAddress qGeoAddr;
    qGeoAddr.setPostalCode(QString::fromUtf8(PostalCode));
    qGeoAddr.setCity(QString::fromUtf8(City));
    qGeoAddr.setStreet(QString::fromUtf8(StreetNo));
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

string CoordinateToAddress(int argc, char **argv, Coordinate coord){
    #undef qApp
    QCoreApplication qApp(argc, argv);
    // we use an api call to osm
    QGeoServiceProvider qGeoService("osm");
    QGeoCodingManager *pQGeoCoder = qGeoService.geocodingManager();
    QLocale qLocaleC(QLocale::C, QLocale::France);
    pQGeoCoder->setLocale(qLocaleC);

    // build address
    QGeoCoordinate qGeoCoord(coord.get_latitude(), coord.get_longitude());
    QGeoCodeReply *pQGeoCode = pQGeoCoder->reverseGeocode(qGeoCoord);

    string res;

    QObject::connect(pQGeoCode, &QGeoCodeReply::finished,
      [&qApp, &qGeoCoord, pQGeoCode, &res](){
        // eval. result
        QList<QGeoLocation> qGeoLocs = pQGeoCode->locations();
        if (pQGeoCode->error() != QGeoCodeReply::NoError) {
            std::cout << "an error occured!" << std::endl;
            return;}

        for (QGeoLocation &qGeoLoc : qGeoLocs) {
            qGeoLoc.setCoordinate(qGeoCoord);
            QGeoAddress qGeoAddr = qGeoLoc.address();
            res = qGeoAddr.text().toUtf8().constData();
        }
        qApp.exit(0);
      });
     qApp.exec();
    return res;
}

int main(int argc, char **argv){
    Coordinate coord = AddressToCoordinate(argc, argv, (char*)"91120", (char*)"Palaiseau", (char*)"Ecole Polytechnique");
    std::cout << coord.get_latitude() << std::endl;
    std::cout << coord.get_longitude() << std::endl;
    // CoordinateToAddress(argc, argv, Coordinate(48.711559,2.215030));
    return 0;
}
