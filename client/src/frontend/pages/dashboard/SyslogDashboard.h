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

class SyslogData{
    QWidget* widget;
    QFrame *card1, *card2, *card3, *card4;
    QLabel *lbl1Title, *lbl1Value, *lbl1Sub;
    QLabel *lbl2Title, *lbl2Value, *lbl2Sub;
    QLabel *lbl3Title, *lbl3Value, *lbl3Sub;
    QLabel *lbl4Title, *lbl4Value, *lbl4Sub;
    
public:
    SyslogData();
    QWidget *get_widget();
    void updateLogsPerSecond(int logsPerSecond);
    void updateTotalLogs(int totalLogs);
    void updateUptime(std::string uptime);
    void updateDatabaseSize(std::string dbSize);
};

class SyslogLineChart {
    QLineSeries *series;      
    QChart *chart;
    QChartView *chartView;

    QDateTimeAxis *axisX;     
    QValueAxis *axisY;

public:
    SyslogLineChart();
    QWidget *get_chart();
    void updateValues(int newLogsCount); 
};

class SyslogDonutChart{
    QPieSeries *series;
    QChart *chart;
    QChartView *chartView;
    int high,medium,low;
    
public:
    SyslogDonutChart();
    QWidget *get_chart();
    void updateAnim();
    void updateValues(int info, int warning, int error);
};

class SyslogTable{
    QWidget *widget;
    QTableWidget *table;

public: 
    SyslogTable();
    QWidget* get_widget();
    void add(std::vector<std::string> SyslogDashboard_data);
    void clear();
};

class SyslogDashboardScreen: public Page{
    QPushButton *btn;
    int total_logs;
    std::shared_ptr<SyslogTable> SyslogDashboard_table;
    std::shared_ptr<SyslogDonutChart> syslog_donut_chart;
    std::shared_ptr<SyslogLineChart> syslog_line_chart;
    std::shared_ptr<SyslogData> syslog_data;
    void bind_buttons();
    QWidget* get_top_menu();
    
public:
    SyslogDashboardScreen(std::shared_ptr<DataRequester> data,const std::shared_ptr<PageManager> &page_manager,std::shared_ptr<QMainWindow> window);
    void on_enter() override;
    void on_exit() override;
};