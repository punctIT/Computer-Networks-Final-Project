#include "HomePage.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.hpp"
#include <QtWidgets/QMainWindow>
void HomePage::bind_buttons()
{
    QObject::connect(btn,&QPushButton::clicked,[this](){
        auto data = this->data_requester->sent_request("type:{logout};");
        if(data){
            qDebug()<<data.value().c_str();
        }
        else {
            qDebug()<<data.error().c_str();
        }
        this->page_manager->change_page(1);

    });
}

HomePage::HomePage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager,std::shared_ptr <QMainWindow> window) : Page(data, page_manager,window)
{
    QGridLayout *layout = new QGridLayout();
    layout->setRowStretch(0, 1);  
    layout->setRowStretch(1, 99);  

    QLabel *label = new QLabel("HOME");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label,1,0);
   
    btn = new QPushButton("login");
    layout->addWidget(btn,2,0);
    page->setLayout(layout);
    bind_buttons();
}

void HomePage::on_enter()
{
    window->showMaximized();
    auto data = data_requester->sent_request("type:logs;");
    if(data){
        qDebug()<<data.value().c_str();
    }
    qDebug()<<"enter Home";
}

void HomePage::on_exit()
{
     qDebug()<<"leave Home";
}
