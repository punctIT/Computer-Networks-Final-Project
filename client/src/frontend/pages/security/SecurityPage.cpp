#include "SecurityPage.h"


void SecurityPage::bind_buttons()
{
    QObject::connect(whitelist,&QPushButton::clicked,[this](){
        security_pages->change_page(0);
    });
    QObject::connect(blacklist,&QPushButton::clicked,[this](){
        security_pages->change_page(1);
    });
}

QWidget *SecurityPage::get_side_menu()
{
    QGridLayout *layout = new QGridLayout;
    whitelist= new QPushButton("WhiteList");
    blacklist = new QPushButton("Blacklist");
    layout->addWidget(whitelist,0,0);
    layout->addWidget(blacklist,1,0);
    QWidget *menu = new QWidget();
    menu->setLayout(layout);
    return menu;
}

SecurityPage::SecurityPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    layout = new QGridLayout();
    pages = std::make_shared<std::vector<std::shared_ptr<Page>>>();
    //popup_whitelist_add=std::make_shared<AddWhitelistPopup>(window.get(),data_requester,400,200); 
  
    layout->addWidget(get_side_menu(),0,0);
    auto app_ptr = std::shared_ptr<SecurityPage>(this, [](SecurityPage*) {});
    security_pages=std::make_shared<PageManager>(app_ptr);
    pages->push_back(std::make_shared<WhiteListScreen>(data,page_manager,window));
    pages->push_back(std::make_shared<BlackListScreen>(data,page_manager,window));
    for (auto page : *pages){
       security_pages->add_page(page->get_page());
    }
    security_pages->change_page(0);
    layout->addWidget(security_pages->GetStack(),0,1);
    page->setLayout(layout);
    bind_buttons();
}

void SecurityPage::on_enter()
{
    window->showMaximized();
   
}
void SecurityPage::update(){
    qDebug()<<"update";
    
}
void SecurityPage::on_exit()
{

}
