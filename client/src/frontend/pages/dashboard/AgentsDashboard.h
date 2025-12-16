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

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>

#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QDateEdit>
#include <QFrame>




class AgentsDonutChart{
    QPieSeries *series;
    QChart *chart;
    QChartView *chartView;
    int last_val;
    
public:
    AgentsDonutChart (const std::string name, const std::string usedColor, const std::string freeColor);
    QWidget *get_chart();
    void updateAnim();
    void updateValues(int val);
};

class AgentsDashboardScreen: public Page{
    QPushButton *btn;
    int total_logs;
    std::shared_ptr<AgentsDonutChart> ram_chart;
    std::shared_ptr<AgentsDonutChart> disk_chart;
    std::shared_ptr<AgentsDonutChart> cpu_chart;
    void bind_buttons();
    QWidget* get_top_menu();
    
public:
    AgentsDashboardScreen(std::shared_ptr<DataRequester> data,const std::shared_ptr<PageManager> &page_manager,std::shared_ptr<QMainWindow> window);
    void on_enter() override;
    void on_exit() override;
};