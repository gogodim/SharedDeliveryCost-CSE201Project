#include "Database.h"

#include <Wt/WApplication.h>

using namespace Wt;

Database::Database()
{
    auto sqlite3 = cpp14::make_unique<dbo::backend::Sqlite3>(WApplication::instance()->docRoot() + "\\SDC.db");
    std::cout<<"Create .db file in: "<<WApplication::instance()->docRoot()<<std::endl;
    //std::unique_ptr<dbo::backend::Sqlite3> sqlite3(new dbo::backend::Sqlite3(":memory:"));
    sqlite3->setProperty("show-queries", "true");

    dbo::Session session;
    session.setConnection(std::move(sqlite3));

    session.mapClass<User>("user");

    session.createTables();

    dbo::Transaction transaction(session);

    std::unique_ptr<User> user{new User()};
    user->name = "Joe";
    user->password = "Secret";
    user->role = Role::Visitor;
    user->karma = 13;

    dbo::ptr<User> userPtr = session.add(std::move(user));

}
