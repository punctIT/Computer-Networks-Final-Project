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
#include "AddWhiteListPopup.hpp"

void SecurityPage::bind_buttons()
{
    QObject::connect(btn,&QPushButton::clicked,[this](){
        // auto data = data_requester->sent_request("type:{add_blacklist_ip};source_name:{local};ip:{127.0.0.1};admin_username:{admin};");
        // if(data){
        //     qDebug()<<data.value().c_str();
        // }
        popup_whitelist_add->showCentered();
    });
}

SecurityPage::SecurityPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager,std::shared_ptr <QMainWindow> window) : Page(data, page_manager,window)
{
   
    popup_whitelist_add=std::make_shared<AddWhitelistPopup>(window.get(),data_requester,400,200); 
    QGridLayout *layout = new QGridLayout();
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
