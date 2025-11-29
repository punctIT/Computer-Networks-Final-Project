#pragma once

#include "../../page_system/Popup.h"
#include <QLabel>

class DataRequester;
class AddWhitelistPopup:public Popup{
    public:
    AddWhitelistPopup(QWidget* parent,std::shared_ptr <DataRequester> data,int x,int y):Popup(parent,data,x,y){
        layout->addWidget(new QLabel("test"));
    };
};