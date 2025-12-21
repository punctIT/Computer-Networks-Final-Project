#include "FiltresPage.h"
#include "../../style/SecurityStyle.hpp"

void FiltresPage::bind_buttons()
{
    connect(data_requester. get(), &DataRequester::UpdateFiltres, 
        this, [this](QString mesaj) {
           qDebug()<<"update filtres tables";
           auto data = JUNK:: deserialize(mesaj. toStdString());
           
           if(data.has_value() && data.value()["types"].has_value()){
                type_table->clear();
                type_table->add(BetterString::split(data. value()["types"].value(),":;:"));
           }
           
           if(data.has_value() && data.value()["msg"].has_value()){
                message_table->clear();
                message_table->add(BetterString::split(data.value()["msg"].value(),":;:"));
           }
           
           if(data.has_value() && data.value()["alerts"].has_value()){
                alert_table->clear();
                alert_table->add(BetterString::split(data.value()["alerts"].value(),":;:"));
           }
        });
}

FiltresPage::FiltresPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) :  Page(data, page_manager, window)
{
    layout = new QGridLayout();
    popup = std::make_shared<AddPopup>(window. get(),data_requester,400,400);
    type_table = std::make_shared<TypeFiltresTable>(data_requester);
    message_table = std::make_shared<MessageFiltresTable>(data_requester);
    alert_table = std::make_shared<CustomAlertsTable>(data_requester);
    
    btn_add_type = new QPushButton("Add Type Filter");
    btn_add_type->setCursor(Qt::PointingHandCursor);
    btn_add_type->setFixedHeight(40);
    btn_add_type->setStyleSheet(R"(
        QPushButton {
            background-color: #1ABC9C;
            color: #FFFFFF;
            border: none;
            border-radius: 20px;
            padding: 10px 25px;
            font-weight: bold;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #16A085;
        }
    )");
    
    btn_add_message = new QPushButton("Add Message Filter");
    btn_add_message->setCursor(Qt::PointingHandCursor);
    btn_add_message->setFixedHeight(40);
    btn_add_message->setStyleSheet(R"(
        QPushButton {
            background-color: #1ABC9C;
            color:  #FFFFFF;
            border:  none;
            border-radius:  20px;
            padding:  10px 25px;
            font-weight: bold;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #16A085;
        }
    )");
    
    btn_add_alert = new QPushButton("Add Custom Alert");
    btn_add_alert->setCursor(Qt:: PointingHandCursor);
    btn_add_alert->setFixedHeight(40);
    btn_add_alert->setStyleSheet(R"(
        QPushButton {
            background-color:  #1ABC9C;
            color: #FFFFFF;
            border: none;
            border-radius: 20px;
            padding: 10px 25px;
            font-weight: bold;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #16A085;
        }
    )");
    QObject::connect(btn_add_alert,&QPushButton::clicked,[this](){
        popup->showCentered();
        popup->update("alert");
    });
    QObject::connect(btn_add_type,&QPushButton::clicked,[this](){
        popup->showCentered();
        popup->update("type");
    });
     QObject::connect(btn_add_message,&QPushButton:: clicked,[this](){
        popup->showCentered();
        popup->update("message");
    });
    QLabel *title1 = new QLabel("Type Filtres");
    title1->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");
    
    QLabel *title2 = new QLabel("Message Filtres");
    title2->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");
    
    QLabel *title3 = new QLabel("Custom Alerts");
    title3->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");
    
    layout->addWidget(title1, 0, 0);
    layout->addWidget(btn_add_type, 1, 0);
    layout->addWidget(type_table->get_widget(), 2, 0);
    
    layout->addWidget(title2, 0, 1);
    layout->addWidget(btn_add_message, 1, 1);
    layout->addWidget(message_table->get_widget(), 2, 1);
    
    layout->addWidget(title3, 0, 2);
    layout->addWidget(btn_add_alert, 1, 2);
    layout->addWidget(alert_table->get_widget(), 2, 2);
    
    updateTimer = new QTimer();
    connect(updateTimer, &QTimer::timeout, this, &FiltresPage::update);
    updateTimer->setInterval(2000);
    
    bind_buttons();
    page->setLayout(layout);
}

void FiltresPage::on_enter()
{
    update();
    updateTimer->start();
    window->showMaximized();
}

void FiltresPage::update()
{
    auto status = data_requester->sent("type:{update_filtres};");
    if(!status){
        qDebug()<<QString::fromStdString(status. error());
    }
}

void FiltresPage::on_exit()
{
    updateTimer->stop();
}

