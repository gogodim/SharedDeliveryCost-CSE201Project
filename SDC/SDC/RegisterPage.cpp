#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <stdlib.h>
#include <string>
//#include <boost/regex.hpp>
#include <regex>
#include <typeinfo>

#include "Database.h"
#include "RegisterPage.h"
#include "OrderPage.h"

RegisterPage::RegisterPage(int argc, char** argv): WContainerWidget()
{
    this->argc = argc;
    this->argv = argv;

    this->setStyleClass("login-page");
    addWidget(Wt::cpp14::make_unique<WText>("Register your account, SVP? "));


    /*Register layout*/
    auto Login = Wt::cpp14::make_unique<Wt::WContainerWidget>();
    Login->setHeight(400);
    Login->setWidth(200);
    Login->setStyleClass("login-box");

    /*vertical box*/
    auto vbox = Login->setLayout(Wt::cpp14::make_unique<Wt::WVBoxLayout>());

    /*username input*/
    auto hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    auto text = Wt::cpp14::make_unique<Wt::WText>("Username");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    usernameEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    usernameEdit_->setStyleClass("login-edit");
    usernameEdit_->setFocus();

    /*name input*/
    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    text = Wt::cpp14::make_unique<Wt::WText>("Name");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    nameEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    nameEdit_->setStyleClass("login-edit");
    nameEdit_->setFocus();

    /*surname input*/
    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    text = Wt::cpp14::make_unique<Wt::WText>("Surame");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    surnameEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    surnameEdit_->setStyleClass("login-edit");
    surnameEdit_->setFocus();

    /*email input*/
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
    passwordEdit_->setEchoMode(EchoMode::Password);
    passwordEdit_->setStyleClass("login-edit");
    passwordEdit_->setFocus();


    /*postalcode input*/
    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    text = Wt::cpp14::make_unique<Wt::WText>("PostalCode");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    PostCodeEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    PostCodeEdit_->setStyleClass("login-edit");
    PostCodeEdit_->setFocus();

    /*city input*/
    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    text = Wt::cpp14::make_unique<Wt::WText>("City");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    CityEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    CityEdit_->setStyleClass("login-edit");
    CityEdit_->setFocus();

    /*street input*/
    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    text = Wt::cpp14::make_unique<Wt::WText>("Street Name and Number");
    text->setStyleClass("login-element");
    hbox->addWidget(std::move(text));
    StreetNoEdit_ = hbox->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    StreetNoEdit_->setStyleClass("login-edit");
    StreetNoEdit_->setFocus();


    hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());

    /*Login button*/
    auto button = hbox->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Login")); // create a button
    button->setMargin(5, Wt::Side::Left);
    addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    button->clicked().connect(this, &RegisterPage::Go_Login);

    /*Confirm button*/
    button = hbox->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Confirm")); // create a button
    button->setMargin(5, Wt::Side::Left);
    addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    button->clicked().connect(this, &RegisterPage::Register);
    confirm_ = vbox->addWidget(Wt::cpp14::make_unique<Wt::WText>());

    /*Register Page*/
    hbox = this->setLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    auto logo = Wt::cpp14::make_unique<WImage>("images/logo.png");
    logo->setStyleClass("login-image");
    hbox->addWidget(std::move(logo));
    hbox->addWidget(std::move(Login));

    /*Confirm Message*/

    StreetNoEdit_->enterPressed().connect(std::bind(&RegisterPage::Register, this));

    database = Wt::cpp14::make_unique<Database>();

}

void RegisterPage::Register(){

    confirm_->setText("Loading......");
    UserDB* user{new UserDB()};
    Address useraddress((PostCodeEdit_->text()).toUTF8(), (CityEdit_->text()).toUTF8(), (StreetNoEdit_->text()).toUTF8());

    user->set_username(usernameEdit_->text().toUTF8());
    user->set_password((passwordEdit_->text()).toUTF8());
    user->set_email((emailEdit_->text()).toUTF8());
    user->set_address(useraddress.get_address());
    user->set_useraddress(useraddress);
    user->set_name((nameEdit_->text()).toUTF8());
    user->set_surname((surnameEdit_->text()).toUTF8());
    bool find_flag = database->find_user(user);

    if(find_flag){
        bool email_flag = this->Check_Valid_Email(user->get_email());
        if(!email_flag){
        //if (false){
            confirm_->setText("Wrong Email");
        }
        else{
            Coordinate cor = this->Check_Valid_Address((PostCodeEdit_->text()).toUTF8(), (CityEdit_->text()).toUTF8(), (StreetNoEdit_->text()).toUTF8());
            if(cor.get_latitude() == -1 && cor.get_longitude() == -1){
            //if (false){
                confirm_->setText("Wrong Address");
                return;
            }

            //user->set_coordinates(cor);
            user->lat = cor.get_latitude();
            user->lo =cor.get_longitude();
            std::cout << user->lo <<" user information:"<<typeid(cor.get_latitude()).name()<<std::endl;
            confirm_->setText("Register Successful");
            database->add_user(user);
            return;
        }

    }
    else{
        confirm_->setText("There is already a username: " + usernameEdit_->text() +
                          ". Please check again.");
        return;
    }
}

void RegisterPage::Go_Login(){
    /*Change Container too RegisterPage*/
    std::move(database);
    this->removeFromParent();
    WApplication::instance()->root()->addWidget(cpp14::make_unique<OrderPage>(this->argc, this->argv));
}

//functions necessary for user
bool RegisterPage::Check_Valid_Email(std::string email){
    return regex_match(email, std::regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"));
}

Coordinate RegisterPage::Check_Valid_Address(std::string postalcode, std::string city, std::string street){
    Coordinate cor = address_to_coordinates(argc, argv, postalcode, city, street);
    std::cout<<"latitude: "<<cor.get_latitude()<<", longtitude: "<<cor.get_longitude()<<std::endl;
    if(cor.get_latitude() == -1 && cor.get_longitude() == -1){
        return Coordinate(-1, -1);
    }
    return cor;
}
