#include "PageManager.h"
#include "Page.h"
PageManager::PageManager(){
    stack= new QStackedWidget();
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
    (*pages)[index]->on_enter();
}

QStackedWidget *PageManager::GetStack(){
    return stack;
}
