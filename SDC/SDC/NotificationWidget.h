#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H
#include <vector>
#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WPushButton.h>

#include "CreateOrderHeaders.h"

class Database;
class Notification;

/*
Represents only the table with all the notifications.
*/
class NotificationTable: public Wt::WContainerWidget
{
public:
  NotificationTable(const std::string &username,Database *session);

private:
  Wt::WText                 *title_;
  Wt::WTable                *table_;

  Database      *session_;

  void addToTable(Notification newNotification);
  void reloadTable();
};

/*
Represents the whole notification widget with the notification button and the notification table.
*/
class NotificationWidget: public Wt::WContainerWidget
{
public:
  NotificationWidget(const std::string &username,Database *session);

private:
  Wt::WContainerWidget              *container_;
  Wt::WPushButton                   *button_;
  NotificationTable                 *Ntable_;

  Wt::WPushButton                   *CreateOrderButton_;
  NewOrderWidget                    *CreateOrderWidget_;

  bool                               showed;
  void showHide();
  Wt::WTable createTableOrder(std::string otherOrders);
  Database      *session_;

};

/*
Class for representing the small tables inside the big table to show the info of the other users ordering with the given user.
*/
class OtherOrdersTable: public Wt::WContainerWidget
{
public:
  OtherOrdersTable(std::string otherOrders);

private:
  Wt::WTable                *table_;
};

#endif // NOTIFICATIONWIDGET_H
