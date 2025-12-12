#include "UnknownAgentDashboard.h"
#include "../../style/DashboardStyle.hpp"

void UnknownAgentDashboardScreen::bind_buttons()
{

}

UnknownAgentDashboardScreen::UnknownAgentDashboardScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    QGridLayout *layout = new QGridLayout;
    SyslogDashboard_table= std::make_shared<UnknownAgentTable>();
    btn = new QPushButton("UNKNOWN Dashboard AGENT");
    btn->setStyleSheet("background-color: black; color: white;");
    layout->addWidget(btn,0,0);
    layout->addWidget(SyslogDashboard_table->get_widget(),1,0);
    bind_buttons();
    page->setLayout(layout);
}
void UnknownAgentDashboardScreen::on_enter() {
    qDebug()<<"whitelsit enter";
   
}

void UnknownAgentDashboardScreen::on_exit() {
    qDebug()<<"whitelsit leave";
 
}




UnknownAgentTable::UnknownAgentTable()
{
    widget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    QFrame *frame = new QFrame();
    frame->setObjectName("TableFrame");
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(0, 10, 0, 10); 

    table = new QTableWidget();
    table->setColumnCount(5);
    
    QStringList headers = {"Nume", "IP Address", "Timp", "Admin", ""}; 
    table->setHorizontalHeaderLabels(headers);

  
    table->setShowGrid(false);
    table->setFocusPolicy(Qt::NoFocus); 
    table->setSelectionMode(QAbstractItemView::NoSelection); 
    table->verticalHeader()->setVisible(false); 
   
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed); 
    table->setColumnWidth(4, 120); 

    widget->setStyleSheet(QString::fromStdString(get_table_style()));

   
    frameLayout->addWidget(table);
    mainLayout->addWidget(frame);
}

QWidget *UnknownAgentTable::get_widget()
{
    return this->widget;
}

void UnknownAgentTable::clear()
{
    table->setRowCount(0); 
}
void UnknownAgentTable::add(std::vector<std::string> whitelist_data)
{
    table->setUpdatesEnabled(false); 

    for(auto entry : whitelist_data) 
    {
       
        auto content = BetterString::split(entry, "[]");
        if(content.size() <= 4) { 
            qDebug() << "Skip invalid entry (size too small):" << QString::fromStdString(entry);
            continue; 
        }

        table->insertRow(0);

        for(int i = 0; i < 4; ++i) {
            if((i + 1) >= content.size()) break;

            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(content[i+1]));
            item->setTextAlignment(Qt::AlignCenter); // Centrat frumos
            table->setItem(0, i, item);
        }

        QWidget* btnWidget = new QWidget();
        QHBoxLayout* btnLayout = new QHBoxLayout(btnWidget);
        btnLayout->setContentsMargins(0,0,0,0);
        btnLayout->setAlignment(Qt::AlignCenter);

        QPushButton *deleteBtn = new QPushButton("Șterge");
        deleteBtn->setCursor(Qt::PointingHandCursor);
     
        deleteBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #FFEBEE;
                color: #D32F2F;
                border-radius: 15px; 
                padding: 6px 15px;
                font-weight: bold;
                border: none;
            }
            QPushButton:hover {
                background-color: #FFCDD2;
            }
        )");

        QObject::connect(deleteBtn, &QPushButton::clicked, [this, deleteBtn]() {
            QWidget *w = deleteBtn->parentWidget();
            if(!w) return;
            for(int r = 0; r < table->rowCount(); ++r) {
                if(table->cellWidget(r, 4) == w) {
                    table->removeRow(r);
                    break;
                }
            }
        });

        btnLayout->addWidget(deleteBtn);
        table->setCellWidget(0, 4, btnWidget);
    }

    table->setUpdatesEnabled(true);
}