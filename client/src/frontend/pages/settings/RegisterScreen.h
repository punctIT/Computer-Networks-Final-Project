#pragma once 

#include <memory>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include "../../../server_request/DataRequester.h"    
#include "../../page_system/PageManager.h"
#include "../../../utils/JUNK.hpp"

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