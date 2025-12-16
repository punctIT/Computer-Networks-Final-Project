#include "HomePage.h"
#include "../../style/HomeStyle.hpp"
#include <QMessageBox>

void make_big_tile(QPushButton* btn) {
    btn->setCursor(Qt::PointingHandCursor);
    btn->setSizePolicy(QSizePolicy:: Expanding, QSizePolicy:: Expanding);
    btn->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(255, 255, 255, 0.05);"
        "   color: #B0B0B0;"
        "   border:  none;"
        "   border-radius: 20px;"
        "   padding: 10px 30px;"
        "   font-size: 14px;"
        "   font-weight: 600;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #1ABC9C;"
        "   color: #121212;"
        "}"
        "QPushButton:pressed {"
        "   background-color:  #0E6655;"
        "   color: #FFFFFF;"
        "   padding-top:  12px;"
        "   padding-bottom: 8px;"
        "}"
    );
}

QWidget *HomePage::get_top_layout()
{
 
    QWidget *top = new QWidget(); 
    QVBoxLayout *main_top = new QVBoxLayout();
    QGridLayout *layout = new QGridLayout();
    layout->setSpacing(15); 


    QPushButton *security = new QPushButton("Security");
    QPushButton *dashboard = new QPushButton("Dashboard");
    QPushButton *filters = new QPushButton("Filters"); 
    QPushButton *settings = new QPushButton("Settings");
    

    make_big_tile(security);
    make_big_tile(dashboard);
    make_big_tile(filters);
    make_big_tile(settings);

    layout->addWidget(dashboard, 0, 0);
    layout->addWidget(security, 0, 1);
    layout->addWidget(filters, 1, 0);
    layout->addWidget(settings, 1, 1);

    QObject::connect(dashboard,&QPushButton::clicked,[this](){
        page_manager->change_page(3);   
    });
    QObject::connect(security,&QPushButton:: clicked,[this](){
        page_manager->change_page(5);   
    });
    QObject::connect(filters,&QPushButton::clicked,[this](){
        page_manager->change_page(6);
    });
    QObject::connect(settings,&QPushButton::clicked,[this](){
        page_manager->change_page(4);   
    });
    
  
    main_top->addLayout(layout);
    
    main_top->setAlignment(Qt::AlignCenter); 

    top->setLayout(main_top);

   
    top->setAttribute(Qt::WA_StyledBackground, true);
    top->setStyleSheet(QString::fromStdString(top_part_home_style()));

    return top;
}

void HomePage::bind_buttons()
{
    connect(data_requester. get(), &DataRequester::LogsData, 
        this, [this](QString mesaj) {
            qDebug()<<mesaj;
            auto data = JUNK::deserialize(mesaj.toStdString());
            if(data.has_value()==false){
                qDebug()<<data.error().c_str();
                return ;
            }
            if(data.value()["whitelist"].has_value()&&data.value()["blacklist"].has_value()){
                try{
                    this->card1->updateValue(stoi(data.value()["whitelist"].value()));
                    this->card2->updateValue(stoi(data.value()["blacklist"].value()));
                }
                catch(const std::exception& e){
                    qDebug() << e.what() ;
                }
                
                
            }
           //table_widget->add(BetterString:: split(mesaj. toStdString(),"{}"));
        }); 
    connect(data_requester.get(), &DataRequester::lost_connection, this, [this]() {
        QMessageBox::critical(window. get(), "Connection Error", "connextion lost. .");
        page_manager->change_page(0);    
    });
}

HomePage::HomePage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager,std::shared_ptr <QMainWindow> window) : Page(data, page_manager,window)
{
    QVBoxLayout *layout = new QVBoxLayout();
    card1= std::make_shared<StatCard>("Whitelist","0","sources");
    card2= std::make_shared<StatCard>("Blacklist","0","sources");
    card3= std::make_shared<StatCard>("Uptime","UNKNOWN","time");
    card4= std::make_shared<StatCard>("Database Size","UNKNOWN","size");
    layout->setContentsMargins(30, 20, 30, 20);
    layout->setSpacing(20);
    
    QGridLayout *layout_top = new QGridLayout();
    layout_top->setSpacing(20);
    layout_top->setContentsMargins(0, 0, 0, 0);
    
    QLabel *title = new QLabel("Home Menu");
    title->setAlignment(Qt:: AlignCenter);
    title->setStyleSheet("font-size:  28px; font-weight: bold; color: #FFFFFF; padding:  15px;");


    layout->addWidget(title);
    layout_top->addWidget(card1->get_widget(),0,0);
    layout_top->addWidget(card2->get_widget(),0,1);
    layout_top->addWidget(card3->get_widget(),0,2);
    layout_top->addWidget(card4->get_widget(),0,3);
    layout->addLayout(layout_top);
    
    
    layout->addWidget(get_top_layout());
    page->setLayout(layout);

    updateTimer = new QTimer(this); 

    connect(updateTimer, &QTimer::timeout, this, &HomePage::update);
    updateTimer->setInterval(2000); 

    bind_buttons();
}

void HomePage:: on_enter()
{
      update();
    window->showMaximized();
    
    qDebug()<<"enter Home";
    updateTimer->start();
}
void HomePage::update(){
    auto data = data_requester->sent(std::format("type:{{logs}};"));
     if(! data){
          qDebug()<<data.error().c_str();
     }
     
    
}
void HomePage::on_exit()
{
     updateTimer->stop();
     qDebug()<<"leave Home";
}



StatCard::StatCard(const QString& title, 
                   const QString& initialValue, 
                   const QString& subtitle)
{
    card = new QFrame();
    card->setMinimumHeight(140);
    card->setMaximumHeight(160);
    card->setStyleSheet(
        "QFrame {"
        "   background-color: #252525;" 
        "   border: 2px solid #1ABC9C;"
        "   border-radius: 15px;"
        "}"
        "QLabel { border: none; background:  transparent; }"
    );
    
    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(20, 15, 20, 15);
    layout->setSpacing(8);
    
    lblTitle = new QLabel(title);
    lblTitle->setStyleSheet("color: #B0B0B0; font-weight: 600; font-size: 13px;");
    lblTitle->setAlignment(Qt::AlignLeft);
    
    lblValue = new QLabel(initialValue);
    lblValue->setStyleSheet("color:  #FFFFFF; font-weight:  bold; font-size: 32px;");
    lblValue->setAlignment(Qt::AlignCenter);
    
    lblSubtitle = new QLabel(subtitle);
    lblSubtitle->setStyleSheet("color: #707070; font-size: 11px;");
    lblSubtitle->setAlignment(Qt::AlignCenter);
    
    layout->addWidget(lblTitle);
    layout->addStretch();
    layout->addWidget(lblValue);
    layout->addWidget(lblSubtitle);
    layout->addStretch();
    
    card->setLayout(layout);
}

QWidget* StatCard::get_widget()
{
    return card;
}

void StatCard::updateValue(const QString& value)
{
    lblValue->setText(value);
}

void StatCard:: updateValue(int value)
{
    lblValue->setText(QString::number(value));
}