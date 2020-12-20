#include "Session.h"

#include <Wt/WApplication.h>
#include <Wt/WLogger.h>

#ifndef WT_WIN32
#include <unistd.h>
#endif

#if !defined(WT_WIN32) && !defined(__CYGWIN__) && !defined(ANDROID)
#define HAVE_CRYPT
#ifndef _XOPEN_CRYPT
#include <crypt.h>
#endif // _XOPEN_CRYPT
#endif

namespace dbo = Wt::Dbo;

namespace {

#ifdef HAVE_CRYPT
class UnixCryptHashFunction : public Auth::HashFunction
  {
  public:
    virtual std::string compute(const std::string& msg,
                const std::string& salt) const
    {
      std::string md5Salt = "$1$" + salt;
      return crypt(msg.c_str(), md5Salt.c_str());
    }

    virtual bool verify(const std::string& msg,
            const std::string& salt,
            const std::string& hash) const
    {
      return crypt(msg.c_str(), hash.c_str()) == hash;
    }

    virtual std::string name () const {
      return "crypt";
    }
  };
#endif // HAVE_CRYPT
}



Session::Session()
{
  auto sqlite3 = cpp14::make_unique<Dbo::backend::Sqlite3>(WApplication::instance()->appRoot() + "hangman.db");
  sqlite3->setProperty("show-queries", "true");
  session_.setConnection(std::move(sqlite3));

  session_.mapClass<Notification>("notification");

  dbo::Transaction transaction(session_);
  try {
    session_.createTables();
    log("info") << "Database created";
  } catch (...) {
    log("info") << "Using existing database";
  }

  transaction.commit();
}

Session::~Session()
{
}

dbo::ptr<Notification> Session::notification() const
{
    return dbo::ptr<Notification>();
}







