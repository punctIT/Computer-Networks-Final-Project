#include "ConnectPage.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../page_system/PageManager.h"
#include "../../server_request/DataRequester.hpp"
#include <QtWidgets/QMainWindow>

void ConnectPage::bind_buttons()
{
    QObject::connect(this->connect_btn, &QPushButton::clicked, [this]() {
        try{
            data_requester->set_ip(ip_input->text().toStdString())
                        .set_port(stoi(port_input->text().toStdString()))
                        .configure();
            page_manager->change_page(1);
        }
        catch(std::exception &e){
            error_lbn->show();
            error_lbn->setText("Invalid IP adress or port");
        }
    });
}

ConnectPage::ConnectPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window):Page(data,page_manager,window){
    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *label = new QLabel("Connect");
    label->setAlignment(Qt::AlignCenter);
    error_lbn = new QLabel("");
    connect_btn = new QPushButton("Connect");
    ip_input = new QLineEdit();
    port_input = new QLineEdit();
    
    layout->addWidget(label);
    layout->addWidget(new QLabel("IP adreess"));
    layout->addWidget(ip_input);
    layout->addWidget(new QLabel("Port"));
    layout->addWidget(port_input);
    layout->addWidget(error_lbn);
    layout->addWidget(connect_btn);
    QPushButton *localhost = new QPushButton("localhost");
    layout->addWidget(localhost);
    QObject::connect(localhost,&QPushButton::clicked,[this,page_manager](){
        try{
            data_requester->set_ip("127.0.0.1")
                        .set_port(8080)
                        .configure();
            page_manager->change_page(1);            
        }
        catch(std::exception &e){
            error_lbn->show();
            error_lbn->setText("Invalid IP adress or port");
        }
    });
    page->setLayout(layout);
    bind_buttons();
}

void ConnectPage::on_enter()
{
    window->resize(300,200);
    error_lbn->hide(); 
}

void ConnectPage::on_exit()
{
    qDebug()<<"exit Connect";
}
