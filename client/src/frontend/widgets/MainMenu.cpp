#include "MainMenu.hpp"
#include <QStyle>
void MainMenu::bind_buttons()
{
    QObject::connect(home_btn,&QPushButton::clicked,[this](){
        page_manager->change_page(2);
    });
    QObject::connect(statistiscs_btn,&QPushButton::clicked,[this](){
        page_manager->change_page(3);
    });
    QObject::connect(settings_btn,&QPushButton::clicked,[this](){
        page_manager->change_page(4); 
    });
    QObject::connect(security_btn,&QPushButton::clicked,[this](){
        page_manager->change_page(5); 
    });
    //home_btn
}
MainMenu::MainMenu(std::shared_ptr<PageManager> page_manager) {
    this->page_manager = page_manager;

    menu = new QWidget();
    menu->setStyleSheet("background-color: white; border-bottom: 1px solid #e0e0e0;");
    
    grid = new QGridLayout();

    grid->setContentsMargins(10, 5, 10, 5); 
    grid->setSpacing(5);

    home_btn = new QPushButton("Home");
    statistiscs_btn = new QPushButton("Dashboard");
    security_btn = new QPushButton("Security");
    settings_btn = new QPushButton("Settings");


    QString btnStyle = 
        "QPushButton {"
        "   background-color: transparent;"
        "   border: none;"
        "   border-radius: 5px;"     
        "   color: #555555;"         
        "   font-weight: bold;"
        "   font-size: 13px;"
        "   padding: 8px 15px;"     
        "   text-align: left;"       
        "}"
        "QPushButton:hover {"       
        "   background-color: #f0f2f5;"
        "   color: #1a73e8;"        
        "}";


    home_btn->setStyleSheet(btnStyle);
    home_btn->setIcon(menu->style()->standardIcon(QStyle::SP_DirHomeIcon)); 
    home_btn->setIconSize(QSize(24, 24));

    statistiscs_btn->setStyleSheet(btnStyle);
    statistiscs_btn->setIcon(menu->style()->standardIcon(QStyle::SP_FileIcon));
    statistiscs_btn->setIconSize(QSize(24, 24));

    security_btn->setStyleSheet(btnStyle);
    security_btn->setIcon(menu->style()->standardIcon(QStyle::SP_MessageBoxWarning));
    security_btn->setIconSize(QSize(24, 24));

    settings_btn->setStyleSheet(btnStyle);
    settings_btn->setIcon(menu->style()->standardIcon(QStyle::SP_ComputerIcon));
    settings_btn->setIconSize(QSize(24, 24));


    grid->addWidget(home_btn, 0, 0);
    grid->addWidget(statistiscs_btn, 0, 1);
    grid->addWidget(security_btn, 0, 2);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    grid->addWidget(spacer, 0, 3); 

    grid->addWidget(settings_btn, 0, 4);

    menu->setLayout(grid); 
    bind_buttons();
}


QWidget* MainMenu::get_widget() {
    return this->menu;
}

