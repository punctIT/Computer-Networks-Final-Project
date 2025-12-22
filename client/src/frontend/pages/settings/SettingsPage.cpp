#include "SettingsPage.h"



void SettingsPage::bind_buttons(){
    
}

QWidget *SettingsPage::get_side_menu()
{
      QWidget *menu = new QWidget();
    menu->setStyleSheet("QWidget { background-color: #1E1E1E; }"); 
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5); 
    
    QString buttonStyle = R"(
        QPushButton {
            background-color: #1E1E1E;
            color: #E0E0E0;
            border: none;
            border-left: 4px solid transparent;
            padding: 18px 20px;
            text-align: left;
            font-size: 14px;
            font-weight:  600;
            font-family: 'Segoe UI', sans-serif;
        }
        
        QPushButton:hover {
            background-color: #252525;
            color: #1ABC9C;
            border-left: 4px solid #1ABC9C;
        }
        
        QPushButton:pressed {
            background-color: #0E6655;
            color: #FFFFFF;
            border-left: 4px solid #16A085;
        }
        
        QPushButton[active="true"] {
            background-color: #252525;
            color: #1ABC9C;
            border-left: 4px solid #1ABC9C;
            font-weight: bold;
        }
    )";
    
    register_menu = new QPushButton("Register");
    register_menu->setCursor(Qt:: PointingHandCursor);
    register_menu->setStyleSheet(buttonStyle);
    register_menu->setProperty("active", true); 
    layout->addWidget(register_menu);


    QPushButton *logout = new QPushButton("Logout");
    logout->setCursor(Qt:: PointingHandCursor);
    logout->setStyleSheet(buttonStyle);
    logout->setProperty("active", false); 
    layout->addWidget(logout);

    QObject::connect(logout,&QPushButton::clicked,[this](){
        this->page_manager->change_page(1);
    });

    layout->addStretch();

    menu->setLayout(layout);
    menu->setFixedWidth(220); 

    return menu;
}

SettingsPage::SettingsPage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager,std::shared_ptr <QMainWindow> window):Page(data,page_manager,window){
   
    QGridLayout * layout= new QGridLayout();
    stack= new QStackedWidget();
    register_screen=std::make_shared<RegisterScreen>(data,page_manager);
    layout->addWidget(get_side_menu(),0,0);
    layout->addWidget(register_screen->get_screen(),0,1);
    page->setLayout(layout);
    bind_buttons();
}

void SettingsPage::on_enter()
{

    window->showMaximized();
}

void SettingsPage::on_exit(){
    
}
