#ifndef USER_H
#define USER_H

#include <Wt/WDateTime.h>
#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/Auth/Dbo/AuthInfo.h>

#include <string>

using namespace Wt;

namespace dbo = Wt::Dbo;

class User;
// AuthInfo for user information
typedef Auth::Dbo::AuthInfo<User> AuthInfo;
// Users for pointer to an user in database
typedef dbo::collection< dbo::ptr<User> > Users;

class User
{
public:
    User();

    std::string name; /* a copy of auth info's user name */
    int isOrdered;
    long long amount;

    WDateTime lastOrder;
    dbo::collection<dbo::ptr<AuthInfo>> authInfos;

    template<class Action>
    void persist(Action& a)
    {
      dbo::field(a, isOrdered, "isOrdered");
      dbo::field(a, amount, "amount");
      dbo::field(a, lastOrder, "lastOrder");

      dbo::hasMany(a, authInfos, dbo::ManyToOne, "user");
    }
};

#endif // USER_H
