#include "PageManager.h"

PageManager::PageManager(){
    stack= new QStackedWidget();
}

void PageManager::add_page(QWidget* page){
    stack->addWidget(page);
}

void PageManager::change_page(int index){
    qDebug()<<stack->count();
    stack->setCurrentIndex(index);
}

QStackedWidget *PageManager::GetStack(){
    return stack;
}
