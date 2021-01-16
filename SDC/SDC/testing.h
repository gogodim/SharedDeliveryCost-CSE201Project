#include <stdio.h>
#include <iostream>
#include <classes.h>
#include <math.h>
#include <string>
#include <regex>
#include <algorithm>
using namespace std;

int testing(){
    
    //-------------------small test case for distance computing with coords of type (lat,lon)--------------

//    Coordinate NY=Coordinate(40.7128,-74.0060);
//    Coordinate Tokyo=Coordinate(35.6895,139.6917);
//    double distance=NY.get_distance(Tokyo);
//    cout<< "Test for computing distance, distance between NY and Tokyo : " << distance << " m \n";


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
//    cout <<"Test for match_delivery cost: completion state=" << buc.get_completion() <<"\n";


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


//    //--------------------test for sorting in decreasing order of length------------------------

    Bucket b1=Bucket();

    Bucket b2=Bucket();

    Bucket b3=Bucket();

    Bucket b4=Bucket();

    Bucket b5=Bucket();

    vector<double> vect1{0,10,1};
    vector<double> vect2{10,30,1};
    vector<double> vect3{30,70,0.8};
    vector<double> vect4{70,200,0.8};

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

    John=User(("Kyon"),("shdgfhsd"),("John"),("Smith"),Coordinate(48.710542,2.214975),("john.smith@gmail.com"));// lives in building 79 bv des maréchaux

    Yuki=User(("NGT"),("gehihrgus"),("Yuki"),("Nagato"),Coordinate(48.710444,2.215033),("yuki.nagato@gmail.com")); // lives in building 78 bv des maréchaux

    Haruhi=User(("HS"),("fhzuifzef"),("Haruhi"),("Suzumiya"),Coordinate(48.712644,2.215800),("haruhi.suzumiya@gmail.com")); // lives at 103 avenue becquerel

    Noah=User(("Noix"),("feuihfrf"),("Noah"),("Russotto"),Coordinate(48.712137,2.218609),("noah.rb@gmail.com")); // ensta dorms

    Order ord1=Order(John,X,24,0.1,200); // change orders here
    Order ord2=Order(Yuki,X,3,0.2,200);
    Order ord3=Order(Haruhi,X,57,0.1,200);
    Order ord4=Order(Noah,X,5,0.8,200);

    b1.add_order(ord1); // b1 has John + Yuki + Haruhi
    b1.add_order(ord2);
    b1.add_order(ord3);
    b2.add_order(ord2); // b2 has Yuki
    b3.add_order(ord3); // b3 has Haruhi
    b4.add_order(ord3); // b4 has Yuki + Haruhi
    b4.add_order(ord2);

    list<Bucket> B_list={b2,b1,b3,b4};

//   cout << (b1==b4); /// testing if two buckets are equal


    B_list.sort(compare);

    list<Bucket>::iterator iter;

//    print_bucket_list(B_list);

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

//    print_bucket_list(new_bucket_list);


    //---------------------------test for circle intersection------------------------------------

        Coordinate c1=Coordinate(48.712644,2.215800); // 103 avenue Henri Becquerel

        Coordinate c2=Coordinate(48.710542,2.214975); // 79 bv des Maréchaux

        Coordinate c3=Coordinate(48.712137,2.218609); // ENSTA dorms

        Coordinate c4=Coordinate(48.710444,2.215033); // 78 bv des Maréchaux

        double d=c1.get_distance(c2); // used for computing distances

       cout<<"\n"<<"---------"<<"\n";

        list<Bucket> dflt;

        tuple<bool,Bucket,list<Bucket>,string> tpl=processOrder(dflt,ord2); // Yuki's order

        cout<< "optimization: "<<get<0>(tpl)<<"\n";
        cout<< "optimization bucket:";
        get<1>(tpl).print();
        cout << "link: "<<get<3>(tpl)<<"\n";
        cout<< "remaining buckets:"<<"\n";
        print_bucket_list(get<2>(tpl));


        cout<<"\n"<<"---------"<<"\n";

        dflt=get<2>(tpl);

        tpl=processOrder(dflt,ord3); // adding Haruhi's order

        cout<< "optimization: "<<get<0>(tpl)<<"\n";
        cout<< "optimization bucket:";
        get<1>(tpl).print();
        cout << "link: "<<get<3>(tpl)<<"\n";
        cout<< "remaining buckets:"<<"\n";
        print_bucket_list(get<2>(tpl));

        cout<<"\n"<<"---------"<<"\n";

        dflt=get<2>(tpl);

        tpl=processOrder(dflt,ord1); // adding John's order

        cout<< "optimization: "<<get<0>(tpl)<<"\n";
        cout<< "optimization bucket:";
        get<1>(tpl).print();
        cout << "link: "<<get<3>(tpl)<<"\n";
        cout<< "remaining buckets:"<<"\n";
        print_bucket_list(get<2>(tpl));

        cout<<"\n"<<"---------"<<"\n";

        dflt=get<2>(tpl);

        tpl=processOrder(dflt,ord4); // adding Noah's order

        cout<< "optimization: "<<get<0>(tpl)<<"\n";
        cout<< "optimization bucket:";
        get<1>(tpl).print();
        cout << "link: "<<get<3>(tpl)<<"\n";
        cout<< "remaining buckets:"<<"\n";
        print_bucket_list(get<2>(tpl));

    return 0;
}
