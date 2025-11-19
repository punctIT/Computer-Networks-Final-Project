#pragma once



#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QtCore/QThread>
#include <QtCore/QObject>
#include <memory>

class DataRequester;
class PageManager;
class LoginPage;
class ConnectPage;
class App{
    QMainWindow *window;
    std::shared_ptr<PageManager> page_manager;
    std::shared_ptr<DataRequester> data_requster;
    std::shared_ptr<LoginPage> login_page;
    std::shared_ptr<ConnectPage> connect_page;
    public:
        App();

};