#include "LoginPage.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../../utils/JUNK.hpp"
#include "../page_system/PageManager.h"
#include "../../server_request/DataRequester.hpp"

void LoginPage::bind_buttons(){
    QObject::connect(this->signin_btn, &QPushButton::clicked, [this]() {
        qDebug() << "login";    
        auto response = this->data_requester->sent_request(
                              data_requester->login_request(this->username_input->text().toStdString(),
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
            data_requester->set_token(data.value()["content"].value());
            page_manager->change_page(2);
        }   
        else {

        }
        
        
        
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

void LoginPage::on_enter()
{
    qDebug()<<"login";
}
