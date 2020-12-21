#include "Session.h"
#include "notification.h"

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
  auto sqlite3 = cpp14::make_unique<Dbo::backend::Sqlite3>(WApplication::instance()->appRoot() + "notification.db");
  sqlite3->setProperty("show-queries", "true");
  session_.setConnection(std::move(sqlite3));

  session_.mapClass<Notification>("Notification");

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

std::vector<Notification> Session::readNotifications()
{
    dbo::Transaction transaction(session_);
    std::vector<Notification> result;
    //std::vector<User> result;

    Notifications temp = session_.find<Notification>();

    for (Notifications::const_iterator i = temp.begin(); i != temp.end(); ++i) {
      dbo::ptr<Notification> notification = *i;
      result.push_back(*notification);
    }

    transaction.commit();

    return result;
}



void Session::addNotification(int userID1,int orderID1,double costShare1,std::string deliveryLocation1,std::string otherOrders1)
{
    dbo::Transaction transaction(session_);

    std::unique_ptr<Notification> notification{new Notification()};
    notification->costShare = costShare1;
    notification->deliveryLocation = deliveryLocation1;
    notification->orderID = orderID1;
    notification->otherOrders = otherOrders1;
    notification->userID = userID1;
    dbo::ptr<Notification> temp = session_.add(std::move(notification));

}


