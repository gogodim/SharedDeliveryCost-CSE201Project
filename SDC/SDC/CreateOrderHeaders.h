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

class NewOrderWidget : public Wt::WContainerWidget
{
public:
    NewOrderWidget();
    void confirm();
    void display();

private:
    Wt::WText           *title_;

    Wt::WSelectionBox   *company_;
    Wt::WText           *company_description;

    Wt::WLineEdit       *diff_loc_;
    Wt::WText           *diff_loc_description;

    Wt::WLineEdit       *order_val_;
    Wt::WText           *order_val_description;

    Wt::WLineEdit       *maxDeliveryVal_;
    Wt::WText           *maxDelivery_description;

    Wt::WLineEdit       *radius_;
//    Wt::WSlider         *radius_
    Wt::WText           *radius_description;;
    Wt::WPushButton     *confirm_;
};

class CreateOrderApplication : public Wt::WApplication
{
public:
    CreateOrderApplication(const Wt::WEnvironment& env);

private:
//    find out later
};

#endif // CREATEORDERHEADERS_H
