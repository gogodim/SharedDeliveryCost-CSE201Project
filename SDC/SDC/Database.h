#ifndef DATABASE_H
#define DATABASE_H

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <string>

namespace dbo = Wt::Dbo;

class User {
public:
    User():name{"Default"}, password{"Password"}, email{"abc@gmail.com"}, location{"France"}{};
    User(const User &u){
        this->email    = u.email;
        this->name     = u.name;
        this->password = u.password;
        this->location = u.location;
    };
    std::string  name;
    std::string  password;
    std::string  email;
    std::string  location;

    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, name,     "name");
        dbo::field(a, password, "password");
        dbo::field(a, email,    "email");
        dbo::field(a, location, "location");
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user){
        os << user.name << " is user's name";
    }
};

class Database
{
public:
    Database();
    bool add_user(const User*);
    bool find_user(const User*);
private:
    dbo::Session session;

};

#endif // DATABASE_H
