#include <Wt/WApplication.h>
#include <Wt/WServer.h>

#include "NotificationWidget.h"
#include "Session.h"

using namespace Wt;

class NotificationWidget;

std::unique_ptr<WApplication> createApplication(const WEnvironment& env)
{
  auto app = cpp14::make_unique<WApplication>(env);
  Session session;
  //*
  session.addNotification(111,1000,10.1,"Address 0","username1,contact1,pays1, username2,contact2,pays2, ");
  session.addNotification(112,1001,100,"Address 1","username1,contact1,pays1, username2,contact2,pays2, ");
  session.addNotification(112,1002,40.4,"Address 2","username1,contact1,pays1, username2,contact2,pays2, ");
  session.addNotification(112,1003,200,"Address 3","username3,contact3,pays3, ");
  //*/
  app->setTitle("Notification");
  app->useStyleSheet("CSS/style.css");
  app->root()->addWidget(cpp14::make_unique<NotificationWidget>(112,&session));

  return app;
}
/*
 * This is just so we have a change here
int main(int argc, char **argv)
{
  try {
    WServer server(argc, argv, WTHTTP_CONFIGURATION);

    server.addEntryPoint(EntryPointType::Application, createApplication);

    server.run();
  } catch (WServer::Exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}
*/
