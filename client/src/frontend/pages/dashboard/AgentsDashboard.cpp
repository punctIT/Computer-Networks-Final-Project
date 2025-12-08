#include "AgentsDashboard.h"

void AgentsDashboardScreen::bind_buttons()
{

}

AgentsDashboardScreen::AgentsDashboardScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    QGridLayout *layout = new QGridLayout;
    AgentsDashboard_table= std::make_shared<AgentsTable>();
    btn = new QPushButton("Dashboard Agents");
    layout->addWidget(btn,0,0);
    layout->addWidget(AgentsDashboard_table->get_widget(),1,0);
    bind_buttons();
    page->setLayout(layout);
}
void AgentsDashboardScreen::on_enter() {
    qDebug()<<"whitelsit enter";
   
}

void AgentsDashboardScreen::on_exit() {
    qDebug()<<"whitelsit leave";
 
}




AgentsTable::AgentsTable()
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

   
    QString style = R"(
     
        QFrame#TableFrame {
            background-color: #FFFFFF;
            border-radius: 15px;  /* Aici e rotunjirea mare */
            border: 1px solid #E0E0E0;
        }

      
        QTableWidget {
            background-color: transparent; /* Transparent ca să se vadă rama */
            border: none;
        }

        
        QHeaderView::section {
            background-color: transparent;
            color: #7F8C8D;
            font-weight: bold;
            border: none;
            padding: 5px;
            font-size: 13px;
            border-bottom: 2px solid #F0F0F0; /* Linie sub header */
        }

        
        QTableWidget::item {
            color: #2C3E50;
            padding: 10px;
            border-bottom: 1px solid #F5F5F5; /* Linie fină între rânduri */
        }
    )";
    widget->setStyleSheet(style);

   
    frameLayout->addWidget(table);
    mainLayout->addWidget(frame);
}

QWidget *AgentsTable::get_widget()
{
    return this->widget;
}

void AgentsTable::clear()
{
    table->setRowCount(0); 
}
void AgentsTable::add(std::vector<std::string> whitelist_data)
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