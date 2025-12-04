#pragma once

#include "../../page_system/Popup.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "../../../server_request/DataRequester.hpp"
#include <format>
#include <string>

class AddWhitelistPopup:public Popup{
    QPushButton *add_btn;
    QLineEdit *ip_entry,*source_name;
    QLabel *error;
    void connect_buttons();
    public:
    AddWhitelistPopup(QWidget* parent,std::shared_ptr <DataRequester> data,int x,int y);
};