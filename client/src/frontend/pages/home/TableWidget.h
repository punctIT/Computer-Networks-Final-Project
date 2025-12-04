#pragma once 
#include <vector>
#include <string>
#include <memory>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <string>
#include <iostream>
#include "../../../utils/BetterString.hpp"

class PageManager;
class QWidget;
class QTableWidget;class QTableWidgetItem;

class TableMenu{
    QWidget *widget;
    QTableWidget *table;
    unsigned int last_id ;
    public:
    TableMenu();
    QWidget* get_widget();
    void add(std::vector<std::string> logs);
    void pop();
    unsigned int get_id();
};