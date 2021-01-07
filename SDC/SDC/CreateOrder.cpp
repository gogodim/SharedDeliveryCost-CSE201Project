#include "CreateOrderHeaders.h"
#include <iostream>

namespace dbo = Wt::Dbo;
using namespace Wt;

NewOrderWidget::NewOrderWidget(){
//    setContentAlignment(AlignmentFlag::Left);

    maxDelivery_description = addWidget(std::make_unique<WText>("max delivery:"));
    maxDeliveryVal_  = addWidget(std::make_unique<WLineEdit>());
    addWidget(std::make_unique<WBreak>());

    diff_loc_description = addWidget(std::make_unique<WText>("Different address"));
    diff_loc_  = addWidget(std::make_unique<WLineEdit>("(optional)"));
    addWidget(std::make_unique<WBreak>());

    order_val_description =addWidget(std::make_unique<WText>("Order value"));
    order_val_  = addWidget(std::make_unique<WLineEdit>());
    addWidget(std::make_unique<WBreak>());
//    radius_ = addWidget(std::make_unique<WSlider>());
    radius_description =addWidget(std::make_unique<WText>("How far can you pick up your order"));
    radius_ = addWidget(std::make_unique<WLineEdit>());
    addWidget(std::make_unique<WBreak>());
//    radius_->setTickInterval(10);
//    radius_->setMinimum(0);
//    radius_->setMaximum(1000);
    company_description = addWidget(std::make_unique<WText>("Select store"));
    company_ = addWidget(std::make_unique<WSelectionBox>());
    company_->addItem("Ikea");
    company_->addItem("Auchan");
    company_->addStyleClass("boxTest");
    company_->setVerticalSize(1);
    auto b5 = addWidget(std::make_unique<WBreak>());

    confirm_ = addWidget(std::make_unique<Wt::WPushButton>("Confirm"));

    this->hide();
};

void NewOrderWidget::display(){
    if(this->isHidden()){
        this->show();
    } else {
        this->hide();
    }
};

CreateOrderApplication::CreateOrderApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
    {
    setTitle("Create Order");
    useStyleSheet("teststyle.css");
    Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Create a new order"));
    NewOrderWidget *widget = root()->addWidget(std::make_unique<NewOrderWidget>());
    widget->setStyleClass("NewOrderWidget");
    auto greet = [widget]{
        if(widget->isHidden()){
            widget->show();
        } else {
            widget->hide();
        }
    };

    button->clicked().connect(greet);
}
/*
HangmanWidget::HangmanWidget(const std::string &name)
    : name_(name),
      badGuesses_(0)
{
    setContentAlignment(AlignmentFlag::Center);

    title_ = addWidget(std::make_unique<WText>(tr("hangman.readyToPlay")));

    word_ = addWidget(std::make_unique<WString>());
    statusText_ = addWidget(std::make_unique<WText>());
    images_ = addWidget(std::make_unique<WImage>(MaxGuesses));

    letters_ = addWidget(std::make_unique<WString>());
//    letters_->letterPushed().connect(this, &HangmanWidget::registerGuess);

    language_ = addWidget(std::make_unique<WComboBox>());
    language_->addItem(tr("hangman.englishWords").arg(18957));
    language_->addItem(tr("hangman.dutchWords").arg(1688));

    addWidget(std::make_unique<WBreak>());

    newGameButton_ = addWidget(std::make_unique<WPushButton>(tr("hangman.newGame")));
    newGameButton_->clicked().connect(this, &HangmanWidget::newGame);

//    letters_->hide();
}
HelloApplication::HelloApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Create Order");
    root()->addWidget(std::make_unique<Wt::WText>("Hello another widget"));
    root()->addWidget(std::make_unique<HangmanWidget>());
    nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    greeting_ = root()->addWidget(std::make_unique<Wt::WText>());
    auto greet = [this]{
      greeting_->setText("Hello there, " + nameEdit_->text());
    };
    button->clicked().connect(greet);
}
*/
