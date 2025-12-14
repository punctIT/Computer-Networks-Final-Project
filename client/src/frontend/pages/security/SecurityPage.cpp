#include "SecurityPage.h"


void SecurityPage::bind_buttons()
{
    QObject::connect(whitelist,&QPushButton::clicked,[this](){
        security_pages->change_page(0);
        whitelist->setProperty("active", true);
        blacklist->setProperty("active", false);
        whitelist->style()->unpolish(whitelist);
        whitelist->style()->polish(whitelist);
        blacklist->style()->unpolish(blacklist);
        blacklist->style()->polish(blacklist);
    });
    QObject::connect(blacklist,&QPushButton::clicked,[this](){
        security_pages->change_page(1);
        blacklist->setProperty("active", true);
        whitelist->setProperty("active", false);
        whitelist->style()->unpolish(whitelist);
        whitelist->style()->polish(whitelist);
        blacklist->style()->unpolish(blacklist);
        blacklist->style()->polish(blacklist);
    });
    
}

QWidget *SecurityPage::get_side_menu()
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
    
    whitelist = new QPushButton("WhiteList");
    whitelist->setCursor(Qt:: PointingHandCursor);
    whitelist->setStyleSheet(buttonStyle);
    whitelist->setProperty("active", true); // Set as default active

    blacklist = new QPushButton("BlackList");
    blacklist->setCursor(Qt::PointingHandCursor);
    blacklist->setStyleSheet(buttonStyle);
    blacklist->setProperty("active", false);

    layout->addWidget(whitelist);
    layout->addWidget(blacklist);

    layout->addStretch();

    menu->setLayout(layout);
    menu->setFixedWidth(220); 

    return menu;
}

SecurityPage::SecurityPage(std:: shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    
    pages = std::make_shared<std::vector<std::shared_ptr<Page>>>();
    
    auto app_ptr = std::shared_ptr<SecurityPage>(this, [](SecurityPage*) {});
    security_pages=std::make_shared<PageManager>(app_ptr);
    
    pages->push_back(std::make_shared<WhiteListScreen>(data,page_manager,window));
    pages->push_back(std::make_shared<BlackListScreen>(data,page_manager,window));
   
    for (auto page : *pages){
       security_pages->add_page(page->get_page());
    }
    
    updateTimer = new QTimer();
    
    layout->addWidget(get_side_menu());
    layout->addWidget(security_pages->GetStack());
    
    page->setLayout(layout);
    
    connect(updateTimer, &QTimer::timeout, this, &SecurityPage::update);
    updateTimer->setInterval(2000); 
    
    bind_buttons();
}

void SecurityPage:: on_enter()
{
    updateTimer->start();
    security_pages->change_page(0);
    
    // Ensure whitelist button shows as active
    whitelist->setProperty("active", true);
    blacklist->setProperty("active", false);
    whitelist->style()->unpolish(whitelist);
    whitelist->style()->polish(whitelist);
    blacklist->style()->unpolish(blacklist);
    blacklist->style()->polish(blacklist);
    
    window->showMaximized();
}

void SecurityPage:: update(){
    if(security_pages->get_current()==0){
        auto status = data_requester->sent("type:{update_whitelist};");
        if(!status){
            qDebug()<<QString::fromStdString(status.error());
        }
    }
    if(security_pages->get_current()==1){
        auto status = data_requester->sent("type:{update_blacklist};");
        if(!status){
            qDebug()<<QString::fromStdString(status.error());
        }
    }
}

void SecurityPage::on_exit()
{
    updateTimer->stop();
}