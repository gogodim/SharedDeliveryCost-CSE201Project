#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "Database.h"

using namespace Wt;

class RegisterPage: public WContainerWidget{

public:
    RegisterPage(int, char**);
    int                    argc;
    char**                 argv;
    void Register();
    void Go_Login();
    bool Check_Valid_Email(std::string email);
    Coordinate Check_Valid_Address(std::string postalcode, std::string city, std::string street);

private:
    Wt::WLineEdit                  *usernameEdit_;
    Wt::WLineEdit                  *nameEdit_;
    Wt::WLineEdit                  *surnameEdit_;

    Wt::WLineEdit                  *emailEdit_;
    Wt::WLineEdit                  *passwordEdit_;
    Wt::WLineEdit                  *PostCodeEdit_;
    Wt::WLineEdit                  *CityEdit_;
    Wt::WLineEdit                  *StreetNoEdit_;
    //Wt::WLineEdit                  *locationEdit_;
    Wt::WText                      *confirm_;
    std::unique_ptr<Database>      database;   
};

#endif // REGISTERPAGE_H
