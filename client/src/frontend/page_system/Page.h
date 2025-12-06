

#pragma once

#include <memory>
#include <QtCore/QObject>
#include <QWidget>

class DataRequester;
class QLineEdit;
class QWidget;
class QPushButton;
class QMainWindow;

class PageManager;

class Page : public QWidget {
    Q_OBJECT
    protected:
        QWidget * page;
        std::shared_ptr <DataRequester> data_requester;
        std::shared_ptr <PageManager> page_manager;
        std::shared_ptr <QMainWindow> window;
    public:
        Page(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window){
            this->page = new QWidget();
            this->data_requester=data;
            this->page_manager=page_manager;
            this->window=window;
        }
        virtual void on_enter() =0;
        virtual void on_exit()=0;
        QWidget* get_page(){
            return this->page;
        }


};