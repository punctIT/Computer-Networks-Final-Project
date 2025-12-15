#include "BlackListPopup.hpp"

void AddBlacklistPopup::connect_buttons()
{
    QObject::connect(add_btn,&QPushButton::clicked,[this](){
        const std::string cmd = std::format("type:add_blacklist_ip;ip:{{{}}};admin_username:admin;",
        ip_entry->text().toStdString());
        auto data = data_requester->sent(cmd);
        this->hide();
    });
}

AddBlacklistPopup::AddBlacklistPopup(QWidget *parent, std::shared_ptr<DataRequester> data, int x, int y) : Popup(parent, data, x, y)
{
    add_btn= new QPushButton("Add to Blacklist");
    ip_entry= new QLineEdit();
    add_btn->setStyleSheet(R"(
            QPushButton {
                background-color: #1ABC9C;
                color: white;
                border-radius: 6px;
                padding: 8px 15px;
                font-weight: bold;
                font-size: 14px;
                border: none;
            }
            QPushButton:hover {
                background-color: #16A085;
            }
            QPushButton:pressed {
                background-color: #0E6655;
            }
        )");
    error = new QLabel();
    error->hide();
    layout->addWidget(new QLabel("Add new ip source to blacklist"),0,0);
    layout->addWidget(new QLabel("IP adreess:"),1,0);
    layout->addWidget(ip_entry,2,0);      
    layout->addWidget(error,5,0);
    layout->addWidget(add_btn,6,0);
    connect_buttons();
};