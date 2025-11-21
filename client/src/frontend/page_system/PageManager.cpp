#include "PageManager.h"
#include "Page.h"
PageManager::PageManager(){
    stack= new QStackedWidget();
    current_page=0;
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
}

QStackedWidget *PageManager::GetStack(){
    return stack;
}
