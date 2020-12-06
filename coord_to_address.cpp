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
  QGeoCoordinate qGeoCoord(48.711559,2.215030);
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
