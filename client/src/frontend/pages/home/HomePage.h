

#pragma once

#include <memory>

#include <QtCore/QTimer>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>

#include <format>
#include "TableWidget.h"

#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.h"
#include "../../page_system/Page.h"
#include "../../../utils/BetterString.hpp"



#include <QFrame>
#include <QLabel>
#include <QWidget>

class StatCard
{
private:
    QFrame *card;
    QLabel *lblTitle;
    QLabel *lblValue;
    QLabel *lblSubtitle;
    
public:
    StatCard(const QString& title, 
             const QString& initialValue = "0", 
             const QString& subtitle = "");
    
    QWidget* get_widget();
    
    void updateValue(const QString& value);
    void updateValue(int value);
};

class HomePage:public Page{
    QPushButton *btn;
    std::shared_ptr<StatCard> card1;
    std::shared_ptr<StatCard> card2;
    std::shared_ptr<StatCard> card3;
    std::shared_ptr<StatCard> card4;
    QWidget *get_top_layout();
    void bind_buttons();
    QTimer *updateTimer;
   
    public:
        HomePage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
    private slots:
        void update();
    

};