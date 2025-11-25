#include "RegisterPage.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../../utils/JUNK.hpp"
#include "../page_system/PageManager.h"
#include "../../server_request/DataRequester.hpp"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>

void RegisterPage::bind_buttons(){
    QObject::connect(this->login_btn,&QPushButton::clicked,[this](){
        page_manager->change_page(1);
    });
    QObject::connect(this->signin_btn, &QPushButton::clicked, [this]() {
        error_lbn->setText("");
        if(password_input->text()!= password2_input->text()){
            error_lbn->show();
            error_lbn->setText("Diffenent password");
            return;
        }  
        auto response = this->data_requester->sent_request(
                              data_requester->register_request(this->username_input->text().toStdString(),
                                                            this->password_input->text().toStdString()));
        if(!response.has_value()){
            qDebug()<<response.error().c_str();
            return;
        }
        auto data = JUNK::deserialize(response.value());
        if(!data.has_value() || !data.value()["succes"].has_value() || !data.value()["content"].has_value()){
            return;
        }
        if(data.value()["succes"].value()=="true"){
            QMessageBox::information(window.get(), "Success", "Register successful");
            page_manager->change_page(1);
            return;
        }   
        error_lbn->setText("Username already exists");
        error_lbn->show();
    });
}

void RegisterPage::clear_data()
{
    error_lbn->hide();
    username_input->setText("");  
    password_input->setText("");
    error_lbn->setText("");
}

RegisterPage::RegisterPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window):Page(data,page_manager,window){
    QVBoxLayout *layout = new QVBoxLayout();

    QLabel *label = new QLabel("Register");
    label->setAlignment(Qt::AlignCenter);

    error_lbn=new QLabel();
    signin_btn =  new QPushButton("Register");
    login_btn =  new QPushButton("Login");
    username_input = new QLineEdit();
    password_input = new QLineEdit();
    password2_input = new QLineEdit();

    layout->addWidget(label);
    layout->addWidget(new QLabel("*Username"));
    layout->addWidget(username_input);
    layout->addWidget(new QLabel("*Password"));
    layout->addWidget(password_input);
    layout->addWidget(new QLabel("*Confirm password"));
    layout->addWidget(password2_input);
    layout->addWidget(error_lbn);
    layout->addWidget(signin_btn);
    layout->addWidget(login_btn);
    
    page->setLayout(layout);
    bind_buttons();
}

void RegisterPage::on_enter()
{
    window->resize(500,300);

    clear_data();
}

void RegisterPage::on_exit(){
    
}
