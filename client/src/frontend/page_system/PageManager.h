#pragma once 
#include <QtWidgets/QStackedWidget>
#include <vector>
#include <memory>

class Page;

class PageManager{
    QStackedWidget *stack;
    std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages;
    public:
    PageManager();
    void add_page(QWidget* page);
    void set(std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages);
    void change_page(int index);
    QStackedWidget* GetStack();
};