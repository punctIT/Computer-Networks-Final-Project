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

class LogsTable {
    QWidget *widget;
    QTableWidget *table;

public:
    LogsTable();
    QWidget* get_widget();
    void add(std::vector<std::string> data);
    void clear();
};

class SourcesTable {
    QWidget *widget;
    QTableWidget *table;

public:
    SourcesTable();
    QWidget* get_widget();
    void add(std:: vector<std::string> data);
    void clear();
};

class UnknownSyslogDashboardScreen :  public Page {
    QPushButton *btn;
    std::shared_ptr<LogsTable> Logs_table;
    std:: shared_ptr<SourcesTable> sources_table;
    void bind_buttons();

public:
    UnknownSyslogDashboardScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window);
    void on_enter() override;
    void on_exit() override;
};