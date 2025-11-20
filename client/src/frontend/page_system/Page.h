

#pragma once

#include <memory>

class DataRequester;
class QLineEdit;
class QWidget;
class QPushButton;

class PageManager;
class Page{
    protected:
        QWidget * page;
        std::shared_ptr <DataRequester> data_requester;
        std::shared_ptr <PageManager> page_manager;
    public:
        Page(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager);
        QWidget* get_page();

};