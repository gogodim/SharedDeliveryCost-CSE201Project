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

    //-------------------small test case for distance computing with coords of type (lat,lon)--------------

    Coordinate NY=Coordinate(40.7128,-74.0060);
    Coordinate Tokyo=Coordinate(35.6895,139.6917);
    double distance=NY.get_distance(Tokyo);


    //----------------------------small test case for match_delivery cost-------------------------------

    User user=User();

    vector<vector<double>> l;
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

    //-----------------------------test 1 for removing and finding for ints----------------------------------

    cout<<"test 1 for removing and finding"<<"\n";


    list<int> content;
    int a=2;
    int b=3;
    int d=1;

    int val=1;

    content.push_back(a);
    content.push_back(b);
    content.push_back(d);

    std::list<int>::iterator i;
    std::list<int>::iterator final;

    cout<<"Before deletion, list size:"<<content.size()<<"\n";

    for(i=content.begin();i!=content.end();i++){

        if (*i==val){
             final=i;
             content.erase(final);
             break;
            }
        }

        for(i=content.begin();i!=content.end();i++){
            cout<<*i<<"\n";
            }

    cout<<"After deletion, list size:"<<content.size()<<"\n";

    //--------------------test 2 for removing and finding for ints----------------------------

    cout<<"test 2 for removing and finding"<<"\n";

    list<int> numbers={1,2,3,4,5,6,7,8,9,10};
    list<int> to_remove={7,2,11,1};

    cout<<"Before deletion, list size:"<<numbers.size()<<"\n";

    list<int>::iterator t;
    list<int>::iterator s;

    for (t=to_remove.begin();t!=to_remove.end();t++){
        int key=*t;
        s=std::find(numbers.begin(), numbers.end(), key); // return iterator at position of key in numbers

    if (s != numbers.end()){ //true if key has been found in numbers
           numbers.erase(s); //remove the key in numbers
        }
    }


    cout<<"After deletion, list size:"<<numbers.size()<<"\n";

    cout<< "Test for computing distance, distance between NY and Tokyo : " << distance << " km \n";

    cout <<"Test for match_delivery cost: completion state=" << buc.get_completion() <<"\n";

//    return a.exec();
}

