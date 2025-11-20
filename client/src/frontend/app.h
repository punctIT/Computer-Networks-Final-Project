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
class App{
    QMainWindow *window;
    std::shared_ptr<PageManager> page_manager;
    std::shared_ptr<DataRequester> data_requster;

    std::vector<std::shared_ptr<Page>> pages;
    public:
        App();

};