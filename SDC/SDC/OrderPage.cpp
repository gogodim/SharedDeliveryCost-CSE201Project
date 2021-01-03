#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include "NotificationWidget.h"

#include "OrderPage.h"
#include "RegisterPage.h"
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

    /*username input*/
    auto hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    auto text = Wt::cpp14::make_unique<Wt::WText>("Username");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    nameEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    nameEdit_->setStyleClass("login-edit");
    nameEdit_->setFocus();

    /*email input
    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    text = Wt::cpp14::make_unique<Wt::WText>("Email");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    emailEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    emailEdit_->setStyleClass("login-edit");
    emailEdit_->setFocus();*/

    /*password input*/
    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    text = Wt::cpp14::make_unique<Wt::WText>("Password");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    passwordEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    passwordEdit_->setEchoMode(EchoMode::Password);
    passwordEdit_->setStyleClass("login-edit");
    passwordEdit_->setFocus();

    /*address input
    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    text = Wt::cpp14::make_unique<Wt::WText>("Address");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    locationEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    locationEdit_->setStyleClass("login-edit");
    locationEdit_->setFocus();*/


    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());

    /*Register button*/
    auto button = hbox->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Register")); // create a button
    button->setMargin(5, Wt::Side::Left);
    addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    button->clicked().connect(this, &OrderPage::Go_Register);

    /*Confirm button*/
    button = hbox->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Confirm")); // create a button
    button->setMargin(5, Wt::Side::Left);
    addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    button->clicked().connect(this, &OrderPage::Login);
    confirm_ = vbox->addWidget(Wt::cpp14::make_unique<Wt::WText>());

    /*Login Page*/
    hbox = this->setLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    auto logo = Wt::cpp14::make_unique<WImage>("images/logo.png");
    logo->setStyleClass("login-image");
    hbox->addWidget(std::move(logo));
    hbox->addWidget(std::move(Login));

    /*Confirm Message*/



    //addWidget(Wt::cpp14::make_unique<WText>("Enter your name, SVP? "));

    passwordEdit_->enterPressed().connect(std::bind(&OrderPage::Login, this));

    //Database database;

    //database.addNotification("G",1000,10.1,"Address 0","username1,contact1,pays1, username2,contact2,pays2, ");


}

void OrderPage::Login(){
    User* user{new User()};
    user->set_password((passwordEdit_->text()).toUTF8());
    user->set_username((nameEdit_->text()).toUTF8());
    bool find_flag = database.find_user(user);
    if(find_flag){
        bool valid_flag = database.valid_user(user);
        if(valid_flag){
            confirm_->setText("Login Successful");
            //std::move(database);
            this->hide();
            //this->removeFromParent();
            WApplication::instance()->useStyleSheet("CSS/style.css");
            WApplication::instance()->root()->addWidget(Wt::cpp14::make_unique<NotificationWidget>(user->get_username(),&database));

        }
        else{
            confirm_->setText("Wrong Password");
        }
    }
    else{
        confirm_->setText("Cannot find the user" + nameEdit_->text());
    }
}

void OrderPage::Go_Register(){
    std::move(database);

    this->removeFromParent();
    WApplication::instance()->root()->addWidget(cpp14::make_unique<RegisterPage>());
}
