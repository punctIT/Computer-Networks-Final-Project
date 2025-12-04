#include "BlacklistScreen.h"

BlackListScreen::BlackListScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window):
    Page(data,page_manager,window)
{
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(new QLabel("salut test"),0,0);
    page->setLayout(layout);
}
void BlackListScreen::on_enter() {
    // implementare
}

void BlackListScreen::on_exit() {
    // implementare
}