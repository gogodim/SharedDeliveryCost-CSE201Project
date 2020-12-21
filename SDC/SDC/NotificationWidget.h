#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H
#include <vector>
#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>

class Session;
class Notification;


class NotificationWidget: public Wt::WContainerWidget
{
public:
  NotificationWidget(const int &userID,Session *session);

  //Wt::Signal<int>& scoreUpdated() { return scoreUpdated_; }

private:
  Wt::WText                 *title_;
  Wt::WTable                *table_;

  Session *session_;

  void addToTable(Notification newNotification);
  void reloadTable();
};

#endif // NOTIFICATIONWIDGET_H
