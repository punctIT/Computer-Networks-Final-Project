

#pragma once

#include <memory>
#include "../../page_system/Page.h"
#include <QtCore/QTimer>
#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>

#include <format>

#include "../../page_system/PageManager.h"
#include "../../widgets/MainMenu.hpp"
#include "../../../server_request/DataRequester.hpp"
#include "../../../utils/BetterString.hpp"
#include "WhiteListPopup.hpp"


class SecurityPage:public Page{
    QPushButton *btn;
    void bind_buttons();
    std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages;
    std::shared_ptr<PageManager> security_pages;
    QGridLayout *layout;
    QWidget* get_side_menu();
    public:
        SecurityPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window);
        void on_enter() override;
        void on_exit() override;
    private slots:
        void update();
    

};