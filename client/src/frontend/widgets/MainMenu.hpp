#pragma once 

#include <memory>
class PageManager;
class QWidget;
class QPushButton;
class QGridLayout;

class MainMenu{
    std::shared_ptr <PageManager> page_manager;
    QPushButton *home_btn;
    QPushButton *statistiscs_btn;
    QPushButton *settings_btn;
    QGridLayout *grid;
    QWidget *menu;
    void bind_buttons();
    public:
    MainMenu(std::shared_ptr <PageManager> page_manager);
    QWidget* get_widget();
};