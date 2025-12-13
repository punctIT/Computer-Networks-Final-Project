#include "FiltresPage.h"
#include "Filtres.h"

void FiltresPage::bind_buttons()
{
    QObject::connect(filtres,&QPushButton::clicked,[this](){
        filtres_pages->change_page(0);
    });
   
}

QWidget *FiltresPage::get_side_menu()
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
    filtres = new QPushButton("filtres");
    filtres->setCursor(Qt::PointingHandCursor);
    filtres->setStyleSheet(buttonStyle);
    layout->addWidget(filtres);
    
    layout->addStretch();

    menu->setLayout(layout);
    menu->setFixedWidth(200); 

    return menu;
}
FiltresPage::FiltresPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    pages = std::make_shared<std::vector<std::shared_ptr<Page>>>();
    layout->addWidget(get_side_menu());
    auto app_ptr = std::shared_ptr<FiltresPage>(this, [](FiltresPage*) {});
    filtres_pages=std::make_shared<PageManager>(app_ptr);
    pages->push_back(std::make_shared<FiltresScreen>(data,page_manager,window));
   
    for (auto page : *pages){
       filtres_pages->add_page(page->get_page());
    }
    
    updateTimer = new QTimer();
    layout->addWidget(filtres_pages->GetStack());
    page->setLayout(layout);
    connect(updateTimer, &QTimer::timeout, this, &FiltresPage::update);
    updateTimer->setInterval(2000); 
    bind_buttons();
}

void FiltresPage::on_enter()
{
    updateTimer->start();
    filtres_pages->change_page(0);
    window->showMaximized();
   
}
void FiltresPage::update(){
    if(filtres_pages->get_current()==0){
        auto status = data_requester->sent("type:{update_filtres};");
        if(!status){
            qDebug()<<QString::fromStdString(status.error());
        }
    }
    
    
}
void FiltresPage::on_exit()
{
    updateTimer->stop();
}
