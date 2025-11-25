#include "PageManager.h"
#include "Page.h"
#include "../app.h"
PageManager::PageManager(std::shared_ptr<App> a)
{
    stack= new QStackedWidget();
    current_page=0;
    this->app=a;
}

void PageManager::add_page(QWidget* page){
    stack->addWidget(page);
}

void PageManager::set(std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages){
    this->pages=pages;
}

void PageManager::change_page(int index){
    //qDebug()<<stack->count();
    stack->setCurrentIndex(index);
    (*pages)[current_page]->on_exit();
    (*pages)[index]->on_enter();
    current_page=index;
    if(index<2){
        app->hide_menu();
    }
    else {
        app->show_menu();
    }
}

QStackedWidget *PageManager::GetStack(){
    return stack;
}
