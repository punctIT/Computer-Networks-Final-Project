#include "MainMenu.hpp"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include "../page_system/PageManager.h"
void MainMenu::bind_buttons()
{
    QObject::connect(home_btn,&QPushButton::clicked,[this](){
        page_manager->change_page(2);
        qDebug()<<"salut home";
    });
    QObject::connect(statistiscs_btn,&QPushButton::clicked,[this](){
        page_manager->change_page(3); qDebug()<<"ceva";
    });
    QObject::connect(settings_btn,&QPushButton::clicked,[this](){
        qDebug()<<"settings";
    });
    //home_btn
}
MainMenu::MainMenu(std::shared_ptr<PageManager> page_manager)
{
    this->page_manager=page_manager;
    grid = new QGridLayout();
    menu = new QWidget();
    this->statistiscs_btn= new QPushButton("Dashboard");
    this->home_btn= new QPushButton("Home");
    this->settings_btn = new QPushButton("Settings");
    grid->addWidget(home_btn,0,0);
    grid->addWidget(statistiscs_btn,0,1);
    grid->addWidget(settings_btn,0,2);
    menu->setLayout(grid); 
    bind_buttons();
}

QWidget *MainMenu::get_widget()
{ 
    return menu;
}