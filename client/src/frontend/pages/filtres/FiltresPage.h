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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QHBoxLayout>
#include <format>

#include "../../page_system/PageManager.h"
#include "../../page_system/Page.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.h"
#include "../../../utils/BetterString.hpp"

class TypeFiltresTable {
    QWidget *widget;
    QTableWidget *table;
    std:: shared_ptr<DataRequester> data_requester;

public:
    TypeFiltresTable(std::shared_ptr<DataRequester> data_requester);
    QWidget* get_widget();
    void add(std::vector<std::string> data);
    void clear();
};

class MessageFiltresTable {
    QWidget *widget;
    QTableWidget *table;
    std:: shared_ptr<DataRequester> data_requester;

public: 
    MessageFiltresTable(std::shared_ptr<DataRequester> data_requester);
    QWidget* get_widget();
    void add(std::vector<std::string> data);
    void clear();
};

class CustomAlertsTable {
    QWidget *widget;
    QTableWidget *table;
    std::shared_ptr<DataRequester> data_requester;

public: 
    CustomAlertsTable(std::shared_ptr<DataRequester> data_requester);
    QWidget* get_widget();
    void add(std::vector<std::string> data);
    void clear();
};

class FiltresPage : public Page {
    void bind_buttons();

    QGridLayout *layout;
    QPushButton *btn_add_type;
    QPushButton *btn_add_message;
    QPushButton *btn_add_alert;
    QTimer *updateTimer;
    
    std::shared_ptr<TypeFiltresTable> type_table;
    std::shared_ptr<MessageFiltresTable> message_table;
    std::shared_ptr<CustomAlertsTable> alert_table;

public:
    FiltresPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window);
    void on_enter() override;
    void on_exit() override;

private slots:
    void update();
};