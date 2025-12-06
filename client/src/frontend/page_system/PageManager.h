#pragma once 
#include <QtWidgets/QStackedWidget>
#include <vector>
#include <memory>
#include "Page.h"
#include "../app.h"

class Page;
class App;
class PageManager{
    QStackedWidget *stack;
    std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages;
    std::shared_ptr<App> app;
    std::shared_ptr<Page> page;
    int current_page;
    public:
    PageManager(std::shared_ptr<App> );
    PageManager(std::shared_ptr<Page>);
    void add_page(QWidget* page);
    void set(std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages);
    void change_page(int index);
    int get_current();
    QStackedWidget* GetStack();
};