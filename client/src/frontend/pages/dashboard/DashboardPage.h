

#pragma once

#include <memory>
#include "../../page_system/Page.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QBoxLayout>
#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include <QtWidgets/QMainWindow>
#include <QtCore/QTimer>

class DashboardPage:public Page{
    std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages;
    std::shared_ptr<PageManager> dashboard_pages;
    QHBoxLayout *layout;
    QPushButton *syslog_dashbord;
    QPushButton *agents_dashbord;
    QPushButton *unknown_syslog_dashboard;
     QPushButton *unknown_agent_dashboard;
    void bind_buttons();
    QTimer *update_timer;
    QWidget* get_bottom_menu();
    public:
        DashboardPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
        void update();
};