#include "FiltersScreen.h"

FiltersScreen::FiltersScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window):
    Page(data,page_manager,window)
{
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(new QLabel("salut filtre"),0,0);
    page->setLayout(layout);
}
void FiltersScreen::on_enter() {
    // implementare
}

void FiltersScreen::on_exit() {
    // implementare
}