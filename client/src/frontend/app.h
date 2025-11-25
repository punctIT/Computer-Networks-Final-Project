#pragma once



#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QtCore/QThread>
#include <QtCore/QObject>
#include <memory>
#include "page_system/Page.h"
#include <vector>
class DataRequester;
class PageManager;
class LoginPage;
class ConnectPage;
class HomePage;
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