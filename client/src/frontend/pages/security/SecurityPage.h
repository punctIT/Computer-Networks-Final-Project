

#pragma once

#include <memory>
#include "../../page_system/Page.h"
#include <QtCore/QTimer>
#include <QtCore/QObject>

class DataRequester;
class QLineEdit;
class QWidget;
class QPushButton;

class TableMenu;

class MainMenu;
class PageManager;
class SecurityPage:public Page{
    QPushButton *btn;
    void bind_buttons();
    QTimer *updateTimer;
    public:
        SecurityPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
    private slots:
        void update();
    

};