

#pragma once

#include <memory>
#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.h"
#include "../../../utils/JUNK.hpp"
#include "WhiteListPopup.hpp"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QtCore/QTimer>



class WhitelistTable{
    QWidget *widget;
    QTableWidget *table;
    std::shared_ptr<DataRequester> data_requester;
    public:
    WhitelistTable(std::shared_ptr<DataRequester> data_requester);
    QWidget* get_widget();
    void add(std::vector<std::string> whitelist_data);
    void clear();
};

class WhiteListScreen:public Page{
    QPushButton *btn;
    std::shared_ptr<AddWhitelistPopup> add_whitelist;
    std::shared_ptr<WhitelistTable> whitelist_table;
    void bind_buttons();
    public:
        WhiteListScreen(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
};


