#include "AddPopup.hpp"

void AddPopup::connect_buttons()
{
    QObject::connect(add_btn,&QPushButton::clicked,[this](){
        const std::string cmd = std::format("type:{{add_filtres}};type_f:{{{}}};keyword:{{{}}};",this->type,keyword->text().toStdString());
;       auto data = data_requester->sent(cmd);
        this->hide();
    });
}

void AddPopup::update(const std::string type)
{
    this->title->setText("New filter for "+QString::fromStdString(type));
    this->add_btn->setText("Add new "+QString::fromStdString(type));
    this->type= type;
}

AddPopup::AddPopup(QWidget *parent, std::shared_ptr<DataRequester> data, int x, int y) : Popup(parent, data, x, y)
{
    add_btn= new QPushButton("Add to whitelist");
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
    keyword= new QLineEdit();
    title = new QLabel("");
    error = new QLabel();
    error->hide();
    layout->addWidget(title,0,0);
    layout->addWidget(new QLabel("Keyword:"),1,0);
    layout->addWidget(keyword,2,0);
    layout->addWidget(add_btn,6,0);
    connect_buttons();
};