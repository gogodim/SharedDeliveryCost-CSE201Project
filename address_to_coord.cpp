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

int main(int argc, char **argv)
{
    #undef qApp
  QCoreApplication qApp(argc, argv);
  QGeoServiceProvider qGeoService("osm");
  QGeoCodingManager *pQGeoCoder = qGeoService.geocodingManager();
  QLocale qLocaleC(QLocale::C, QLocale::France);
  pQGeoCoder->setLocale(qLocaleC);

  // build address
  QGeoAddress qGeoAddr;
  qGeoAddr.setPostalCode(QString::fromUtf8("91120"));
  qGeoAddr.setCity(QString::fromUtf8("Palaiseau"));
  qGeoAddr.setStreet(QString::fromUtf8("Avenue Henri Becquerel 103"));
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