TypeFiltresTable::TypeFiltresTable(std::shared_ptr<DataRequester> data_requester)
{
    this->data_requester = data_requester;
    this->popup = popup;
    widget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    QFrame *frame = new QFrame();
    frame->setObjectName("TableFrame");
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(0, 10, 0, 10);

    table = new QTableWidget();
    table->setColumnCount(2);
    
    QStringList headers = {"Keyword", "Remove"};
    table->setHorizontalHeaderLabels(headers);

    table->verticalHeader()->setDefaultSectionSize(60);
    table->verticalHeader()->setVisible(false);
    
    table->setShowGrid(false);
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QAbstractItemView::NoSelection);
   
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView:: Fixed);
    table->setColumnWidth(1, 150);

    widget->setStyleSheet(QString::fromStdString(get_table_style()));

    frameLayout->addWidget(table);
    mainLayout->addWidget(frame);
}

QWidget *TypeFiltresTable::get_widget()
{
    return this->widget;
}

void TypeFiltresTable::clear()
{
    table->setRowCount(0);
}

void TypeFiltresTable::add(std::vector<std::string> data)
{
    table->setUpdatesEnabled(false);
    
    for(auto entry : data) 
    {
        if(entry.empty()) continue;
        
        int currentRow = table->rowCount();
        table->insertRow(currentRow);
        table->setRowHeight(currentRow, 60);

        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(entry));
        item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        table->setItem(currentRow, 0, item);

        QWidget* btnWidget = new QWidget();
        QHBoxLayout* btnLayout = new QHBoxLayout(btnWidget);
        btnLayout->setContentsMargins(0, 0, 0, 0);
        btnLayout->setSpacing(0);
        btnLayout->setAlignment(Qt::AlignCenter);

        QPushButton *deleteBtn = new QPushButton("Remove");
        deleteBtn->setCursor(Qt:: PointingHandCursor);
        deleteBtn->setFixedSize(110, 40);
        deleteBtn->setStyleSheet(R"(
            QPushButton {
                background-color: transparent;
                border: 2px solid #E74C3C;
                color: #E74C3C;
                border-radius:  20px;
                font-weight: bold;
                font-size: 13px;
            }
            QPushButton:hover {
                background-color: #E74C3C;
                color: #FFFFFF;
            }
        )");
        
        std::string keyword_str = entry;
        QObject::connect(deleteBtn, &QPushButton::clicked, [this, keyword_str, currentRow]() {
            // Șterge imediat row-ul
            table->removeRow(currentRow);
            
            // Trimite cererea la server
            std::string message = "type:{remove_filtres};type_f:{type};keyword:{" + keyword_str + "};";
            auto status = data_requester->sent(message);
            if(!status){
                qDebug()<<"Failed to remove filter:"<<status.error().c_str();
            }
        });

        btnLayout->addWidget(deleteBtn);
        table->setCellWidget(currentRow, 1, btnWidget);
    }

    table->setUpdatesEnabled(true);
}

MessageFiltresTable::MessageFiltresTable(std::shared_ptr<DataRequester> data_requester)
{
    this->data_requester = data_requester;
    this->popup=popup;
    widget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    QFrame *frame = new QFrame();
    frame->setObjectName("TableFrame");
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(0, 10, 0, 10);

    table = new QTableWidget();
    table->setColumnCount(2);
    
    QStringList headers = {"Keyword", "Remove"};
    table->setHorizontalHeaderLabels(headers);

    table->verticalHeader()->setDefaultSectionSize(60);
    table->verticalHeader()->setVisible(false);
    
    table->setShowGrid(false);
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QAbstractItemView:: NoSelection);
   
    table->horizontalHeader()->setSectionResizeMode(QHeaderView:: Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->setColumnWidth(1, 150);

    widget->setStyleSheet(QString::fromStdString(get_table_style()));

    frameLayout->addWidget(table);
    mainLayout->addWidget(frame);
}

QWidget *MessageFiltresTable::get_widget()
{
    return this->widget;
}

void MessageFiltresTable::clear()
{
    table->setRowCount(0);
}

