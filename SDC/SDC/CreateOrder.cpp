#include "CreateOrderHeaders.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <classes.h>
#include <math.h>
#include <string>
#include <regex>
#include <algorithm>

namespace dbo = Wt::Dbo;
using namespace Wt;

NewOrderWidget::NewOrderWidget(const std::string &username,Database *session){
    session_ = session;
    username_ = username;

    maxDelivery_description = addWidget(std::make_unique<WText>("max delivery:"));
    maxDeliveryVal_  = (addWidget(std::make_unique<WLineEdit>()));
    addWidget(std::make_unique<WBreak>());

    postal_description = addWidget(std::make_unique<WText>("Postal code"));
    postal_ = addWidget(std::make_unique<WLineEdit>());
    addWidget(std::make_unique<WBreak>());
    city_description = addWidget(std::make_unique<WText>("City"));
    city_ = addWidget(std::make_unique<WLineEdit>());
    addWidget(std::make_unique<WBreak>());
    diff_loc_description = addWidget(std::make_unique<WText>("Street"));
    diff_loc_  = addWidget(std::make_unique<WLineEdit>());
    addWidget(std::make_unique<WBreak>());

    order_val_description =addWidget(std::make_unique<WText>("Order value"));
    order_val_  = addWidget(std::make_unique<WLineEdit>());
    addWidget(std::make_unique<WBreak>());

    radius_description =addWidget(std::make_unique<WText>("How far can you pick up your order"));
    radius_ = addWidget(std::make_unique<WLineEdit>());
    addWidget(std::make_unique<WBreak>());

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

    cout<<"HEREEEEEE"<<endl;
    int orderID = session_->addOrder(username_, std::stod(maxDeliveryVal_->text().toUTF8()),
                       std::stod(order_val_->text().toUTF8()), std::stod(radius_->text().toUTF8()),
                       company_->currentText().toUTF8(),postal_->text().toUTF8(),
                                     city_->text().toUTF8(),diff_loc_->text().toUTF8());
    this->display();

    //Run process order
    cout<<"Starting process order"<<endl;
    list<Bucket> listBuckets = session_->createBucketList();
    cout<<"Buckets list for processcreated"<<endl;
    tuple<bool,Bucket,list<Bucket>,string> tpl;
    Order ord = session_->createOrderForProcess(orderID);
    cout<<"Order for process created"<<endl;
    tpl = processOrder(listBuckets,ord);
    cout<<"ORDER PROCESSED"<<endl;
    cout<<"TF:"<<get<0>(tpl)<<endl;
    if(get<0>(tpl)==true){
        session_->createNotifications(get<1>(tpl), get<3>(tpl));
        cout<<"Notifications created"<<endl;

    }else{
        cout<<"No notifications"<<endl;

    }

    session_->deleteBucket();
    cout<<"Old buckets deleted"<<endl;

    session_->createBucketDBs(get<2>(tpl));
    cout<<"New buckets created"<<endl;


};

