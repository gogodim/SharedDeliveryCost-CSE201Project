#ifndef DATABASE_H
#define DATABASE_H

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <string>

namespace dbo = Wt::Dbo;

enum class Role {
    Visitor = 0,
    Admin = 1,
    Alien = 42
};

class User {
public:
    std::string  name;
    std::string  password;
    Role         role;
    int          karma;

    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, name,     "name");
        dbo::field(a, password, "password");
        dbo::field(a, role,     "role");
        dbo::field(a, karma,    "karma");
    }
};

class Database
{
public:
    Database();
    bool add_user(std::unique_ptr<User>);
private:
    dbo::Session session;

};

#endif // DATABASE_H
