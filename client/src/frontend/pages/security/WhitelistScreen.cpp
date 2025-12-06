#include "WhitelistScreen.h"

WhiteListScreen::WhiteListScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window):
    Page(data,page_manager,window)
{
    QGridLayout *layout = new QGridLayout;
    add_whitelist=std::make_shared<AddWhitelistPopup>(window.get(),data_requester,400,200); 
    layout->addWidget(new QLabel("salut test white"),0,0);
    btn = new QPushButton("add new");
    layout->addWidget(btn,0,1);
    QObject::connect(btn,&QPushButton::clicked,[this](){
        add_whitelist->showCentered();
    });
    page->setLayout(layout);
}
void WhiteListScreen::on_enter() {
    // implementare
}

void WhiteListScreen::on_exit() {
    // implementare
}