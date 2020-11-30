#include <Wt/WApplication.h>
#include <Wt/WServer.h>

#include "Orderpage.h"
#include "Session.h"

#include <iostream>

using namespace Wt;

std::unique_ptr<WApplication> createApplication(const WEnvironment& env)
{
  auto app = cpp14::make_unique<WApplication>(env);

  app->setTitle("Shared Delivery Cost");
  std::cout<<"Out"<<app->appRoot()<<std::endl;
  app->messageResourceBundle().use("C:\\Users\\user\\Desktop\\Project\\boost\\strings");
  app->messageResourceBundle().use("C:\\Users\\user\\Desktop\\Project\\boost\\templates");

  app->useStyleSheet("shared.css");

  app->root()->addWidget(cpp14::make_unique<Orderpage>());

  return app;
}


int main(int argc, char **argv)
{
  try {
    WServer server(argc, argv, WTHTTP_CONFIGURATION);

    server.addEntryPoint(EntryPointType::Application, createApplication);

    Session::configureAuth();

    server.run();
  } catch (WServer::Exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}
