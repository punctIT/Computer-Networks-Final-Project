#include "MainMenu.hpp"
#include <QStyle>
#include "../style/AppStype.hpp"

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
     QObject::connect(filtres_btn,&QPushButton::clicked,[this](){
        page_manager->change_page(6); 
    });
    //home_btn
}
MainMenu::MainMenu(std::shared_ptr<PageManager> page_manager) {
    this->page_manager = page_manager;

    menu = new QWidget();
    grid = new QGridLayout();

    grid->setContentsMargins(10, 5, 10, 5); 
    grid->setSpacing(5);
    menu->setObjectName("mainMenuContainer");
    home_btn = new QPushButton("Home");
    statistiscs_btn = new QPushButton("Dashboard");
    security_btn = new QPushButton("Security");
    settings_btn = new QPushButton("Settings");
    filtres_btn = new QPushButton("Filtres");

    home_btn->setIcon(menu->style()->standardIcon(QStyle::SP_DirHomeIcon)); 
    home_btn->setIconSize(QSize(24, 24));

    statistiscs_btn->setIcon(menu->style()->standardIcon(QStyle::SP_FileIcon));
    statistiscs_btn->setIconSize(QSize(24, 24));

    security_btn->setIcon(menu->style()->standardIcon(QStyle::SP_MessageBoxWarning));
    security_btn->setIconSize(QSize(24, 24));

    filtres_btn->setIcon(menu->style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    filtres_btn->setIconSize(QSize(24, 24));


    settings_btn->setIcon(menu->style()->standardIcon(QStyle::SP_ComputerIcon));
    settings_btn->setIconSize(QSize(24, 24));


    grid->addWidget(home_btn, 0, 0);
    grid->addWidget(statistiscs_btn, 0, 1);
    grid->addWidget(security_btn, 0, 2);
    grid->addWidget(filtres_btn, 0, 3);


    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    grid->addWidget(spacer, 0, 4); 

    grid->addWidget(settings_btn, 0, 5);
    menu->setStyleSheet(QString::fromStdString(main_menu_style()));
    menu->setLayout(grid); 
    bind_buttons();
}


QWidget* MainMenu::get_widget() {
    return this->menu;
}

