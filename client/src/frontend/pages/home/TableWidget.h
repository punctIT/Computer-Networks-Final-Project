#pragma once 

#include <memory>
class PageManager;
class QWidget;
class QPushButton;
class QGridLayout;

class TableMenu{
    QWidget *table;
    public:
    TableMenu();
    QWidget* get_widget();
};