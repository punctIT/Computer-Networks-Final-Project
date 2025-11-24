#include "MainMenu.hpp"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
MainMenu::MainMenu(std::shared_ptr<PageManager> page_manager)
{
    this->page_manager=page_manager;
}
QWidget *MainMenu::get_widget()
{
    QGridLayout *grid = new QGridLayout();
    this->statistiscs_btn= new QPushButton("Statistics");
    this->home_btn= new QPushButton("Home");
    grid->addWidget(home_btn,0,0);
    grid->addWidget(statistiscs_btn,0,1);
    QWidget *menu = new QWidget();
    menu->setLayout(grid); 
    return menu;
}