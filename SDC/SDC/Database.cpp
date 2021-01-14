#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <string>
#include "notification.h"
#include <Wt/WApplication.h>
#include <Wt/WLogger.h>
#include "Database.h"
#include "Coordinate.h"
#include <fstream>
using namespace Wt;
namespace dbo = Wt::Dbo;


Database::Database()
{
    /* check if .db file exists*/
    std::string path = WApplication::instance()->docRoot() + "\\SDC.db";
    std::ifstream db(path, std::ifstream::in);

    /*create or open .db file*/
    std::unique_ptr<dbo::backend::Sqlite3> sqlite3 =
            cpp14::make_unique<dbo::backend::Sqlite3>(WApplication::instance()->docRoot() + "\\SDC.db");
    sqlite3->setProperty("show-queries", "true");
    session.setConnection(std::move(sqlite3));

    /* load user class from table*/
    session.mapClass<UserDB>("user");
    session.mapClass<Notification>("Notification");
    session.mapClass<OrderDB>("Order");
    session.mapClass<CompanyDB>("Company");
    session.mapClass<BucketDB>("BucketDB");

    /* if there isn't a .db, create and add a default user to the database*/
    dbo::Transaction transaction(session);
    try {
      std::cout<<"Create a new database in" + path << std::endl;
      session.createTables();
      dbo::Transaction transaction(session);
      std::unique_ptr<UserDB> user{new UserDB()};
      dbo::ptr<UserDB> userPtr = session.add(std::move(user));
      log("info") << "Database created";
    } catch (...) {
      log("info") << "Using existing database";
    }
    transaction.commit();

}

bool Database::add_user(const UserDB* user){
    if (!Database::find_user(user)){
        dbo::Transaction transaction(session);
        std::unique_ptr<UserDB> userptr = std::make_unique<UserDB>(*user);
        std::cerr << "Add user " << userptr->get_username()<< " with email of " << userptr->get_email() << std::endl;
        std::cout<< "latitude in databasecpp: " << userptr->get_coordinates().get_latitude() << std::endl;
        dbo::ptr<UserDB> userPtr = session.add(std::move(userptr));
        return true;
    }
    return false;
}



int Database::addOrder(std::string username, double maxDeliveryCost, double orderCost,
                        double radius, std::string store, string postal, string city, string street){

    dbo::Transaction transaction(session);
    dbo::ptr<UserDB> u = session.find<UserDB>().where("username = ?").bind(username);
    CompanyDB comp = CompanyDB();
    Coordinate coord = u->get_coordinates();
    double lat = coord.get_latitude();
    double lon = coord.get_longitude();
    Address address = u->get_useraddress();
    if (postal != "" && city!="" && street!=""){
        address = Address(postal, city, street);
        Coordinate coord = Coordinate();
        lat = coord.get_latitude();
        lon = coord.get_longitude();
    };
    typedef dbo::collection< dbo::ptr<OrderDB> > OrderDBs;

    OrderDBs temp = session.find<OrderDB>();


    std::unique_ptr<OrderDB> ordptr = std::make_unique<OrderDB>(temp.size()+1,   username,store, orderCost,
                                                                maxDeliveryCost, radius,
                                                                address.get_postalcode(), address.get_city(),
                                                                address.get_street(), lat, lon);
    dbo::ptr<OrderDB> ordrPtr = session.add(std::move(ordptr));
    return temp.size()+1;
}


bool Database::find_user(const UserDB* user){
    dbo::Transaction transaction(session);
    std::unique_ptr<UserDB> userptr = std::make_unique<UserDB>(*user);
    dbo::ptr<UserDB> u = session.find<UserDB>().where("username = ?").bind(userptr->get_username());
    std::cerr << "Return" << u << std::endl;
    if(!u){
       std::cout<<"False"<<std::endl;
       return false;
    }
    std::cout<<"True"<<u->get_username()<<std::endl;
    return true;
}

