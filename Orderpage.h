#ifndef ORDERPAGE_H
#define ORDERPAGE_H

#include <Wt/WContainerWidget.h>

#include "Session.h"

using namespace Wt;

namespace Wt {
  class WStackedWidget;
  class WAnchor;
}

class OrderWidget;
class HighAmountWidget;
class Session;

class Orderpage: public WContainerWidget
{
public:
    Orderpage();
    void handleInternalPath(const std::string &internalPath);

private:
    WStackedWidget    *mainStack_;
    OrderWidget     *order_;
    HighAmountWidget  *amounts_;
    WContainerWidget  *links_;
    WAnchor           *backToGameAnchor_;
    WAnchor           *scoresAnchor_;

    Session session_;

    void onAuthEvent();
    void showGame();
    void showHighScores();
};

#endif // ORDERPAGE_H
