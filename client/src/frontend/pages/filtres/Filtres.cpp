#include "Filtres.h"

FiltresScreen::FiltresScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window):
    Page(data,page_manager,window)
{
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(new QLabel("salut test"),0,0);
    page->setLayout(layout);
}
void FiltresScreen::on_enter() {
    // implementare
}

void FiltresScreen::on_exit() {
    // implementare
}
