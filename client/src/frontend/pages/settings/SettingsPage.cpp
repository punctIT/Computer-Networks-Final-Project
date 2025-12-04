#include "SettingsPage.h"



void SettingsPage::bind_buttons(){
    
}



SettingsPage::SettingsPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window):Page(data,page_manager,window){
   
    QGridLayout * layout= new QGridLayout();
    stack= new QStackedWidget();
    register_screen=std::make_shared<RegisterScreen>(data,page_manager);

    layout->addWidget(register_screen->get_screen(),0,0);
    page->setLayout(layout);
    bind_buttons();
}

void SettingsPage::on_enter()
{

    window->showMaximized();
}

void SettingsPage::on_exit(){
    
}
