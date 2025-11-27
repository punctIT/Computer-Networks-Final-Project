#include "HomePage.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>

#include <format>

#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.hpp"
#include "TableWidget.h"
#include "../../../utils/BetterString.hpp"

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
    table_widget= std::make_shared<TableMenu>();
    layout->setRowStretch(0, 1);  
    layout->setRowStretch(1, 99);  

    QLabel *label = new QLabel("HOME");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label,1,0);
    layout->addWidget(table_widget->get_widget(),2,0);
    btn = new QPushButton("login");
    layout->addWidget(btn,3,0);
    page->setLayout(layout);

    updateTimer = new QTimer(this); 

    connect(updateTimer, &QTimer::timeout, this, &HomePage::update);
    updateTimer->setInterval(2000); 

    bind_buttons();
}

void HomePage::on_enter()
{
    window->showMaximized();
    
    qDebug()<<"enter Home";
    updateTimer->start();
}
void HomePage::update(){
    auto data = data_requester->sent_request(std::format("type:{{logs}};last_id:{{{}}};",table_widget->get_id()));
    if(!data){
        qDebug()<<data.error().c_str();
    }
    table_widget->add(BetterString::split(data.value(),"{}"));
    
}
void HomePage::on_exit()
{
     updateTimer->stop();
     qDebug()<<"leave Home";
}
