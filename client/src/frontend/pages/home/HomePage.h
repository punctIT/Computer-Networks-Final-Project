

#pragma once

#include <memory>
#include "../../page_system/Page.h"

class DataRequester;
class QLineEdit;
class QWidget;
class QPushButton;

class PageManager;
class HomePage:public Page{
    QPushButton *btn;
    void bind_buttons();
    public:
        HomePage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager);
        void on_enter() override;
        void on_exit() override;
};