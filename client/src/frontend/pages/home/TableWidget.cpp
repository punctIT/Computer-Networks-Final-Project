#include "TableWidget.h"
TableMenu::TableMenu()
{
    last_id = 0;
    widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0); 
    table = new QTableWidget();
    table->setColumnCount(6);
    
    table->setShowGrid(false); 
    table->setAlternatingRowColors(true); 
    table->setSelectionBehavior(QAbstractItemView::SelectRows); 
    table->setSelectionMode(QAbstractItemView::SingleSelection); 
    table->setFocusPolicy(Qt::NoFocus);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers); 
    table->verticalHeader()->setVisible(false);

    QStringList headers = {"ID", "Timestamp", "Severity", "Hostname", "Source", "Content"};
    table->setHorizontalHeaderLabels(headers);

    QHeaderView *header = table->horizontalHeader();
   
    header->setSectionResizeMode(QHeaderView::Interactive); 
    header->setSectionResizeMode(5, QHeaderView::Stretch);  

    header->resizeSection(0, 60);  
    header->resizeSection(1, 140); 
    header->resizeSection(2, 80); 
    header->resizeSection(3, 120); 
    header->resizeSection(4, 120); 

    QString style = R"(
        QTableWidget {
            background-color: #FFFFFF;
            border: none;
            gridline-color: #F0F0F0; /* Linie foarte subtilă dacă activezi gridul */
        }
        QTableWidget::item {
            padding: 8px; /* Spațiu ca să nu fie textul îngrămădit */
            border-bottom: 1px solid #F0F0F0;
        }
        QTableWidget::item:selected {
            background-color: #E3F2FD; /* Albastru deschis la selecție */
            color: #000000;
        }
        QHeaderView::section {
            background-color: #FAFAFA;
            color: #666666;
            padding: 8px;
            font-weight: bold;
            border: none;
            border-bottom: 2px solid #E0E0E0;
            text-transform: uppercase; /* Text majuscule pentru header */
            font-size: 12px;
        }
    )";
    table->setStyleSheet(style);

    layout->addWidget(table);
    widget->setLayout(layout);
}

QWidget *TableMenu::get_widget()
{
    return widget;
}
void TableMenu::pop()
{
    int lastRow = table->rowCount() - 1;
    if (lastRow >= 0)
        table->removeRow(lastRow);
}
unsigned int TableMenu::get_id()
{
    return last_id;
}
void TableMenu::add(std::vector<std::string> logs)
{
    for(auto log : logs ){
        auto content = BetterString::split(log,"[]");
        //qDebug()<<log.c_str()<< content.size();
        if(content.size()<6){
           continue;
        }
        table->insertRow(0);
        for(int i=0;i<=5;++i){
            table->setItem(0, i, new QTableWidgetItem(QString::fromStdString(content[i])));
            
        }
        try{
            last_id = std::stoi(content[0])+1;
        }
        catch(std::exception & e){
            qDebug()<<e.what();
        }
        
    }
   
}
