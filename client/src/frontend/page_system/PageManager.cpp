#include "PageManager.h"

PageManager::PageManager(std::shared_ptr<App> a)
{
    stack= new QStackedWidget();
    current_page=0;
    this->app=a;
}

PageManager::PageManager(std::shared_ptr<Page> a)
{
    stack= new QStackedWidget();
    current_page=0;
    this->page=a;
}

void PageManager::add_page(QWidget* page){
    stack->addWidget(page);
}

void PageManager::set(std::shared_ptr<std::vector<std::shared_ptr<Page>>> pages){
    this->pages=pages;
}

void PageManager::change_page(int index) {
    //qDebug() << "change_page:" << index << "count:" << stack->count();
    
    stack->setCurrentIndex(index);
    
    if (pages && current_page < pages->size()) {
        (*pages)[current_page]->on_exit();
    }
    
    if (pages && index < pages->size()) {
        (*pages)[index]->on_enter();
    }
    
    current_page = index;
    if (app) {
        if (index < 2) {
            app->hide_menu();
        } else {
            app->show_menu();
        }
    }
}
int PageManager::get_current(){
    return current_page;
}
QStackedWidget *PageManager::GetStack(){
    return stack;
}
