#include "SecurityPage.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>

#include <format>

#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.hpp"
#include "../../../utils/BetterString.hpp"

void SecurityPage::bind_buttons()
{
    QObject::connect(btn,&QPushButton::clicked,[this](){
        auto data = data_requester->sent_request("type:{add_whitelist_ip};source_name:{local};ip:{none};admin_username:{admin};");
        if(data){
            qDebug()<<data.value().c_str();
        }
    });
}

SecurityPage::SecurityPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager,std::shared_ptr <QMainWindow> window) : Page(data, page_manager,window)
{
    QGridLayout *layout = new QGridLayout();
    layout->setRowStretch(0, 1);  
    layout->setRowStretch(1, 99);  
    btn = new QPushButton("sent");
    QLabel *label = new QLabel("Security");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label,1,0);
    layout->addWidget(btn,1,1);
    page->setLayout(layout);
    
    updateTimer = new QTimer(this); 
    connect(updateTimer, &QTimer::timeout, this, &SecurityPage::update);
    updateTimer->setInterval(2000); 

    bind_buttons();
}

void SecurityPage::on_enter()
{
    window->showMaximized();
    updateTimer->start();
}
void SecurityPage::update(){
    qDebug()<<"update";
    
}
void SecurityPage::on_exit()
{
     updateTimer->stop();
}
