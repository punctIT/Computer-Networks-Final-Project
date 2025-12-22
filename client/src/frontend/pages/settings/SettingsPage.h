

#pragma once

#include <memory>
#include "../../page_system/Page.h"
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../../../utils/JUNK.hpp"
#include "../../page_system/PageManager.h"
#include "../../../server_request/DataRequester.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include "RegisterScreen.h"

class RegisterScreen;
class PageManager;
class SettingsPage:public Page{
    QStackedWidget *stack;
    std::shared_ptr<RegisterScreen> register_screen;
    QPushButton *register_menu;
    void bind_buttons();
    QWidget* get_side_menu();
    public:
     SettingsPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
        
    
};