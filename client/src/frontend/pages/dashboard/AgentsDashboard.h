

#pragma once

#include <memory>
#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.h"
#include "../../../utils/JUNK.hpp"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QtCore/QTimer>



class AgentsTable{
    QWidget *widget;
    QTableWidget *table;

    public:
    AgentsTable();
    QWidget* get_widget();
    void add(std::vector<std::string> AgentsDashboard_data);
    void clear();
};

class AgentsDashboardScreen:public Page{
    QPushButton *btn;
    std::shared_ptr<AgentsTable> AgentsDashboard_table;
    void bind_buttons();
    public:
        AgentsDashboardScreen(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
};


