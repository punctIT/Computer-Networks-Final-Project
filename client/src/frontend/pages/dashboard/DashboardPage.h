

#pragma once

#include <memory>
#include "../../page_system/Page.h"

class DataRequester;
class QLineEdit;
class QWidget;
class QPushButton;

class MainMenu;
class PageManager;
class DashboardPage:public Page{
    QPushButton *btn;
    void bind_buttons();
    public:
        DashboardPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
};