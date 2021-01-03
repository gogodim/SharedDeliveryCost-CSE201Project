#ifndef DATABASE_H
#define DATABASE_H

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <string>
#include "Coordinate.h"
#include "User.h"

namespace dbo = Wt::Dbo;

class Database
{
public:
    Database();
    bool add_user(const User*);
    bool find_user(const User*);
    bool valid_user(const User*);
private:
    dbo::Session session;
};

#endif // DATABASE_H
