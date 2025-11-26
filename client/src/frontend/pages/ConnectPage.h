

#pragma once

#include <memory>
#include "../page_system/Page.h"
class DataRequester;
class QLineEdit;
class QWidget;
class QPushButton;
class QLabel;

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
