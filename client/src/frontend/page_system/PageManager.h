#pragma once 
#include <QtWidgets/QStackedWidget>
#include <vector>
#include <memory>

class Page;
class App;
class PageManager{
    QStackedWidget *stack;
    std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages;
    std::shared_ptr<App> app;
    int current_page;
    public:
    PageManager(std::shared_ptr<App> );
    void add_page(QWidget* page);
    void set(std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages);
    void change_page(int index);
    QStackedWidget* GetStack();
};