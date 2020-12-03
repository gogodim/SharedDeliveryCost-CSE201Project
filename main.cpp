#include <QCoreApplication>
#include <stdio.h>
#include <iostream>
#include <QGeoLocation>
#include <classes.h>
//#include <Wt/WApplication.h>
//#include <Wt/WBreak.h>
//#include <Wt/WContainerWidget.h>
//#include <Wt/WLineEdit.h>
//#include <Wt/WPushButton.h>
//#include <Wt/WText.h>


using namespace std;

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    Coordinate NY=Coordinate(40.7128,-74.0060);
    Coordinate Tokyo=Coordinate(35.6895,139.6917);
    double distance=NY.get_distance(Tokyo);

    cout<< "distance between NY and Tokyo : " << distance << " km ";

    QGeoLocation b=QGeoLocation();

    //return a.exec();
}

