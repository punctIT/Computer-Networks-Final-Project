#include "LoginPage.h"
#include "../style/LoginStyle.hpp"
void LoginPage::bind_buttons(){
    QObject::connect(this->signin_btn, &QPushButton::clicked, [this]() {
        error_lbn->setText("");
        qDebug() << "login";    
        auto response = this->data_requester->sent(
                              data_requester->login_request(this->username_input->text().toStdString(),
                                                            this->password_input->text().toStdString()));
        if(!response.has_value()){
            qDebug()<<response.error().c_str();
            return;
        }
    });
    connect(data_requester.get(), &DataRequester::LoginData, 
        this, [this](QString mesaj) {
            auto data = JUNK::deserialize(mesaj.toStdString());
            if(!data.has_value() || !data.value()["succes"].has_value() || !data.value()["content"].has_value()){
                return;
            }
            if(data.value()["succes"].value()=="true"){
                data_requester->set_token(data.value()["content"].value());
                page_manager->change_page(2);
            }   
            else {
                show_error();
            }
        });
}

void LoginPage::clear_data()
{
    error_lbn->hide();
    username_input->setText("");  
    password_input->setText("");
    error_lbn->setText("");
}

void LoginPage::show_error()
{
    error_lbn->show();
    error_lbn->setText("Username or password invalid");
    error_lbn->setStyleSheet("color: red;"); 
}

LoginPage::LoginPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window):Page(data,page_manager,window){
    QVBoxLayout *layout = new QVBoxLayout();
    
    QLabel *label = new QLabel("Welcome Back");
    label->setObjectName("titleLabel"); 
    label->setAlignment(Qt::AlignCenter);
    
    error_lbn = new QLabel();
    error_lbn->setObjectName("errorLabel"); 
    error_lbn->hide();
    
    signin_btn = new QPushButton("Login"); 
    signin_btn->setCursor(Qt::PointingHandCursor);
    
    username_input = new QLineEdit();
    username_input->setPlaceholderText("Enter your username"); 

    password_input = new QLineEdit();
    password_input->setEchoMode(QLineEdit::Password); 
    password_input->setPlaceholderText("Enter your password");

    layout->addWidget(label);
    layout->addWidget(new QLabel("Username:"));
    layout->addWidget(username_input);
    layout->addWidget(new QLabel("Password:"));
    layout->addWidget(password_input);
    layout->addWidget(error_lbn);
    layout->addWidget(signin_btn);
    
    layout->addStretch(); 

    page->setLayout(layout);
    page->setAttribute(Qt::WA_StyledBackground, true);
    page->setStyleSheet(QString::fromStdString(login_style()));
    
    bind_buttons();
}

void LoginPage::on_enter()
{
    window->resize(600,400);
    clear_data();
}

void LoginPage::on_exit(){
}
