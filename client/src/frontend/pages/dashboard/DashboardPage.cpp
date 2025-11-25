#include "DashboardPage.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include <QtWidgets/QMainWindow>

void DashboardPage::bind_buttons(){
    QObject::connect(btn,&QPushButton::clicked,[this](){
        this->page_manager->change_page(1);
    });
}

DashboardPage::DashboardPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager,std::shared_ptr <QMainWindow> window) : Page(data, page_manager,window)
{
    QGridLayout *layout = new QGridLayout();
    layout->setRowStretch(0, 1);  
    layout->setRowStretch(1, 99);  

    QLabel *label = new QLabel("Dashboard");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label,1,0);
   
    btn = new QPushButton("login");
    layout->addWidget(btn,2,0);
    page->setLayout(layout);
    bind_buttons();
}

void DashboardPage::on_enter()
{
    window->showMaximized();
    qDebug()<<"enter dashboard";
}

void DashboardPage::on_exit()
{
     qDebug()<<"leave dashboard";
}
