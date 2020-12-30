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

//    Coordinate NY=Coordinate(40.7128,-74.0060);
//    Coordinate Tokyo=Coordinate(35.6895,139.6917);
//    double distance=NY.get_distance(Tokyo);


//    //----------------------------small test case for match_delivery cost-------------------------------

//    User user=User();

//    vector<vector<double>> l;
//    vector<double> v;
//    v.push_back(1);
//    v.push_back(10);
//    v.push_back(4);
//    l.push_back(v);

// // printing content of the company list

// //    list<vector<double>>::iterator i;
// //    for(i=l.begin();i!=l.end(); ++i){
// //        vector<double> v=*i;
// //        for(int j=0; j<3;++j)
// //            cout<< v[j] << " euros ";
// //    }

//    Company c=Company(("company") ,l);
//    Order order=Order(user, c,2,5,98);

//    list<Order> ct;
//    ct.push_back(order);
//    Bucket buc=Bucket(c, ct ,2,5,4,false,Coordinate());

//    buc.match_delivery_cost();

//    //-----------------------------test 1 for removing and finding for ints----------------------------------

//    cout<<"test 1 for removing and finding"<<"\n";


//    list<int> content;
//    int a=2;
//    int b=3;
//    int d=1;

//    int val=1;

//    content.push_back(a);
//    content.push_back(b);
//    content.push_back(d);

//    std::list<int>::iterator i;
//    std::list<int>::iterator final;

//    cout<<"Before deletion, list size:"<<content.size()<<"\n";

//    for(i=content.begin();i!=content.end();i++){

//        if (*i==val){
//             final=i;
//             content.erase(final);
//             break;
//            }
//        }

//        for(i=content.begin();i!=content.end();i++){
//            cout<<*i<<"\n";
//            }

//    cout<<"After deletion, list size:"<<content.size()<<"\n";

//    //--------------------test 2 for removing and finding for ints-----------------------------

//    cout<<"test 2 for removing and finding"<<"\n";

//    list<int> numbers={1,2,3,4,5,6,7,8,9,10};
//    list<int> to_remove={7,2,11,1};

//    cout<<"Before deletion, list size:"<<numbers.size()<<"\n";

//    list<int>::iterator t;
//    list<int>::iterator s;

//    for (t=to_remove.begin();t!=to_remove.end();t++){
//        int key=*t;
//        s=std::find(numbers.begin(), numbers.end(), key); // return iterator at position of key in numbers

//    if (s != numbers.end()){ //true if key has been found in numbers
//           numbers.erase(s); //remove the key in numbers
//        }
//    }


    //--------------------test for sorting in decreasing order of length------------------------

    Bucket b1=Bucket();

    Bucket b2=Bucket();

    Bucket b3=Bucket();

    Bucket b4=Bucket();

    Bucket b5=Bucket();

    vector<double> vect1={0,10,2};
    vector<double> vect2={10,30,3};
    vector<double> vect3={30,70,4};
    vector<double> vect4={70,200,4};

    vector<vector<double>> opts;

    opts.push_back(vect1);
    opts.push_back(vect2);
    opts.push_back(vect3);
    opts.push_back(vect4);

    string name="X";

    Company X=Company(name,opts);

    User John;
    User Yuki;
    User Haruhi;
    User Noah;

    John=User(("Kyon"),("shdgfhsd"),("John"),("Smith"),Coordinate(54,87),("john.smith@gmail.com"));

    Yuki=User(("NGT"),("gehihrgus"),("Yuki"),("Nagato"),Coordinate(23,34),("yuki.nagato@gmail.com"));

    Haruhi=User(("HS"),("fhzuifzef"),("Haruhi"),("Suzumiya"),Coordinate(89,23),("haruhi.suzumiya@gmail.com"));

    Noah=User(("Noix"),("feuihfrf"),("Noah"),("Russoto"),Coordinate(92,13),("noah.rb@gmail.com"));

    //Order(User user, Company company,double value,double delivery_cost,double distance,Coordinate address)

    Order ord1=Order(John,X,24,3,20);
    Order ord2=Order(Yuki,X,16,2,30);
    Order ord3=Order(Haruhi,X,57,5,10);
    Order ord4=Order(Noah,X,5,1,100);

    b1.add_order(ord1); // b1 has John + Yuki
    b1.add_order(ord2);
    b2.add_order(ord2); // b2 has Yuki
    b3.add_order(ord3); // b3 has Haruhi
    b4.add_order(ord3); // b4 has Yuki + Haruhi
    b4.add_order(ord2);

    list<Bucket> B_list={b2,b1,b3,b4};

    B_list.sort(compare);

    list<Bucket>::iterator iter;

    int cnt=0;

    iter=B_list.begin();

    for (iter=B_list.begin();iter!=B_list.end();iter++){

        cnt+=1;

        Bucket buc=*iter;

        cout << "Bucket " << cnt;

        cout << "\n" << "Start" << "\n";

        list<Order> ord_list=buc.get_content();

        list<Order>::iterator iter2;

        for (iter2=ord_list.begin();iter2!=ord_list.end();iter2++){

            Order order=*iter2;
            cout << "User:" << order.get_user().get_name() << "\n";
        }

        cout << "End" << "\n";

    }

    //---------------------test for removal of orders in optimal bucket----------------------------

    list<Order> orders_to_remove;

    orders_to_remove.push_back(ord1);
    orders_to_remove.push_back(ord2);
    orders_to_remove.push_back(ord4);

    list<Bucket> new_bucket_list;


    for (iter=B_list.begin();iter!=B_list.end();iter++){
        Bucket buc=*iter;
        buc.find_and_remove_order_list(orders_to_remove);
        if (buc.get_content().size()>0){
            new_bucket_list.push_back(buc);
        }
    }

        cout<<"Order removal in bucket list"<<"\n";

        cnt=0;

        for (iter=new_bucket_list.begin();iter!=new_bucket_list.end();iter++){

            cnt+=1;

            Bucket buc=*iter;

            cout << "Bucket " << cnt;

            cout << "\n" << "Start" << "\n";

            list<Order> ord_list=buc.get_content();

            list<Order>::iterator iter2;

            for (iter2=ord_list.begin();iter2!=ord_list.end();iter2++){

                Order order=*iter2;
                cout << "User:" << order.get_user().get_name() << "\n";
            }

            cout << "End" << "\n";

        }


    //---------------------------test for circle intersection------------------------------------


    //--------------------------final run with complete example----------------------------------


    //cout<<"After deletion, list size:"<<numbers.size()<<"\n";

    //cout<< "Test for computing distance, distance between NY and Tokyo : " << distance << " km \n";

    //cout <<"Test for match_delivery cost: completion state=" << buc.get_completion() <<"\n";

//    return a.exec();
}

