#pragma once



#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QtCore/QThread>
#include <QtCore/QObject>
#include <memory>

class DataRequester;

class App{
    QStackedWidget *stack;
    QMainWindow *window;
    std::shared_ptr<DataRequester> data_requster;
    public:
        App();

};