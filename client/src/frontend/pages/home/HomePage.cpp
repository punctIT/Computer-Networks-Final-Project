#include "HomePage.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include <QtWidgets/QMainWindow>
void HomePage::bind_buttons()
{
    QObject::connect(btn,&QPushButton::clicked,[this](){
        this->page_manager->change_page(1);
    });
}

HomePage::HomePage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager,std::shared_ptr <QMainWindow> window) : Page(data, page_manager,window)
{
    main_menu= std::make_shared<MainMenu>(page_manager);
    QGridLayout *layout = new QGridLayout();
    layout->setRowStretch(0, 1);  
    layout->setRowStretch(1, 99);  

    QLabel *label = new QLabel("HOME");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(main_menu->get_widget(),0,0);
    layout->addWidget(label,1,0);
   
    btn = new QPushButton("login");
    layout->addWidget(btn,2,0);
    page->setLayout(layout);
    bind_buttons();
}

void HomePage::on_enter()
{
    window->showMaximized();
    qDebug()<<"enter Home";
}

void HomePage::on_exit()
{
     qDebug()<<"leave Home";
}
