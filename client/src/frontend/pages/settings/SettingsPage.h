

#pragma once

#include <memory>
#include "../../page_system/Page.h"
#include <QtWidgets/QStackedWidget>


class RegisterScreen;
class PageManager;
class SettingsPage:public Page{
    QStackedWidget *stack;
    std::shared_ptr<RegisterScreen> register_screen;
    
    void bind_buttons();
    public:
     SettingsPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
        
    
};