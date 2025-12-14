#include "WhitelistScreen.h"
#include "../../style/SecurityStyle.hpp"

void WhiteListScreen::bind_buttons()
{
     connect(data_requester. get(), &DataRequester::UpdateWhitelist, 
        this, [this](QString mesaj) {
           qDebug()<<"update table;";
           whitelist_table->clear();
           auto data = JUNK::deserialize(mesaj.toStdString());
           if(data.has_value() && data.value()["content"].has_value()){
                whitelist_table->add(BetterString::split(data.value()["content"].value(),"{}"));
           }
        });
}

WhiteListScreen::WhiteListScreen(std:: shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    QGridLayout *layout = new QGridLayout;
    whitelist_table= std::make_shared<WhitelistTable>(data_requester);
    add_whitelist=std::make_shared<AddWhitelistPopup>(window.get(),data_requester,400,300); 
    btn = new QPushButton("Add new whitelist rule");
     btn->setCursor(Qt::PointingHandCursor);
    btn->setFixedHeight(40);
    btn->setMinimumWidth(120);
    btn->setStyleSheet(R"(
        QPushButton {
            background-color:  #1ABC9C;
            color: #FFFFFF;
            border: none;
            border-radius: 20px;
            padding: 10px 25px;
            font-weight:  bold;
            font-size:  14px;
            font-family:  'Segoe UI', sans-serif;
        }
        QPushButton:hover {
            background-color: #16A085;
        }
        QPushButton:pressed {
            background-color: #0E6655;
        }
    )");
    layout->addWidget(new QLabel("Whitelist"),0,0);
    layout->addWidget(btn,2,0);
    layout->addWidget(whitelist_table->get_widget(),1,0);
    QObject::connect(btn,&QPushButton:: clicked,[this](){
        add_whitelist->showCentered();
    });
    bind_buttons();
    page->setLayout(layout);
}

void WhiteListScreen::on_enter() {
    qDebug()<<"whitelsit enter";
}

void WhiteListScreen::on_exit() {
    qDebug()<<"whitelsit leave";
}


WhitelistTable::WhitelistTable(std::shared_ptr<DataRequester> data_requester)
{
    this->data_requester=data_requester;
    widget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    QFrame *frame = new QFrame();
    frame->setObjectName("TableFrame");
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(0, 10, 0, 10); 

    table = new QTableWidget();
    table->setColumnCount(5);
    
    QStringList headers = {"Source Name", "IP Address", "Time", "Admin", "Remove Rule"}; 
    table->setHorizontalHeaderLabels(headers);

    // Setări importante pentru înălțimea rândurilor
    table->verticalHeader()->setDefaultSectionSize(60); // Înălțime rând mai mare
    table->verticalHeader()->setVisible(false);
    
    table->setShowGrid(false);
    table->setFocusPolicy(Qt::NoFocus); 
    table->setSelectionMode(QAbstractItemView::NoSelection); 
   
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed); 
    table->setColumnWidth(4, 150); // Lățime mai mare pentru buton

    widget->setStyleSheet(QString:: fromStdString(get_table_style()));

    frameLayout->addWidget(table);
    mainLayout->addWidget(frame);
}

QWidget *WhitelistTable::get_widget()
{
    return this->widget;
}

void WhitelistTable:: clear()
{
    table->setRowCount(0); 
}

void WhitelistTable:: add(std::vector<std:: string> whitelist_data)
{
    table->setUpdatesEnabled(false); 
    table->clear();
    for(auto entry : whitelist_data) 
    {
        auto content = BetterString::split(entry, "[]");
        if(content.size() <= 4) { 
            qDebug() << "Skip invalid entry (size too small):" << QString::fromStdString(entry);
            continue; 
        }

        int currentRow = table->rowCount();
        table->insertRow(currentRow);
        table->setRowHeight(currentRow, 60);

        for(int i = 0; i < 4; ++i) {
            if((i + 1) >= content.size()) break;

            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(content[i+1]));
            item->setTextAlignment(Qt:: AlignCenter | Qt::AlignVCenter);
            table->setItem(currentRow, i, item);
        }

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
                background-color:  transparent;
                border: 2px solid #E74C3C;
                color:  #E74C3C;
                border-radius: 20px;
                padding: 0px;
                font-weight: bold;
                font-size: 13px;
                font-family:  'Segoe UI', sans-serif;
            }
            QPushButton:hover {
                background-color: #E74C3C;
                color: #FFFFFF;
                border: 2px solid #C0392B;
            }
            QPushButton:pressed {
                background-color: #C0392B;
                color: #FFFFFF;
                border: 2px solid #C0392B;
            }
        )");
        QString ipAddress;
        if(content.size() > 2) {
            ipAddress = QString::fromStdString(content[1]);
        }
        QObject::connect(deleteBtn, &QPushButton::clicked, [this, ipAddress]() {
            for(int r = 0; r < table->rowCount(); ++r) {
                QTableWidgetItem* ipItem = table->item(r, 0); 
                if(ipItem && ipItem->text() == ipAddress) {
                    auto data = data_requester->sent(std::format("type:{{remove_whitelist_ip}};ip:{{{}}};",ipAddress.toStdString())); 
                    table->removeRow(r);
                    break;
                }
            }
        });

        btnLayout->addWidget(deleteBtn);
        table->setCellWidget(currentRow, 4, btnWidget);
    }

    table->setUpdatesEnabled(true);
}