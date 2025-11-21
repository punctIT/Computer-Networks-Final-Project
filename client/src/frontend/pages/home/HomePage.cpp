#include "HomePage.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../../page_system/PageManager.h"
void HomePage::bind_buttons()
{
    QObject::connect(btn,&QPushButton::clicked,[this](){
        this->page_manager->change_page(1);
    });
}

HomePage::HomePage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager) : Page(data, page_manager)
{
    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *label = new QLabel("HOME");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    btn = new QPushButton("login");
    layout->addWidget(btn);
    page->setLayout(layout);
    bind_buttons();
}

void HomePage::on_enter()
{
    qDebug()<<"enter Home";
}

void HomePage::on_exit()
{
     qDebug()<<"leave Home";
}
