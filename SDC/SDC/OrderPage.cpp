#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "OrderPage.h"

using namespace Wt;

OrderPage::OrderPage(): WContainerWidget(){
    addWidget(Wt::cpp14::make_unique<WText>("Enter your name, SVP? "));

    nameEdit_ = this->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>()); // allow text input
    nameEdit_->setFocus();  

    auto button = this->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Greet me.")); // create a button
    button->setMargin(5, Wt::Side::Left);

    addWidget(Wt::cpp14::make_unique<Wt::WBreak>());  
    //greeting_ = root()->addWidget(Wt::cpp14::make_unique<Wt::WText>()); 

    //button->clicked().connect(this, &OrderPage::greet);

    //nameEdit_->enterPressed().connect(std::bind(&HelloApplication::greet, this));

}

void OrderPage::greet(){
    greeting_->setText("Hello there, " + nameEdit_->text());
}
