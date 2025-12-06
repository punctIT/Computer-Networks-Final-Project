

#pragma once

#include <memory>
#include "../page_system/Page.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../../utils/JUNK.hpp"
#include "../page_system/PageManager.h"
#include "../../server_request/DataRequester.h"
#include <QtWidgets/QMainWindow>

class LoginPage:public Page{
    QLineEdit *username_input ;
    QLineEdit *password_input ;
    QLabel *error_lbn;
    QPushButton * signin_btn ;
    void bind_buttons();
    void clear_data();
    void show_error();
    public:
        LoginPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
        

};