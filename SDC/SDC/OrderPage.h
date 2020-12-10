#ifndef ORDERPAGE_H
#define ORDERPAGE_H

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

using namespace Wt;

class OrderPage: public WContainerWidget{

public:
    OrderPage();

private:
    Wt::WLineEdit *nameEdit_;
    Wt::WText     *greeting_;

    void greet();
};


#endif // ORDERPAGE_H
