#include "LoginPage.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>

void LoginPage::bind_buttons()
{
    QObject::connect(this->signin_btn, &QPushButton::clicked, []() {
        qDebug() << "Buton apăsat!";
    });
}

LoginPage::LoginPage(std::shared_ptr<DataRequester> data)
{
    page = new QWidget();
   
    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *label = new QLabel("Salut! Acesta este un QLabel într-un QWidget.");
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

QWidget *LoginPage::get_page(){
    return page;
}
