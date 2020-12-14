#ifndef USER_H
#define USER_H

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
  std::string name;
  std::string password;
  Role        role;
  std::string email;

  template<class Action>
  void persist(Action& a)
  {
    dbo::field(a, name,     "name");
    dbo::field(a, password, "password");
    dbo::field(a, role,     "role");
    dbo::field(a, email,    "email");
  }
};

#endif // USER_H