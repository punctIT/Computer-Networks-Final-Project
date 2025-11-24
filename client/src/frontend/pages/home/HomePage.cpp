#include "HomePage.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
void HomePage::bind_buttons()
{
    QObject::connect(btn,&QPushButton::clicked,[this](){
        this->page_manager->change_page(1);
    });
}

HomePage::HomePage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager,std::shared_ptr <QMainWindow> window) : Page(data, page_manager,window)
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
