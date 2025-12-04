#pragma once 

#include <memory>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include "../page_system/PageManager.h"

class MainMenu{
    std::shared_ptr <PageManager> page_manager;
    QPushButton *home_btn;
    QPushButton *statistiscs_btn;
    QPushButton *security_btn;
    QPushButton *settings_btn;
    QGridLayout *grid;
    QWidget *menu;
    void bind_buttons();
    public:
    MainMenu(std::shared_ptr <PageManager> page_manager);
    QWidget* get_widget();
};