

#pragma once

#include <memory>
#include "../../page_system/Page.h"
#include <QtCore/QTimer>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <format>

#include "../../page_system/PageManager.h"
#include "../../page_system/Page.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.h"
#include "../../../utils/BetterString.hpp"

#include "AlertsPopup.hpp"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <vector>
#include <string>

struct AlertData {
    std::string id;
    std::string alert_name;
    std::string category;
    int severity;
    std::string status;
    std::string timestamp;
    std::string details;
};

class AlertsTable {
    QWidget *widget;
    QScrollArea *scrollArea;
    QWidget *contentWidget;
    QVBoxLayout *contentLayout;
    int alertCount;
     std::shared_ptr<AlertsPopup> popup;
public:
    AlertsTable( std::shared_ptr<AlertsPopup> popup);
    QWidget* get_widget();
    void remove_at(int i);
    void add(std:: vector<AlertData> alerts_data);
    void clear();
};


class AlertsPage:public Page {
    void bind_buttons();
    QVBoxLayout *layout;
    QPushButton *Alerts;
    QTimer *updateTimer;   
    std::shared_ptr<AlertsTable> alerts_table;
    std::shared_ptr<AlertsPopup> popup;
    public:
        AlertsPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
    private slots:
        void update();
    

};