#include "Database.h"

#include <Wt/WApplication.h>
#include <fstream>

using namespace Wt;

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

    /* if there isn't a .db, create and add a default user to the database*/
    if(db.fail()){
        session.createTables();
        dbo::Transaction transaction(session);
        std::unique_ptr<User> user{new User()};
        dbo::ptr<User> userPtr = session.add(std::move(user));
    }

}

bool Database::add_user(const User* user){
    if (!Database::find_user(user)){
        dbo::Transaction transaction(session);
        std::cerr << "Add user " << user->name << " with email of " << user->email << std::endl;
        std::unique_ptr<User> userptr = std::make_unique<User>(*user);
        dbo::ptr<User> userPtr = session.add(std::move(userptr));
        return true;
    }
    return false;
}

bool Database::find_user(const User* user){
    dbo::Transaction transaction(session);
    dbo::ptr<User> u = session.find<User>().where("name = ?").bind(user->name);
    std::cerr << "Return" << u << std::endl;
    if(!u){
       std::cout<<"False"<<std::endl;
       return false;
    }
    std::cout<<"True"<<std::endl;
    return true;
}
