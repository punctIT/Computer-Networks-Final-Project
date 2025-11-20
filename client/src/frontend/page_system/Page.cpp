#include "Page.h"
#include <QtWidgets/QLabel>

Page::Page(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager){
    this->page = new QWidget();
    this->data_requester=data;
    this->page_manager=page_manager;
}

QWidget *Page::get_page()
{
    return this->page;
}
