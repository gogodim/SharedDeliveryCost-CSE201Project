#ifndef ORDERPAGE_H
#define ORDERPAGE_H

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "Database.h"

using namespace Wt;

class OrderPage: public WContainerWidget{

public:
    OrderPage();

private:
    Wt::WLineEdit                  *nameEdit_;
    Wt::WLineEdit                  *passwordEdit_;
    Wt::WText                      *confirm_;
    Database      database;

    void Login();
    void Go_Register();
};


#endif // ORDERPAGE_H
