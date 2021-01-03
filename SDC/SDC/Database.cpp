#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <string>
#include "notification.h"
#include <Wt/WApplication.h>
#include <Wt/WLogger.h>
#include "Database.h"
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
    session.mapClass<User>("user");

    session.mapClass<Notification>("Notification");

    /* if there isn't a .db, create and add a default user to the database*/
    dbo::Transaction transaction(session);
    try {
      std::cout<<"Create a new database in" + path << std::endl;
      session.createTables();
      dbo::Transaction transaction(session);
      std::unique_ptr<User> user{new User()};
      dbo::ptr<User> userPtr = session.add(std::move(user));
      log("info") << "Database created";
    } catch (...) {
      log("info") << "Using existing database";
    }
    transaction.commit();

}

bool Database::add_user(const User* user){
    if (!Database::find_user(user)){
        dbo::Transaction transaction(session);
        std::unique_ptr<User> userptr = std::make_unique<User>(*user);
        std::cerr << "Add user " << userptr->get_username()<< " with email of " << userptr->get_email() << std::endl;
        dbo::ptr<User> userPtr = session.add(std::move(userptr));
        return true;
    }
    return false;
}

bool Database::find_user(const User* user){
    dbo::Transaction transaction(session);
    std::unique_ptr<User> userptr = std::make_unique<User>(*user);
    dbo::ptr<User> u = session.find<User>().where("username = ?").bind(userptr->get_username());
    std::cerr << "Return" << u << std::endl;
    if(!u){
       std::cout<<"False"<<std::endl;
       return false;
    }
    std::cout<<"True"<<std::endl;
    return true;
}

bool Database::valid_user(const User* user){
    dbo::Transaction transaction(session);
    std::unique_ptr<User> userptr = std::make_unique<User>(*user);
    dbo::ptr<User> u = session.find<User>().where("username = ?").bind(userptr->get_username());
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

