/*
 * Copyright (C) 2011 Emweb bv, Herent, Belgium
 *
 * See the LICENSE file for terms of use.
 */

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
  session.addNotification(111,1111,10.1,"Doma  ","otherOrders");
  session.addNotification(111,1111,10.1,"Doma2  ","otherOrders2");

  app->setTitle("Notification");
  app->root()->addWidget(cpp14::make_unique<NotificationWidget>(2,&session));

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
