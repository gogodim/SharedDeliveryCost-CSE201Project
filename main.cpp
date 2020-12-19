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

    // small test case for distance computing with coords of type (lat,lon)

    Coordinate NY=Coordinate(40.7128,-74.0060);
    Coordinate Tokyo=Coordinate(35.6895,139.6917);
    double distance=NY.get_distance(Tokyo);


    // small test case for match_delivery cost

    User user=User( ("username"),("password"),("name"),("surname"),("address"), ("email"),NY);

    list<vector<double>> l;
    vector<double> v;
    v.push_back(1);
    v.push_back(10);
    v.push_back(4);
    l.push_back(v);

// printing content of the company list

//    list<vector<double>>::iterator i;
//    for(i=l.begin();i!=l.end(); ++i){
//        vector<double> v=*i;
//        for(int j=0; j<3;++j)
//            cout<< v[j] << " euros ";
//    }

    Company c=Company(("company") ,l);
    Order order=Order(user, c,2,5,98);

    list<Order> ct;
    ct.push_back(order);
    Bucket buc=Bucket(c, ct ,2,5,4,false);

    buc.match_delivery_cost();

    cout<< "Test for computing distance, distance between NY and Tokyo : " << distance << " km \n";

    cout <<"Test for match_delivery cost: completion state=" << buc.completion;

    //return a.exec();
}

