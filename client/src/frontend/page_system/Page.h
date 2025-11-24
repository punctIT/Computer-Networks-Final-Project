

#pragma once

#include <memory>

class DataRequester;
class QLineEdit;
class QWidget;
class QPushButton;
class QMainWindow;

class PageManager;
class Page{
    protected:
        QWidget * page;
        std::shared_ptr <DataRequester> data_requester;
        std::shared_ptr <PageManager> page_manager;
        std::shared_ptr <QMainWindow> window;
    public:
        Page(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        virtual void on_enter() =0;
        virtual void on_exit()=0;
        QWidget* get_page();

};