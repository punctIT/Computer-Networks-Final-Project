#include "ConnectPage.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>

void ConnectPage::bind_buttons()
{
    QObject::connect(this->signin_btn, &QPushButton::clicked, []() {
        qDebug() << "Buton apăsat!";
    });
}

ConnectPage::ConnectPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window):Page(data,page_manager,window){
    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *label = new QLabel("Connect");
    label->setAlignment(Qt::AlignCenter);

    signin_btn = new QPushButton("Connect");
    username_input = new QLineEdit();
    password_input = new QLineEdit();
    layout->addWidget(label);
    layout->addWidget(username_input);
    layout->addWidget(password_input);
    layout->addWidget(signin_btn);
    page->setLayout(layout);
    bind_buttons();
}

void ConnectPage::on_enter()
{
    qDebug()<<"enter Connect";
}

void ConnectPage::on_exit()
{
    qDebug()<<"exit Connect";
}
