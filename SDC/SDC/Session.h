#ifndef SESSION_H
#define SESSION_H

#include <vector>

#include <Wt/Auth/Login.h>

#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>
#include <Wt/Dbo/backend/Sqlite3.h>

#include "User.h"

using namespace Wt;
//typedef Auth::Dbo::User<AuthInfo> USerDatabase;

// Session Class used to hold users that connect to this website
class Session{

public:
    static void configureAuth();
    Session();
    ~Session();

    std::string userName() const;

private:
    mutable Dbo::Session session_;

};

#endif // SESSION_H
