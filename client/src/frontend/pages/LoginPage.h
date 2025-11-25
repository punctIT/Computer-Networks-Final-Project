

#pragma once

#include <memory>
#include "../page_system/Page.h"

class DataRequester;
class QLineEdit;
class QWidget;
class QLabel;
class QPushButton;

class PageManager;
class LoginPage:public Page{
    QLineEdit *username_input ;
    QLineEdit *password_input ;
    QLabel *error_lbn;
    QPushButton * signin_btn ;
    QPushButton * register_btn ;
    void bind_buttons();
    void clear_data();
    void show_error();
    public:
        LoginPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
        

};