bool Database::valid_user(const UserDB* user){
    dbo::Transaction transaction(session);
    std::unique_ptr<UserDB> userptr = std::make_unique<UserDB>(*user);
    dbo::ptr<UserDB> u = session.find<UserDB>().where("username = ?").bind(userptr->get_username());
    std::cerr << "Return" << u << std::endl;
    if(!u){
       //std::cout<<"False"<<std::endl;
       return false;
    }
    //std::cout<<"True"<<std::endl;
    else if(u->get_password() == userptr->get_password()){
        return true;
    }
    return false;
}


dbo::ptr<Notification> Database::notification() const
{
    return dbo::ptr<Notification>();
}

std::vector<Notification> Database::readAllNotifications()
{
    dbo::Transaction transaction(session);
    std::vector<Notification> result;

    Notifications temp = session.find<Notification>();

    for (Notifications::const_iterator i = temp.begin(); i != temp.end(); ++i) {
      dbo::ptr<Notification> notification = *i;
      result.push_back(*notification);
    }

    transaction.commit();

    return result;
}

void Database::addNotification(std::string username1,int orderID1,double costShare1,std::string deliveryLocation1,std::string otherOrders1)
{
    dbo::Transaction transaction(session);

    std::unique_ptr<Notification> notification{new Notification()};
    notification->costShare = costShare1;
    notification->deliveryLocation = deliveryLocation1;
    notification->orderID = orderID1;
    notification->otherOrders = otherOrders1;
    notification->username = username1;
    dbo::ptr<Notification> temp = session.add(std::move(notification));

}

list<Bucket> Database::createBucketList(){
    dbo::Transaction transaction(session);
    list<Bucket> for_return;
    typedef dbo::collection< dbo::ptr<BucketDB> > BucketDBs;
    BucketDBs temp = session.find<BucketDB>();

    for (BucketDBs::const_iterator i = temp.begin(); i != temp.end(); ++i) {
      dbo::ptr<BucketDB> bucketDB = *i;
      list<Order> orders;
      std::vector<int> orderIDs = splitOrderIDs(bucketDB->orderIDs);
      dbo::ptr<CompanyDB> c = session.find<CompanyDB>().where("name = ?").bind(bucketDB->companyname);
      Company comp = Company(bucketDB->companyname,splitCompOprions(c->compressedOptions));
      for(auto& row:orderIDs){
          dbo::ptr<OrderDB> o = session.find<OrderDB>().where("orderID = ?").bind(row);
          dbo::ptr<UserDB> u = session.find<UserDB>().where("username = ?").bind(o->username);

          orders.push_back(Order(row,
                                 User(o->username,
                                      u->get_password(),
                                      u->get_name(),
                                      u->get_surname(),
                                      u->get_coordinates(),
                                      u->get_email()),
                                 comp,
                                 o->value,
                                 o->delivery_cost,
                                 o->distance, // in meters
                                 Coordinate(o->latitude,o->longitude)));
      }





      Bucket newBucket = Bucket(comp,
                       orders,
                       bucketDB->cur_amount,
                       bucketDB->cur_cost,
                       bucketDB->max_cost,
                       bucketDB->completion,
                       Coordinate(bucketDB->lat,bucketDB->lo));
      for_return.push_back(newBucket);
    }

    transaction.commit();

    return for_return;
}

Order Database::createOrderForProcess(int orderID){
    dbo::ptr<OrderDB> o = session.find<OrderDB>().where("orderID = ?").bind(orderID);
    dbo::ptr<UserDB> u = session.find<UserDB>().where("username = ?").bind(o->username);
    dbo::ptr<CompanyDB> c = session.find<CompanyDB>().where("name = ?").bind(o->companyname);
    Company comp = Company(o->companyname,splitCompOprions(c->compressedOptions));
    Order ord = Order(orderID,
                                     User(u->get_username(),
                                          u->get_password(),
                                          u->get_name(),
                                          u->get_surname(),
                                          Coordinate(u->get_coordinates().get_latitude(),u->get_coordinates().get_longitude()),
                                          u->get_email()),
                                     comp,
                                     o->value,
                                     o->delivery_cost,
                                     o->distance,
                                     Coordinate(u->get_coordinates().get_latitude(),u->get_coordinates().get_longitude()));
    return ord;
}
