

#pragma once

#include <memory>
#include "../../page_system/Page.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include <QtWidgets/QMainWindow>

class DashboardPage:public Page{
    QPushButton *btn;
    void bind_buttons();
    public:
        DashboardPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
};