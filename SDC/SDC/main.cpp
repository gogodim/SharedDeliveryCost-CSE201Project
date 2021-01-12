#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include <iostream>



#include "OrderPage.h"
#include "Database.h"

using namespace Wt;

int myargc;
char** myargv;

// Create a New Application/Page of Web
std::unique_ptr<WApplication> createApplication(const WEnvironment& env){
    auto app = cpp14::make_unique<WApplication>(env);
    
    //Load needy string from ResourceBundle
    app->setTitle("Shared Delivery Cost");
    app->messageResourceBundle().use(app->docRoot() + "\\string");

    //Load css
    app->useStyleSheet("css/shared.css");
    app->root()->addWidget(cpp14::make_unique<OrderPage>(myargc, myargv));

    return app;
}

int main(int argc, char** argv){
    myargc = argc;
    myargv = argv;
    try{
        WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(EntryPointType::Application, createApplication);

        server.run();
    } catch (WServer::Exception& e){
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e){
        std::cerr << "exception: " << e.what() << std::endl;
    }
}

