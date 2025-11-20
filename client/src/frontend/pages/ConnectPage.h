

#pragma once

#include <memory>
#include "../page_system/Page.h"
class DataRequester;
class QLineEdit;
class QWidget;
class QPushButton;

class ConnectPage:public Page{
    QLineEdit *username_input ;
    QLineEdit *password_input ;
    QPushButton * signin_btn ;
    void bind_buttons();
    public:
        ConnectPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager);
        void on_enter() override;
};