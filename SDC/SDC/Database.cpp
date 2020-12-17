#include "Database.h"

#include <Wt/WApplication.h>

using namespace Wt;

Database::Database()
{
    //std::unique_ptr<dbo::backend::Sqlite3> sqlite3{new dbo::backend::Sqlite3("blog.db")};
    std::unique_ptr<dbo::backend::Sqlite3> sqlite3 =
            cpp14::make_unique<dbo::backend::Sqlite3>(WApplication::instance()->docRoot() + "\\SDC.db");
    //
    //std::unique_ptr<dbo::backend::Sqlite3> sqlite3(new dbo::backend::Sqlite3(":memory:"));
    sqlite3->setProperty("show-queries", "true");

    session.setConnection(std::move(sqlite3));
    //std::cout<<"1: "<<session.tableName<User>()<<std::endl;

    session.mapClass<User>("user");
    //session.createTables();
    //std::cout<<"2: "<<session.tableName<User>()<<std::endl;
    //std::string path = WApplication::instance()->docRoot() + "\\SDC.db";
    //std::ifstream db(path);
    //if(db.fail()){
        //std::cout<<"Create .db file in: "<<WApplication::instance()->docRoot()<<std::endl;

    //}

//    dbo::Transaction transaction(session);

//    std::unique_ptr<User> user{new User()};
//    user->name = "Joe";
//    user->password = "Secret";
//    user->role = Role::Visitor;
//    user->karma = 13;
//    dbo::ptr<User> userPtr = session.add(std::move(user));

//    dbo::ptr<User> joe = session.find<User>().where("name = ?").bind("Joe");
//    std::cerr << "Joe has karma: " << joe->karma << std::endl;
//    dbo::ptr<User> joe2 = session.query< dbo::ptr<User> >
//      ("select u from user u").where("name = ?").bind("Joe");
//    int count = session.query<int>("select count(1) from user").where("name = ?").bind("Joe");
//    std::cout<<"Count: "<<count<<std::endl;

//      typedef dbo::collection< dbo::ptr<User> > Users;
//      Users users = session.find<User>();
//      std::cerr << "We have " << users.size() << " users:" << std::endl;
//      for (const dbo::ptr<User> &user : users)
//          std::cerr << " user " << user->name
//                    << " with karma of " << user->karma << std::endl;


}
bool Database::add_user(std::unique_ptr<User> user){
    session.mapClass<User>("user");
    dbo::Transaction transaction(session);
    std::cerr << "Add user " << user->name << " with karma of " << user->karma << std::endl;
    dbo::ptr<User> userPtr = session.add(std::move(user));
    return true;
}
