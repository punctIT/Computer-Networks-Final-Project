#pragma once



#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QtCore/QThread>
#include <QtCore/QObject>
#include <memory>
#include "page_system/Page.h"
#include <vector>
#include "../server_request/DataRequester.hpp"
#include "pages/LoginPage.h"
#include "page_system/PageManager.h"
#include "pages/home/HomePage.h"
#include "pages/settings/SettingsPage.h"
#include "pages/dashboard/DashboardPage.h"
#include "pages/security/SecurityPage.h"
#include "pages/ConnectPage.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include "widgets/MainMenu.hpp"

class DataRequester;
class PageManager;

class QGridLayout;
class MainMenu;

class App{
    std::shared_ptr<QMainWindow> window;
    std::shared_ptr<PageManager> page_manager;
    std::shared_ptr<DataRequester> data_requster;
    std::shared_ptr<MainMenu> main_menu;
    std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages;
    
    QGridLayout* layout;
    QWidget* page;
    QWidget* get_window();
    public:
        void show_menu();
        void hide_menu();
        App();

};