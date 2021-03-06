#ifndef CREATEORDERHEADERS_H
#define CREATEORDERHEADERS_H

#include <string>

#include <Wt/WApplication.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/WImage.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WComboBox.h>
#include <Wt/WSplitButton.h>
#include <Wt/WBreak.h>
#include <Wt/WSelectionBox.h>
#include <Wt/WSlider.h>
#include <stdlib.h>
#include "OrderDBfirst.h"
#include "Database.h"
#include "UserDB.h"
#include "Coordinate.h"

class NewOrderWidget : public Wt::WContainerWidget
{
public:
    NewOrderWidget(const std::string &username, Database *session);
    void confirm();
    void display();


private:
    Database            *session_;
    Wt::WText           *title_;

    Wt::WSelectionBox   *company_;
    Wt::WText           *company_description;

    Wt::WLineEdit       *diff_loc_;
    Wt::WText           *diff_loc_description;
    Wt::WLineEdit       *postal_;
    Wt::WText           *postal_description;
    Wt::WLineEdit       *city_;
    Wt::WText           *city_description;
    Coordinate          *address;

    Wt::WLineEdit       *order_val_;
    Wt::WText           *order_val_description;

    Wt::WLineEdit       *maxDeliveryVal_;
    Wt::WText           *maxDelivery_description;

    Wt::WLineEdit       *radius_;
//    Wt::WSlider         *radius_
    Wt::WText           *radius_description;
    Wt::WPushButton     *confirm_;

    std::string         username_;
};



#endif // CREATEORDERHEADERS_H
