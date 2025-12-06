#include "SecurityPage.h"


void SecurityPage::bind_buttons()
{
    QObject::connect(whitelist,&QPushButton::clicked,[this](){
        security_pages->change_page(0);
    });
    QObject::connect(blacklist,&QPushButton::clicked,[this](){
        security_pages->change_page(1);
    });
     QObject::connect(filtres,&QPushButton::clicked,[this](){
        security_pages->change_page(2);
    });
}

QWidget *SecurityPage::get_side_menu()
{
    QWidget *menu = new QWidget();
    menu->setStyleSheet("background-color: #2D2D30;"); 
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0); 
    QString buttonStyle = R"(
        QPushButton {
            background-color: transparent;
            color: #FFFFFF;
            border: none;
            padding: 15px;
            text-align: left;
            font-size: 14px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #3E3E42;
            border-left: 5px solid #007ACC; /* O linie colorată în stânga la hover */
        }
        QPushButton:pressed {
            background-color: #007ACC;
        }
    )";
    whitelist = new QPushButton("WhiteList");
    whitelist->setCursor(Qt::PointingHandCursor);
    whitelist->setStyleSheet(buttonStyle);

    blacklist = new QPushButton("BlackList");
    blacklist->setCursor(Qt::PointingHandCursor);
    blacklist->setStyleSheet(buttonStyle);

    filtres = new QPushButton("Filtres");
    filtres->setCursor(Qt::PointingHandCursor);
    filtres->setStyleSheet(buttonStyle);
    layout->addWidget(whitelist);
    layout->addWidget(blacklist);
    layout->addWidget(filtres);
    layout->addStretch();

    menu->setLayout(layout);
    menu->setFixedWidth(200); 

    return menu;
}
SecurityPage::SecurityPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    pages = std::make_shared<std::vector<std::shared_ptr<Page>>>();
    layout->addWidget(get_side_menu());
    auto app_ptr = std::shared_ptr<SecurityPage>(this, [](SecurityPage*) {});
    security_pages=std::make_shared<PageManager>(app_ptr);
    pages->push_back(std::make_shared<WhiteListScreen>(data,page_manager,window));
    pages->push_back(std::make_shared<BlackListScreen>(data,page_manager,window));
    pages->push_back(std::make_shared<FiltersScreen>(data,page_manager,window));
    for (auto page : *pages){
       security_pages->add_page(page->get_page());
    }
    
    updateTimer = new QTimer();
    layout->addWidget(security_pages->GetStack());
    page->setLayout(layout);
    connect(updateTimer, &QTimer::timeout, this, &SecurityPage::update);
    updateTimer->setInterval(2000); 
    bind_buttons();
}

void SecurityPage::on_enter()
{
    updateTimer->start();
    security_pages->change_page(0);
    window->showMaximized();
   
}
void SecurityPage::update(){
    if(security_pages->get_current()==0){
        auto status = data_requester->sent("type:{update_whitelist};");
        if(!status){
            qDebug()<<QString::fromStdString(status.error());
        }
    }
    
    
}
void SecurityPage::on_exit()
{
    updateTimer->stop();
}
