#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>


#include "OrderPage.h"
#include "Database.h"

using namespace Wt;

OrderPage::OrderPage(): WContainerWidget(){

    this->setStyleClass("login-page");

    /*Login layout*/
    auto Login = Wt::cpp14::make_unique<Wt::WContainerWidget>();
    Login->setHeight(300);
    Login->setWidth(200);
    Login->setStyleClass("login-box");

    /*vertical box*/
    auto vbox = Login->setLayout(Wt::cpp14::make_unique<Wt::WVBoxLayout>());

    /*name input*/
    auto hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    auto text = Wt::cpp14::make_unique<Wt::WText>("Name");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    nameEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    nameEdit_->setStyleClass("login-edit");
    nameEdit_->setFocus();

    /*name input*/
    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    text = Wt::cpp14::make_unique<Wt::WText>("Email");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    emailEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    emailEdit_->setStyleClass("login-edit");
    emailEdit_->setFocus();

    /*password input*/
    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    text = Wt::cpp14::make_unique<Wt::WText>("Password");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    passwordEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    passwordEdit_->setStyleClass("login-edit");
    passwordEdit_->setFocus();

    /*location input*/
    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    text = Wt::cpp14::make_unique<Wt::WText>("Location");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    locationEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    locationEdit_->setStyleClass("login-edit");
    locationEdit_->setFocus();


    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    /*Confirm button*/
    auto button = hbox->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Confirm")); // create a button
    button->setMargin(5, Wt::Side::Left);
    addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    button->clicked().connect(this, &OrderPage::Login);
    confirm_ = vbox->addWidget(Wt::cpp14::make_unique<Wt::WText>());

    /*Register button*/
    button = hbox->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Register")); // create a button
    button->setMargin(5, Wt::Side::Left);
    addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    button->clicked().connect(this, &OrderPage::Login);


    /*Login Page*/
    hbox = this->setLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    auto logo = Wt::cpp14::make_unique<WImage>("images/logo.png");
    logo->setStyleClass("login-image");
    hbox->addWidget(std::move(logo));
    hbox->addWidget(std::move(Login));


    //addWidget(Wt::cpp14::make_unique<WText>("Enter your name, SVP? "));

    locationEdit_->enterPressed().connect(std::bind(&OrderPage::Login, this));

    database = Wt::cpp14::make_unique<Database>();

}

void OrderPage::Login(){
    User* user{new User()};
    user->set_password((passwordEdit_->text()).toUTF8());
    user->set_email((emailEdit_->text()).toUTF8());
    user->set_address((locationEdit_->text()).toUTF8());
    user->set_username((nameEdit_->text()).toUTF8());

    database->add_user(user);
}
