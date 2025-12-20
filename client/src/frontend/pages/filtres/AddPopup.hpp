#pragma once

#include "../../page_system/Popup.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "../../../server_request/DataRequester.h"

#include <format>
#include <string>

class AddPopup:public Popup{
    QLabel *title;
    QPushButton *add_btn;
    QLineEdit *keyword;
    QLabel *error;
    std::string type = "";
    void connect_buttons();
    public:
    void update(const std::string type);
    AddPopup(QWidget* parent,std::shared_ptr <DataRequester> data,int x,int y);
};