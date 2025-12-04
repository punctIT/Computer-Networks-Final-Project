

#pragma once

#include <memory>
#include "../page_system/Page.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../page_system/PageManager.h"
#include "../../server_request/DataRequester.hpp"
#include <QtWidgets/QMainWindow>

class ConnectPage:public Page{
    QLineEdit *ip_input ;
    QLineEdit *port_input ;
    QPushButton * connect_btn ;
    QLabel *error_lbn;
    void bind_buttons();
    public:
        ConnectPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
};
