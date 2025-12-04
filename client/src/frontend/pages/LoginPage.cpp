#include "LoginPage.h"

void LoginPage::bind_buttons(){
    QObject::connect(this->signin_btn, &QPushButton::clicked, [this]() {
        error_lbn->setText("");
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
    label->setAlignment(Qt::AlignCenter);
    error_lbn=new QLabel();
    error_lbn->hide();
    signin_btn =  new QPushButton("Connect");
    
    username_input = new QLineEdit();
    password_input = new QLineEdit();
    layout->addWidget(label);
    layout->addWidget(new QLabel("Username:"));
    layout->addWidget(username_input);
    layout->addWidget(new QLabel("Password:"));
    layout->addWidget(password_input);
    layout->addWidget(error_lbn);
    layout->addWidget(signin_btn);
    page->setLayout(layout);
    bind_buttons();
}

void LoginPage::on_enter()
{
    window->resize(500,300);
    clear_data();
}

void LoginPage::on_exit(){
}
