#include "AlertsPopup.hpp"
#include "AlertsPage.h"

void AlertsPopup::connect_buttons()
{
    QObject::connect(resolve_btn,&QPushButton::clicked,[this](){
        const std::string cmd = std::format("type:{{remove_alert}};alert_id:{{{}}};",data);
        auto data = data_requester->sent(cmd);
        alert_tabele->remove_at(id);
        this->hide();
    });
}

AlertsPopup::AlertsPopup(QWidget *parent, std::shared_ptr<DataRequester> data, int x, int y) : Popup(parent, data, x, y)
{
    resolve_btn= new QPushButton("Solve Alert");
    resolve_btn->setStyleSheet(R"(
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
   
    layout->addWidget(new QLabel("Mark alert resolved"),0,0);
    layout->addWidget(resolve_btn,6,0);
    connect_buttons();
}
void AlertsPopup::update_data(std::string dat,AlertsTable *table,int id){
    alert_tabele=table;
    this->id = id;
    data=dat;
};