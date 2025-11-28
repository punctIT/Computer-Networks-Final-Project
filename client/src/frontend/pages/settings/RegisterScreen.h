#pragma once 

#include <memory>


class DataRequester;
class QLineEdit;
class QWidget;
class QLabel;
class QPushButton;
class PageManager;
class DataRequester;

class RegisterScreen{
    std::shared_ptr<PageManager> page_manager;
    std::shared_ptr<DataRequester> data_requester;

    QLineEdit *username_input ;
    QLineEdit *password_input ;
    QLineEdit *password2_input ;
    QLabel *error_lbn;
    QPushButton * signin_btn ;
    QPushButton * login_btn ;
    QWidget *screen;
    void bind_buttons();
    public:
    RegisterScreen(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager);
    QWidget *get_screen();
};