#pragma once 
#include <QtWidgets/QStackedWidget>

class PageManager{
    QStackedWidget *stack;
    public:
    PageManager();
    void add_page(QWidget* page);
    void change_page(int index);
    QStackedWidget* GetStack();
};