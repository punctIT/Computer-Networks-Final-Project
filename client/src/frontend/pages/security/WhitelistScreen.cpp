#include "WhitelistScreen.h"

WhiteListScreen::WhiteListScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window):
    Page(data,page_manager,window)
{
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(new QLabel("salut test white"),0,0);
    page->setLayout(layout);
}
void WhiteListScreen::on_enter() {
    // implementare
}

void WhiteListScreen::on_exit() {
    // implementare
}