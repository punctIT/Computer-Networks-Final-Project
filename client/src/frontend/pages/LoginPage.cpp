#include "LoginPage.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../page_system/PageManager.h"
#include "../../server_request/DataRequester.hpp"

void LoginPage::bind_buttons(){
    QObject::connect(this->signin_btn, &QPushButton::clicked, [this]() {
        qDebug() << "Buton apăsat!";    
        this->page_manager->change_page(2);

        
    });
}

LoginPage::LoginPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager):Page(data,page_manager){
    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *label = new QLabel("Salut! Acesta este un QLabel într-un QWidget.");
    label->setAlignment(Qt::AlignCenter);

    signin_btn = new QPushButton("Connect");
    username_input = new QLineEdit();
    password_input = new QLineEdit();
    layout->addWidget(label);
    layout->addWidget(username_input);
    layout->addWidget(password_input);
    layout->addWidget(signin_btn);
    page->setLayout(layout);
    bind_buttons();
}
