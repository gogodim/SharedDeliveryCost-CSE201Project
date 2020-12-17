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

int AddressToCoordinate(int argc, char **argv,
          char* PostalCode, char* City, char* StreetNo)
{
    #undef qApp
  QCoreApplication qApp(argc, argv);
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

  QObject::connect(pQGeoCode, &QGeoCodeReply::finished,
    [&qApp, &qGeoAddr, pQGeoCode](){
      // eval. result
      QList<QGeoLocation> qGeoLocs = pQGeoCode->locations();
      if (pQGeoCode->error() != QGeoCodeReply::NoError) return;
      std::cout << qGeoLocs.size() << " location(s) returned." << std::endl;
      for (QGeoLocation &qGeoLoc : qGeoLocs) {
        qGeoLoc.setAddress(qGeoAddr);
        QGeoCoordinate qGeoCoord = qGeoLoc.coordinate();
        std::cout
          << "Lat.:  " << qGeoCoord.latitude() << std::endl
          << "Long.: " << qGeoCoord.longitude() << std::endl;
      }
      qApp.exit(0);
    });
  return qApp.exec();
}
int CoordinateToAddress(int argc, char **argv,
                        double Latitude, double Longitude)
{
  #undef qApp
  QCoreApplication qApp(argc, argv);
  QGeoServiceProvider qGeoService("osm");
  QGeoCodingManager *pQGeoCoder = qGeoService.geocodingManager();
  QLocale qLocaleC(QLocale::C, QLocale::France);
  pQGeoCoder->setLocale(qLocaleC);

  // build address
  QGeoCoordinate qGeoCoord(Latitude, Longitude);
  QGeoCodeReply *pQGeoCode = pQGeoCoder->reverseGeocode(qGeoCoord);
  QObject::connect(pQGeoCode, &QGeoCodeReply::finished,
    [&qApp, &qGeoCoord, pQGeoCode](){
      // eval. result
      QList<QGeoLocation> qGeoLocs = pQGeoCode->locations();
      if (pQGeoCode->error() != QGeoCodeReply::NoError) return;
      std::cout << qGeoLocs.size() << " location(s) returned." << std::endl;
      for (QGeoLocation &qGeoLoc : qGeoLocs) {
          qGeoLoc.setCoordinate(qGeoCoord);
          QGeoAddress qGeoAddr = qGeoLoc.address();
            std::cout << qGeoAddr.text().toUtf8().constData() << std::endl;
      }
      qApp.exit(0);
    });
  return qApp.exec();;

}

int main(int argc, char **argv){
    AddressToCoordinate(argc, argv, (char*)"91120", (char*)"Palaiseau", (char*)"Avenue Henri Becqurel 103");
    CoordinateToAddress(argc, argv, 48.711559, 2.215030);
    return 0;
}
