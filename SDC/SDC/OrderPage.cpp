#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "OrderPage.h"
#include "Database.h"

using namespace Wt;

OrderPage::OrderPage(): WContainerWidget(){
    addWidget(Wt::cpp14::make_unique<WText>("Enter your name, SVP? "));

    nameEdit_ = this->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>()); // allow text input
    nameEdit_->setFocus();

    emailEdit_ = this->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>()); // allow text input
    emailEdit_->setFocus();

    passwordEdit_ = this->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>()); // allow text input
    passwordEdit_->setFocus();

    locationEdit_ = this->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>()); // allow text input
    locationEdit_->setFocus();

    auto button = this->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Confirm")); // create a button
    button->setMargin(5, Wt::Side::Left);

    addWidget(Wt::cpp14::make_unique<Wt::WBreak>());  

    addWidget(cpp14::make_unique<WImage>("images\\logo.png"));

    confirm_ = this->addWidget(Wt::cpp14::make_unique<Wt::WText>());

    button->clicked().connect(this, &OrderPage::greet);

    nameEdit_->enterPressed().connect(std::bind(&OrderPage::greet, this));

    database = Wt::cpp14::make_unique<Database>();


}

void OrderPage::greet(){
    std::unique_ptr<User> user{new User()};
    user->name = "Yarou";
    user->password = "123456";
    user->role = Role::Visitor;
    user->karma = 13;
    database->add_user(std::move(user));

    confirm_->setText("Confirm input " + nameEdit_->text() + emailEdit_->text() + locationEdit_->text());
}
