#pragma once

#include "../../page_system/Popup.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "../../../server_request/DataRequester.h"

#include <format>
#include <string>


class AlertsTable;
class AlertsPopup:public Popup{
    QPushButton *resolve_btn;
    int id=0;
    AlertsTable *alert_tabele;
    void connect_buttons();
    public:
    AlertsPopup(QWidget* parent,std::shared_ptr <DataRequester> data,int x,int y);
    void update_data(std::string ,AlertsTable *table,int id) override;
};