
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <string>

#include <Wt/WApplication.h>
#include <Wt/WLogger.h>

#include "Session.h

using namespace Wt;

Session::Session(){
    auto sqlite3 = cpp14::make_unique<Dbo::backend::Sqlite3>(WApplication::)
}