#include "Orderpage.h"

#include <Wt/WAnchor.h>
#include <Wt/WText.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WApplication.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/RegistrationModel.h>

Orderpage::Orderpage():
    WContainerWidget(),
    order_(0),
    amounts_(0)
{
    session_.login().changed().connect(this, &Orderpage::onAuthEvent);

   std::unique_ptr<Auth::AuthModel> authModel
       = cpp14::make_unique<Auth::AuthModel>(Session::auth(), session_.users());
   authModel->addPasswordAuth(&Session::passwordAuth());
   authModel->addOAuth(Session::oAuth());

   std::unique_ptr<Auth::AuthWidget> authWidget
       = cpp14::make_unique<Auth::AuthWidget>(session_.login());
   auto authWidgetPtr = authWidget.get();
   authWidget->setModel(std::move(authModel));
   authWidget->setRegistrationEnabled(true);

   std::unique_ptr<WText> title(cpp14::make_unique<WText>("<h1>A Shared Delivery Cost: C++ Project</h1>"));
   addWidget(std::move(title));

   addWidget(std::move(authWidget));

   mainStack_ = new WStackedWidget();
   mainStack_->setStyleClass("gamestack");
   addWidget(std::unique_ptr<WStackedWidget>(mainStack_));

   links_ = new WContainerWidget();
   links_->setStyleClass("links");
   links_->hide();
   addWidget(std::unique_ptr<WContainerWidget>(links_));

   backToGameAnchor_ = links_->addWidget(cpp14::make_unique<WAnchor>("/start", "Gaming Grounds"));
   backToGameAnchor_->setLink(WLink(LinkType::InternalPath, "/start"));

   scoresAnchor_ = links_->addWidget(cpp14::make_unique<WAnchor>("/highamounts", "Highscores"));
   scoresAnchor_->setLink(WLink(LinkType::InternalPath, "/highamounts"));

   WApplication::instance()->internalPathChanged()
     .connect(this, &Orderpage::handleInternalPath);

   authWidgetPtr->processEnvironment();
}

void Orderpage::onAuthEvent()
{
  if (session_.login().loggedIn()) {
    links_->show();
    handleInternalPath(WApplication::instance()->internalPath());
  } else {
    mainStack_->clear();
    order_ = 0;
    amounts_ = 0;
    links_->hide();
  }
}

void Orderpage::handleInternalPath(const std::string &internalPath)
{
  if (session_.login().loggedIn()) {
    if (internalPath == "/start")
      showGame();
    else if (internalPath == "/highamounts")
      showHighScores();
    else
      WApplication::instance()->setInternalPath("/start",  true);
  }
}

void Orderpage::showHighScores()
{
  /*if (!scores_)
    scores_ = mainStack_->addWidget(cpp14::make_unique<HighScoresWidget>(&session_));

  mainStack_->setCurrentWidget(scores_);
  scores_->update();

  backToGameAnchor_->removeStyleClass("selected-link");
  scoresAnchor_->addStyleClass("selected-link");*/
}

void Orderpage::showGame()
{
  /*if (!game_) {
    game_ = mainStack_->addWidget(cpp14::make_unique<HangmanWidget>(session_.userName()));
    game_->scoreUpdated().connect(std::bind(&Session::addToScore,&session_,std::placeholders::_1));
  }

  mainStack_->setCurrentWidget(game_);

  backToGameAnchor_->addStyleClass("selected-link");
  scoresAnchor_->removeStyleClass("selected-link");*/
}
