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


/*#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment& env);

private:
    Wt::WLineEdit *nameEdit_;
    Wt::WText *greeting_;
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Hello world");

    root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
    nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    greeting_ = root()->addWidget(std::make_unique<Wt::WText>());
    auto greet = [this]{
      greeting_->setText("Hello there, " + nameEdit_->text());
    };
    button->clicked().connect(greet);
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
      return std::make_unique<HelloApplication>(env);
    });
}
*/
/*#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include <iostream>

#include "OrderPage.h"
//#include "Session.h"

using namespace Wt;

// Create a New Application/Page of Web
std::unique_ptr<WApplication> createApplication(const WEnvironment& env){
    auto app = cpp14::make_unique<WApplication>(env);

    //Load needy string from ResourceBundle
    app->setTitle("Shared Delivery Cost");
    app->messageResourceBundle().use(app->docRoot() + "\\" + "string");

    //Load css
    app->useStyleSheet("shared.css");

    app->root()->addWidget(cpp14::make_unique<OrderPage>());

    return app;
}

int main(int argc, char** argv){
    try{
        WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(EntryPointType::Application, createApplication);

        server.run();
    } catch (WServer::Exception& e){
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e){
        std::cerr << "exception: " << e.what() << std::endl;
    }
}*/
