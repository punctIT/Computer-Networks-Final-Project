#include "SecurityPage.h"


void SecurityPage::bind_buttons()
{
    QObject::connect(btn,&QPushButton::clicked,[this](){
        // auto data = data_requester->sent_request("type:{add_blacklist_ip};source_name:{local};ip:{127.0.0.1};admin_username:{admin};");
        // if(data){
        //     qDebug()<<data.value().c_str();
        // }
        //popup_whitelist_add->showCentered();
    });
}

QWidget *SecurityPage::get_side_menu()
{
    return nullptr;
}

SecurityPage::SecurityPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    
    //popup_whitelist_add=std::make_shared<AddWhitelistPopup>(window.get(),data_requester,400,200); 
    layout = new QGridLayout();
    btn = new QPushButton("sent");
    QLabel *label = new QLabel("Security");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label,1,0);
    layout->addWidget(btn,1,1);
    page->setLayout(layout);
    
    auto app_ptr = std::shared_ptr<SecurityPage>(this, [](SecurityPage*) {});
    security_pages=std::make_shared<PageManager>(app_ptr);
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
