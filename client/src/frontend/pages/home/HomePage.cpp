#include "HomePage.h"

#include "HomePage.h"
#include "../../style/HomeStyle.hpp"

void make_big_tile(QPushButton* btn) {
    btn->setCursor(Qt::PointingHandCursor);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QWidget *HomePage::get_top_layout()
{
 
    QWidget *top = new QWidget(); 
    QVBoxLayout *main_top = new QVBoxLayout();
    QGridLayout *layout = new QGridLayout();
    layout->setSpacing(15); 


    QPushButton *security = new QPushButton("Security");
    QPushButton *dashboard = new QPushButton("Dashboard");
    QPushButton *filters =  new QPushButton("Filters"); 
    QPushButton *settings = new QPushButton("Settings");
    

    make_big_tile(security);
    make_big_tile(dashboard);
    make_big_tile(filters);
    make_big_tile(settings);

    layout->addWidget(dashboard, 0, 0);
    layout->addWidget(security, 0, 1);
    layout->addWidget(filters, 1, 0);
    layout->addWidget(settings, 1, 1);

    
    QLabel *title = new QLabel("Home Menu");
    title->setAlignment(Qt::AlignCenter);


    main_top->addWidget(title);
    main_top->addLayout(layout);
    
    main_top->setAlignment(Qt::AlignCenter); 

    top->setLayout(main_top);

   
    top->setAttribute(Qt::WA_StyledBackground, true);
    top->setStyleSheet(QString::fromStdString(top_part_home_style()));

    return top;
}

void HomePage::bind_buttons()
{
    connect(data_requester.get(), &DataRequester::LogsData, 
        this, [this](QString mesaj) {
           table_widget->add(BetterString::split(mesaj.toStdString(),"{}"));
        });
}

HomePage::HomePage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager,std::shared_ptr <QMainWindow> window) : Page(data, page_manager,window)
{
    QVBoxLayout *layout = new QVBoxLayout();
    table_widget= std::make_shared<TableMenu>();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(get_top_layout());
    layout->addWidget(table_widget->get_widget());
    page->setLayout(layout);

    updateTimer = new QTimer(this); 

    connect(updateTimer, &QTimer::timeout, this, &HomePage::update);
    updateTimer->setInterval(2000); 

    bind_buttons();
}

void HomePage::on_enter()
{
    window->showMaximized();
    
    qDebug()<<"enter Home";
    updateTimer->start();
}
void HomePage::update(){
    auto data = data_requester->sent(std::format("type:{{logs}};last_id:{{{}}};",table_widget->get_id()));
    if(!data){
         qDebug()<<data.error().c_str();
    }
     
    
}
void HomePage::on_exit()
{
     updateTimer->stop();
     qDebug()<<"leave Home";
}
