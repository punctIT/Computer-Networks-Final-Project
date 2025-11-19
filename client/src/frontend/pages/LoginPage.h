

#pragma once

#include <memory>

class DataRequester;
class QLineEdit;
class QWidget;
class QPushButton;

class LoginPage{
    QWidget * page;
    QLineEdit *username_input ;
    QLineEdit *password_input ;
    QPushButton * signin_btn ;
    std::shared_ptr <DataRequester> data_requester;

    void bind_buttons();
    public:
        LoginPage(std::shared_ptr <DataRequester> data);
        QWidget* get_page();

};