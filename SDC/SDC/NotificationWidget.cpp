#include "NotificationWidget.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WAny.h>
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>
#include "helpingFunctions.h"
#include "Database.h"

using namespace Wt;

NotificationTable::NotificationTable(const std::string &username,Database *session)
{
    std::vector<Notification> notifications = session->readAllNotifications();
    table_ = addWidget(cpp14::make_unique<Wt::WTable>());
    table_->addStyleClass("tableNotifications");
    table_->setHeaderCount(1);
    std::string header[4] = {"OrderID","Your part","Delivery location","Order with"};
    for (int i=0;i<4;i++){
        table_->elementAt(0, i)->addWidget(std::make_unique<Wt::WText>(header[i]));
    }

    int counter = 1;
    for (int i=0;i<notifications.size();i++){
        if (notifications[i].username==username){

            Wt::WLink link = Wt::WLink(notifications[i].deliveryLocation);
            link.setTarget(Wt::LinkTarget::NewWindow);
            std::unique_ptr<Wt::WAnchor> anchor = Wt::cpp14::make_unique<Wt::WAnchor>(link,"");
            table_->elementAt(counter, 0)->addWidget(std::make_unique<Wt::WText>(std::to_string(notifications[i].orderID)));
            table_->elementAt(counter, 1)->addWidget(std::make_unique<Wt::WText>((precision_2(notifications[i].costShare))+"$"));
            table_->elementAt(counter, 2)->addWidget( Wt::cpp14::make_unique<Wt::WAnchor>(link,"See on google maps"));
            table_->elementAt(counter, 3)->addWidget(std::make_unique<OtherOrdersTable>(notifications[i].otherOrders));
            counter++;
        }
    }

}

NotificationWidget::NotificationWidget(const std::string &username,Database *session)
{
    button_ = addWidget(std::make_unique<Wt::WPushButton>("Notifications"));
    button_->addStyleClass("buttonNotifications");
    Ntable_ = addWidget(std::make_unique<NotificationTable>(username,&*session));
    Ntable_->hide();
    showed = false;
    button_->clicked().connect(this,&NotificationWidget::showHide);
    addWidget(std::make_unique<Wt::WText>("Logged in as: " + username));
    CreateOrderButton_ = addWidget(std::make_unique<Wt::WPushButton>("Create Order"));
    CreateOrderButton_->addStyleClass("CreateOrderButton");
    CreateOrderWidget_ = addWidget(std::make_unique<NewOrderWidget>(username,&*session));
    CreateOrderWidget_->addStyleClass("CreateOrderWidget");
    CreateOrderWidget_->hide();
    CreateOrderButton_->clicked().connect(CreateOrderWidget_, &NewOrderWidget::display);

}

/*
Function to show and hide the table alternatively with each click on the button.
*/
void NotificationWidget::showHide()
{
    if(this->showed==true)
    {
        this->showed=false;
        this->Ntable_->hide();
    }
    else
    {
        this->showed=true;
        this->Ntable_->show();

    }
}

/*
Function to split the other order string into something more useful.
*/
std::vector< std::vector<std::string> > splitt(std::string otherOrders)
{
    std::vector< std::vector<std::string> > for_return;
    std::string delimiter = " ";
    std::string delimiter2 = ",";
    size_t pos = 0;
    std::string token;
    while ((pos = otherOrders.find(delimiter)) != std::string::npos) {
        token = otherOrders.substr(0, pos);
        size_t pos_temp = 0;
        std::vector<std::string> tokens;
        while((pos_temp = token.find(delimiter2)) != std::string::npos) {
            tokens.push_back(token.substr(0, pos_temp));
            token.erase(0, pos_temp + delimiter2.length());
        }
        for_return.push_back(tokens);
        otherOrders.erase(0, pos + delimiter.length());
    }
    return for_return;
}

OtherOrdersTable::OtherOrdersTable(std::string otherOrders)
{
    table_ = addWidget(cpp14::make_unique<Wt::WTable>());
    table_->addStyleClass("tableNotifications");
    table_->setHeaderCount(1);
    std::string header[3] = {"Username","Contact","Their part"};
    for (int i=0;i<3;i++){
        table_->elementAt(0, i)->addWidget(std::make_unique<Wt::WText>(header[i]));
    }
    std::vector< std::vector<std::string> > splitted = splitt(otherOrders);

    for (int i = 0; i < splitted.size(); i++)
    {
        for (int j=0; j < 3; j++){
            if (j==2) table_->elementAt(i+1, j)->addWidget(std::make_unique<Wt::WText>(precision_2(splitted[i][j])+"$"));
            else table_->elementAt(i+1, j)->addWidget(std::make_unique<Wt::WText>(splitted[i][j]));
        }
    }
}


