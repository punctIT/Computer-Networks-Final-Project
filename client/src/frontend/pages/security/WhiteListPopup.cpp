#include "WhiteListPopup.hpp"

void AddWhitelistPopup::connect_buttons()
{
    QObject::connect(add_btn,&QPushButton::clicked,[this](){
        const std::string cmd = std::format("type:add_whitelist_ip;source_name:{{{}}};ip:{{{}}};admin_username:admin;",
            source_name->text().toStdString(),ip_entry->text().toStdString());
        auto data = data_requester->sent(cmd);
    });
}

AddWhitelistPopup::AddWhitelistPopup(QWidget *parent, std::shared_ptr<DataRequester> data, int x, int y) : Popup(parent, data, x, y)
{
    add_btn= new QPushButton("Add to whitelist");
    ip_entry= new QLineEdit();
    source_name = new QLineEdit();
    error = new QLabel();
    error->hide();
    layout->addWidget(new QLabel("Add new ip source to whitelist"),0,0);
    layout->addWidget(new QLabel("IP adreess:"),1,0);
    layout->addWidget(ip_entry,2,0);
    layout->addWidget(new QLabel("Source Name:"),3,0);
    layout->addWidget(source_name,4,0);       
    layout->addWidget(error,5,0);
    layout->addWidget(add_btn,6,0);
    connect_buttons();
};