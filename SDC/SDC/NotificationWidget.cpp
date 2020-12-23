#include "NotificationWidget.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WAny.h>

#include "Session.h"

using namespace Wt;

NotificationTable::NotificationTable(const int &userID,Session *session)
{
    std::vector<Notification> notifications = session->readAllNotifications();
    //title_ = addWidget(std::make_unique<Wt::WText>());
    //title_->addStyleClass("title");
    //title_->setText("Those are the notifications for the user with ID:"+std::to_string(userID));
    table_ = addWidget(cpp14::make_unique<Wt::WTable>());
    table_->addStyleClass("tableNotifications");
    table_->setHeaderCount(1);
    std::string header[4] = {"OrderID","Your part","Delivery location","Order with"};
    for (int i=0;i<4;i++){
        table_->elementAt(0, i)->addWidget(std::make_unique<Wt::WText>(header[i]));
    }

    int counter = 1;
    for (int i=0;i<notifications.size();i++){
        if (notifications[i].userID==userID){
            table_->elementAt(counter, 0)->addWidget(std::make_unique<Wt::WText>(std::to_string(notifications[i].orderID)));
            table_->elementAt(counter, 1)->addWidget(std::make_unique<Wt::WText>(std::to_string(notifications[i].costShare)+"$"));
            table_->elementAt(counter, 2)->addWidget(std::make_unique<Wt::WText>(notifications[i].deliveryLocation));
            table_->elementAt(counter, 3)->addWidget(std::make_unique<Wt::WText>(notifications[i].otherOrders));
            counter++;
        }
    }

}

NotificationWidget::NotificationWidget(const int &userID,Session *session)
{
    //Wt::WPushButton *button = addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
    button_ = addWidget(std::make_unique<Wt::WPushButton>("Notifications"));
    button_->addStyleClass("buttonNotifications");
    Ntable_ = addWidget(std::make_unique<NotificationTable>(userID,&*session));
    Ntable_->hide();
    showed = false;
    button_->clicked().connect(this,&NotificationWidget::showHide);

}

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

