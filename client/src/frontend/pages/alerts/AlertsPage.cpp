#include "AlertsPage.h"
#include <format>

void AlertsPage::bind_buttons()
{
   connect(data_requester.get(), &DataRequester::UpdateAlertsDashboard, 
        this, [this](QString mesaj) {
            qDebug()<<mesaj;
            std::vector<AlertData> alerts;
            auto data = BetterString::split(mesaj.toStdString(),"{}");
            for(auto alert : data){
                auto content = BetterString:: split(alert,"[]");
                if(content.size()<7){
                    continue;
                }
                AlertData a;
                a.id=content[0];
                a.alert_name = content[1];
                a.category = content[2];
                try
                {
                    a.severity = stoi(content[3]);
                    last_alert=stoi(content[0])+1;
                }
                catch(const std::exception& e){
                    continue;
                }
                a. status = content[6];
                a. timestamp = content[7];
                a.details = content[5];
                alerts.push_back(a);
            }
            
            alerts_table->add(alerts);
    });
   
}

AlertsPage:: AlertsPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    last_alert=0;
    layout = new QVBoxLayout();
    popup = std::make_shared<AlertsPopup>(window.get(),data_requester,100,200);
    layout->setContentsMargins(30, 20, 30, 20);
    layout->setSpacing(20);
    
    QLabel *title = new QLabel("Alerts Dashboard");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 28px; font-weight: bold; color: #FFFFFF; padding: 15px;");
    
    alerts_table=std::make_shared<AlertsTable>(popup);
   
    layout->addWidget(title);
    layout->addWidget(alerts_table->get_widget());
    
    updateTimer = new QTimer();
   
    page->setLayout(layout);
    connect(updateTimer, &QTimer::timeout, this, &AlertsPage:: update);
    updateTimer->setInterval(2000); 
    bind_buttons();
}

void AlertsPage::on_enter()
{
    updateTimer->start();
    window->showMaximized();
   
}
void AlertsPage::update(){
    this->data_requester->sent(std:: format("type:{{alerts_dashboard}};last_alert:{{{}}};",last_alert));
}
void AlertsPage::on_exit()
{
    updateTimer->stop();
}


AlertsTable::AlertsTable( std::shared_ptr<AlertsPopup> popup)
{
    this->popup=popup;
    alertCount = 0;
    widget = new QWidget();
    widget->setStyleSheet("background-color: transparent;");
    
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QFrame *frame = new QFrame();
    frame->setObjectName("AlertsFrame");
    frame->setStyleSheet(
        "QFrame#AlertsFrame {"
        "   background-color:  #252525;"
        "   border-radius: 15px;"
        "   border:  2px solid #1ABC9C;"
        "}"
        "QScrollArea {"
        "   background-color: #252525;"
        "   border: none;"
        "}"
        "QWidget {"
        "   background-color: #252525;"
        "}"
        "QScrollBar: vertical {"
        "   background:  #1E1E1E;"
        "   width: 12px;"
        "   border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: #1ABC9C;"
        "   border-radius: 6px;"
        "}"
        "QScrollBar:: handle:vertical:hover {"
        "   background: #16A085;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line: vertical {"
        "   height:  0px;"
        "}"
    );
    
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(20, 20, 20, 20);

    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("background-color:  #252525; border: none;");

    contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color: #252525;");
    
    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setSpacing(12);
    contentLayout->addStretch();

    scrollArea->setWidget(contentWidget);
    frameLayout->addWidget(scrollArea);
    mainLayout->addWidget(frame);
}

QWidget* AlertsTable::get_widget()
{
    return this->widget;
}

void AlertsTable::clear()
{
    QLayoutItem *item;
    while ((item = contentLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
    contentLayout->addStretch();
    alertCount = 0;
}

void AlertsTable::add(std::vector<AlertData> alerts_data)
{
    for(const auto& alert :  alerts_data)
    {
        QFrame *alertFrame = new QFrame();
        alertFrame->setFixedHeight(70);
        alertFrame->setStyleSheet(
            "QFrame {"
            "   background-color: #2b2b2b;"
            "   border: 1px solid #404040;"
            "   border-radius: 10px;"
            "}"
            "QFrame: hover {"
            "   background-color: #333333;"
            "   border: 1px solid #1ABC9C;"
            "}"
        );

        QHBoxLayout *layout = new QHBoxLayout(alertFrame);
        layout->setContentsMargins(20, 10, 20, 10);
        layout->setSpacing(15);

        QLabel *nameLabel = new QLabel(QString:: fromStdString(alert.alert_name));
        nameLabel->setStyleSheet("font-size:  14px; font-weight:  bold; color: #FFFFFF; background: transparent; border: none;");
        nameLabel->setFixedWidth(200);
        layout->addWidget(nameLabel);

        QLabel *categoryLabel = new QLabel(QString::fromStdString(alert.category));
        categoryLabel->setStyleSheet("color: #B0B0B0; font-size: 13px; background: transparent; border: none;");
        categoryLabel->setFixedWidth(150);
        layout->addWidget(categoryLabel);

        QString severityText;
        QString severityColor;
        if(alert.severity == 1) { severityText = "LOW"; severityColor = "#4CAF50"; }
        else if(alert.severity == 2) { severityText = "MED"; severityColor = "#FF9800"; }
        else if(alert.severity == 3) { severityText = "HIGH"; severityColor = "#F44336"; }
        else { severityText = "CRIT"; severityColor = "#9C27B0"; }

        QLabel *severityLabel = new QLabel(severityText);
        severityLabel->setStyleSheet(QString("color: %1; font-weight:  bold; font-size: 13px; background: transparent; border:  none;").arg(severityColor));
        severityLabel->setFixedWidth(80);
        severityLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(severityLabel);

        QLabel *statusLabel = new QLabel(QString::fromStdString(alert.status));
        statusLabel->setStyleSheet("color: #FFD700; font-size: 13px; background: transparent; border: none;");
        statusLabel->setFixedWidth(100);
        layout->addWidget(statusLabel);

        QLabel *timeLabel = new QLabel(QString::fromStdString(alert.timestamp));
        timeLabel->setStyleSheet("color:  #808080; font-size:  12px; background: transparent; border: none;");
        layout->addWidget(timeLabel);

        layout->addStretch();

        QPushButton *showBtn = new QPushButton(">");
        showBtn->setFixedSize(35, 35);
        showBtn->setCursor(Qt:: PointingHandCursor);
        showBtn->setStyleSheet(
            "QPushButton {"
            "   background-color: rgba(26, 188, 156, 0.2);"
            "   color: #1ABC9C;"
            "   border:  1px solid #1ABC9C;"
            "   border-radius: 8px;"
            "   font-size: 16px;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background-color: #1ABC9C;"
            "   color: #121212;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #0E6655;"
            "   color: #FFFFFF;"
            "}"
        );
        
        QString details = QString::fromStdString(alert.details);
        QObject::connect(showBtn, &QPushButton::clicked, [this,details]() {
            popup->showCentered();
        });
        
        layout->addWidget(showBtn);

        contentLayout->insertWidget(contentLayout->count() - 1, alertFrame);
        alertCount++;
        
        if(alertCount > 100)
        {
            int lastIndex = contentLayout->count() - 2;
            QLayoutItem *item = contentLayout->takeAt(lastIndex);
            if (item && item->widget()) {
                delete item->widget();
                delete item;
                alertCount--;
            }
        }
    }
}