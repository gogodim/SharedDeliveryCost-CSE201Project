#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H
#include <vector>
#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WPushButton.h>


class Session;
class Notification;


class NotificationTable: public Wt::WContainerWidget
{
public:
  NotificationTable(const int &userID,Session *session);

private:
  Wt::WText                 *title_;
  Wt::WTable                *table_;

  Session *session_;

  void addToTable(Notification newNotification);
  void reloadTable();
};

class NotificationWidget: public Wt::WContainerWidget
{
public:
  NotificationWidget(const int &userID,Session *session);

private:
  Wt::WContainerWidget              *container_;
  Wt::WPushButton                   *button_;
  NotificationTable                 *Ntable_;
  bool                               showed;
  void showHide();
  Wt::WTable createTableOrder(std::string otherOrders);

  Session *session_;
};

class OtherOrdersTable: public Wt::WContainerWidget
{
public:
  OtherOrdersTable(std::string otherOrders);

private:
  Wt::WTable                *table_;
};

#endif // NOTIFICATIONWIDGET_H
