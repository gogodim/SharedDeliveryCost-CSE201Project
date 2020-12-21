#include "NotificationWidget.h"
#include <Wt/WBreak.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WAny.h>

#include "Session.h"

using namespace Wt;

NotificationWidget::NotificationWidget(const int &userID,Session *session)
{
    std::vector<Notification> notifications = session->readNotifications();
    Wt::WTable *table = addWidget(cpp14::make_unique<Wt::WTable>());
    for (int i=0;i<notifications.size();i++){
        table->elementAt(i, 0)->addWidget(std::make_unique<Wt::WText>(notifications[i].deliveryLocation));
        table->elementAt(i, 1)->addWidget(std::make_unique<Wt::WText>(notifications[i].otherOrders));
        Wt::WTableCell *cell = table->elementAt(2, 0);
        cell->setColumnSpan(2);
    }
}
    /*
    table->elementAt(0, 0)->addWidget(std::make_unique<Wt::WText>("Item @ row 0, column 0"));
    table->elementAt(0, 1)->addWidget(std::make_unique<Wt::WText>("Item @ row 0, column 1"));
    table->elementAt(1, 0)->addWidget(std::make_unique<Wt::WText>("Item @ row 1, column 0"));
    table->elementAt(1, 1)->addWidget(std::make_unique<Wt::WText>("Item @ row 1, column 1"));
    Wt::WTableCell *cell = table->elementAt(2, 0);
    cell->addWidget(std::make_unique<Wt::WText>("Item @ row 2"));
    cell->setColumnSpan(2);
*/


/*
Wt::WTable *table = addWidget(std::make_unique<Wt::WTable>());
table->elementAt(0, 0)->addWidget(std::make_unique<Wt::WText>("Item @ row 0, column 0"));
table->elementAt(0, 1)->addWidget(std::make_unique<Wt::WText>("Item @ row 0, column 1"));
table->elementAt(1, 0)->addWidget(std::make_unique<Wt::WText>("Item @ row 1, column 0"));
table->elementAt(1, 1)->addWidget(std::make_unique<Wt::WText>("Item @ row 1, column 1"));
Wt::WTableCell *cell = table->elementAt(2, 0);
cell->addWidget(std::make_unique<Wt::WText>("Item @ row 2"));
cell->setColumnSpan(2);


namespace {
  const int MaxGuesses = 9;
}

HangmanWidget::HangmanWidget(const std::string &name)
  : WContainerWidget(),
    name_(name),
    badGuesses_(0)
{
  setContentAlignment(AlignmentFlag::Center);

  title_ = addWidget(cpp14::make_unique<WText>(tr("hangman.readyToPlay")));

  word_ = addWidget(cpp14::make_unique<WordWidget>());
  statusText_ = addWidget(cpp14::make_unique<WText>());
  images_ = addWidget(cpp14::make_unique<ImagesWidget>(MaxGuesses));

  letters_ = addWidget(cpp14::make_unique<LettersWidget>());
  letters_->letterPushed().connect(this, &HangmanWidget::registerGuess);

  language_ = addWidget(cpp14::make_unique<WComboBox>());
  language_->addItem(tr("hangman.englishWords").arg(18957));
  language_->addItem(tr("hangman.dutchWords").arg(1688));

  addWidget(cpp14::make_unique<WBreak>());

  newGameButton_ = addWidget(cpp14::make_unique<WPushButton>(tr("hangman.newGame")));
  newGameButton_->clicked().connect(this, &HangmanWidget::newGame);

  letters_->hide();
}

void HangmanWidget::newGame()
{
  WString title(tr("hangman.guessTheWord"));
  title_->setText(title.arg(name_));

  language_->hide();
  newGameButton_->hide();


   // Choose a new secret word and reset the game

  Dictionary dictionary = (Dictionary) language_->currentIndex();
  word_->init(RandomWord(dictionary));
  letters_->reset();
  badGuesses_ = 0;
  images_->showImage(badGuesses_);
  statusText_->setText("");
}

void HangmanWidget::registerGuess(char c)
{
  if (badGuesses_ < MaxGuesses) {
    bool correct = word_->guess(c);

    if (!correct) {
      ++badGuesses_;
      images_->showImage(badGuesses_);
    }
  }

  if (badGuesses_ == MaxGuesses) {
    WString status = tr("hangman.youHang");
    statusText_->setText(status.arg(word_->word()));

    letters_->hide();
    language_->show();
    newGameButton_->show();

    scoreUpdated_.emit(-10);
  } else if (word_->won()) {
    statusText_->setText(tr("hangman.youWin"));
    images_->showImage(ImagesWidget::HURRAY);

    letters_->hide();
    language_->show();
    newGameButton_->show();

    scoreUpdated_.emit(20 - badGuesses_);
  }
}
*/
