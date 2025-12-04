

#pragma once

#include <memory>
#include "../../page_system/Page.h"
#include <QtCore/QTimer>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>

#include <format>

#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.hpp"
#include "TableWidget.h"
#include "../../../utils/BetterString.hpp"

class HomePage:public Page{
    QPushButton *btn;
    std::shared_ptr<TableMenu> table_widget;
    
    void bind_buttons();
    QTimer *updateTimer;
    public:
        HomePage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
    private slots:
        void update();
    

};