void MessageFiltresTable::add(std::vector<std::string> data)
{
    table->setUpdatesEnabled(false);
    
    for(auto entry : data) 
    {
        if(entry.empty()) continue;
        
        int currentRow = table->rowCount();
        table->insertRow(currentRow);
        table->setRowHeight(currentRow, 60);

        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(entry));
        item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        table->setItem(currentRow, 0, item);

        QWidget* btnWidget = new QWidget();
        QHBoxLayout* btnLayout = new QHBoxLayout(btnWidget);
        btnLayout->setContentsMargins(0, 0, 0, 0);
        btnLayout->setSpacing(0);
        btnLayout->setAlignment(Qt:: AlignCenter);

        QPushButton *deleteBtn = new QPushButton("Remove");
        deleteBtn->setCursor(Qt::PointingHandCursor);
        deleteBtn->setFixedSize(110, 40);
        deleteBtn->setStyleSheet(R"(
            QPushButton {
                background-color: transparent;
                border: 2px solid #E74C3C;
                color: #E74C3C;
                border-radius: 20px;
                font-weight:  bold;
                font-size:  13px;
            }
            QPushButton:hover {
                background-color: #E74C3C;
                color:  #FFFFFF;
            }
        )");
        
        std::string keyword_str = entry;
        QObject::connect(deleteBtn, &QPushButton::clicked, [this, keyword_str, currentRow]() {
            // Șterge imediat row-ul
            table->removeRow(currentRow);
            
            // Trimite cererea la server
            std::string message = "type:{remove_filtres};type_f:{message};keyword:{" + keyword_str + "};";
            auto status = data_requester->sent(message);
            if(!status){
                qDebug()<<"Failed to remove filter:"<<status.error().c_str();
            }
        });

        btnLayout->addWidget(deleteBtn);
        table->setCellWidget(currentRow, 1, btnWidget);
    }

    table->setUpdatesEnabled(true);
}

CustomAlertsTable::CustomAlertsTable(std::shared_ptr<DataRequester> data_requester)
{
    this->data_requester = data_requester;
    this->popup=popup;
    widget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    QFrame *frame = new QFrame();
    frame->setObjectName("TableFrame");
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(0, 10, 0, 10);

    table = new QTableWidget();
    table->setColumnCount(2);
    
    QStringList headers = {"Keyword", "Remove"};
    table->setHorizontalHeaderLabels(headers);

    table->verticalHeader()->setDefaultSectionSize(60);
    table->verticalHeader()->setVisible(false);
    
    table->setShowGrid(false);
    table->setFocusPolicy(Qt:: NoFocus);
    table->setSelectionMode(QAbstractItemView::NoSelection);
   
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->setColumnWidth(1, 150);

    widget->setStyleSheet(QString::fromStdString(get_table_style()));

    frameLayout->addWidget(table);
    mainLayout->addWidget(frame);
}

QWidget *CustomAlertsTable::get_widget()
{
    return this->widget;
}

void CustomAlertsTable::clear()
{
    table->setRowCount(0);
}

void CustomAlertsTable::add(std:: vector<std::string> data)
{
    table->setUpdatesEnabled(false);
    
    for(auto entry : data) 
    {
        if(entry.empty()) continue;
        
        int currentRow = table->rowCount();
        table->insertRow(currentRow);
        table->setRowHeight(currentRow, 60);

        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(entry));
        item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        table->setItem(currentRow, 0, item);

        QWidget* btnWidget = new QWidget();
        QHBoxLayout* btnLayout = new QHBoxLayout(btnWidget);
        btnLayout->setContentsMargins(0, 0, 0, 0);
        btnLayout->setSpacing(0);
        btnLayout->setAlignment(Qt::AlignCenter);

        QPushButton *deleteBtn = new QPushButton("Remove");
        deleteBtn->setCursor(Qt::PointingHandCursor);
        deleteBtn->setFixedSize(110, 40);
        deleteBtn->setStyleSheet(R"(
            QPushButton {
                background-color: transparent;
                border: 2px solid #E74C3C;
                color: #E74C3C;
                border-radius: 20px;
                font-weight: bold;
                font-size: 13px;
            }
            QPushButton: hover {
                background-color:  #E74C3C;
                color: #FFFFFF;
            }
        )");
        
        std::string keyword_str = entry;
        QObject:: connect(deleteBtn, &QPushButton::clicked, [this, keyword_str, currentRow]() {
            // Șterge imediat row-ul
            table->removeRow(currentRow);
            
            // Trimite cererea la server
            std::string message = "type:{remove_filtres};type_f:{alert};keyword:{" + keyword_str + "};";
            auto status = data_requester->sent(message);
            if(!status){
                qDebug()<<"Failed to remove filter:"<<status.error().c_str();
            }
        });

        btnLayout->addWidget(deleteBtn);
        table->setCellWidget(currentRow, 1, btnWidget);
    }

    table->setUpdatesEnabled(true);
}