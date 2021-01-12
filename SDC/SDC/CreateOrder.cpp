#include "CreateOrderHeaders.h"
#include <stdlib.h>

#include <iostream>

namespace dbo = Wt::Dbo;
using namespace Wt;

NewOrderWidget::NewOrderWidget(const std::string &username,Database *session){
    session_ = session;
    user_ = username;

    maxDelivery_description = addWidget(std::make_unique<WText>("max delivery:"));
    maxDeliveryVal_  = (addWidget(std::make_unique<WLineEdit>()));
    addWidget(std::make_unique<WBreak>());

    diff_loc_description = addWidget(std::make_unique<WText>("Different address"));
    diff_loc_  = addWidget(std::make_unique<WLineEdit>(""));
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
    addWidget(std::make_unique<WBreak>());

    confirm_ = addWidget(std::make_unique<Wt::WPushButton>("Confirm"));
    confirm_->clicked().connect(this, &NewOrderWidget::confirm);

    this->hide();
};

void NewOrderWidget::display(){
    if(this->isHidden()){
        this->show();
    } else {
        this->hide();
    }
};
void NewOrderWidget::confirm(){

    session_->addOrder(user_, std::stod(maxDeliveryVal_->text().toUTF8()), diff_loc_->text().toUTF8(),
                       std::stod(order_val_->text().toUTF8()), std::stod(radius_->text().toUTF8()),
                       company_->currentText().toUTF8(),diff_loc_->text().toUTF8() );
};

