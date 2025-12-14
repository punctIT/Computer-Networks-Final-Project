

#pragma once

#include <memory>
#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.h"
#include "../../../utils/JUNK.hpp"
#include "BlackListPopup.hpp"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QtCore/QTimer>



class BlacklistTable{
    QWidget *widget;
    QTableWidget *table;
    std::shared_ptr<DataRequester> data_requester;
    public:
    BlacklistTable( std::shared_ptr<DataRequester> data_requester);
    QWidget* get_widget();
    void add(std::vector<std::string> Blacklist_data);
    void clear();
};

class BlackListScreen:public Page{
    QPushButton *btn;
    std::shared_ptr<AddBlacklistPopup> add_Blacklist;
    std::shared_ptr<BlacklistTable> Blacklist_table;
    void bind_buttons();
    public:
        BlackListScreen(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
};


