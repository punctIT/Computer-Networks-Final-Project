

#pragma once

#include <memory>
#include "../../page_system/Page.h"
#include <QtCore/QTimer>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <format>

#include "../../page_system/PageManager.h"
#include "../../page_system/Page.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.h"
#include "../../../utils/BetterString.hpp"


class FiltresPage:public Page{
    void bind_buttons();
    std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages;
    std::shared_ptr<PageManager> filtres_pages;

    QHBoxLayout *layout;
    QPushButton *filtres;
    QTimer *updateTimer;   
   
    QWidget* get_side_menu();
    public:
        FiltresPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
    private slots:
        void update();
    

};