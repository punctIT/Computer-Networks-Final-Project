#pragma once 

#include <memory>
class PageManager;
class QWidget;
class QPushButton;


class MainMenu{
    std::shared_ptr <PageManager> page_manager;
    QPushButton *home_btn;
    QPushButton *statistiscs_btn;
    void bind_buttons();
    public:
    MainMenu(std::shared_ptr <PageManager> page_manager);
    QWidget* get_widget();
};